/**
 *  file: MathTools.cc
 *  date: 2017.04.10
 *
 */

#include "MathTools.hh"

#include <cmath>
#include <limits>
#include <iostream>
#include <iomanip>
#include <string>

#include <std_ostream.hh>

#include "PrintHelper.hh"

#define ERROROUT 1

namespace
{
  const std::string& class_name("MathTools");
}

namespace math
{
  //______________________________________________________________________________
  bool SolveGaussJordan( const std::vector<double>& z,
			 const std::vector<double>& w,
			 const std::vector<double>& s,
			 const std::vector<double>& ct,
			 const std::vector<double>& st,
			 double& x0,
			 double& u0,
			 double& y0,
			 double& v0 )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    const std::size_t n = z.size();
    if( n != w.size()  ||
	n != s.size()  ||
	n != ct.size() ||
	n != st.size() ){
      hddaq::cerr << "#E " << func_name << " wrong vector size" << std::endl
		  << " z.size()="  << n
		  << " w.size()="  << w.size()
		  << " s.size()="  << s.size()
		  << " ct.size()=" << ct.size()
		  << " st.size()=" << st.size() << std::endl;
      return false;
    }

    double matrx[16] = {};
    double *mtp[4]   = {};
    double fitp[4]   = {};
    mtp[0] = &matrx[ 0];
    mtp[1] = &matrx[ 4];
    mtp[2] = &matrx[ 8];
    mtp[3] = &matrx[12];

    for( int i=0; i<4; ++i )
      for( int j=0; j<4; ++j )
	mtp[i][j] = 0.0;

    for( std::size_t i=0; i<n; ++i ){
      double ww=w[i], zz=z[i], ss=s[i], ctt=ct[i], stt=st[i];
      mtp[0][0] += ww*ctt*ctt;
      mtp[0][1] += ww*zz*ctt*ctt;
      mtp[0][2] += ww*ctt*stt;
      mtp[0][3] += ww*zz*ctt*stt;
      mtp[1][1] += ww*zz*zz*ctt*ctt;
      mtp[1][2] += ww*zz*ctt*stt;
      mtp[1][3] += ww*zz*zz*ctt*stt;
      mtp[2][2] += ww*stt*stt;
      mtp[2][3] += ww*zz*stt*stt;
      mtp[3][3] += ww*zz*zz*stt*stt;

      fitp[0] += ww*ss*ctt;
      fitp[1] += ww*zz*ss*ctt;
      fitp[2] += ww*ss*stt;
      fitp[3] += ww*zz*ss*stt;
    }
    mtp[1][0] = mtp[0][1];
    mtp[2][0] = mtp[0][2];
    mtp[3][0] = mtp[0][3];
    mtp[2][1] = mtp[1][2];
    mtp[3][1] = mtp[1][3];
    mtp[3][2] = mtp[2][3];

#if 0
    PrintMatrix( mtp, "Original Matrix: M_ij" );
    PrintVector( fitp, "Original Vector: Q_i" );
#endif

    double Org[4][4]  = {{}};
    double Org_vec[4] = {};
    for( int i=0; i<4; ++i ){
      Org_vec[i] = fitp[i];
      for( int j=0; j<4; ++j ){
	Org[i][j] = mtp[i][j];
      }
    }

    int indxr[4] = {};
    int indxc[4] = {};
    int ipiv[4]  = {};
    if( !GaussJordan( mtp, 4, fitp, indxr, indxc, ipiv ) ){
      hddaq::cerr << func_name << " Fitting failed" << std::endl;
      return false;
    }

    x0 = fitp[0];
    u0 = fitp[1];
    y0 = fitp[2];
    v0 = fitp[3];

    double Inv[4][4] = {{}};
    double Sol[4]    = {};
    for( int i=0; i<4; ++i ){
      for( int j=0; j<4; ++j ){
	Inv[i][j] = mtp[i][j];
	Sol[i] += Inv[i][j]*Org_vec[j];
      }
    }

    double Final[4][4] = {{}};
    for( int i=0; i<4; ++i ){
      for( int j=0; j<4; ++j ){
	for( int k=0; k<4; ++k ){
	  Final[i][j] += Inv[i][k]*Org[k][j];
	}
	if(Final[i][j]<1.e-10) Final[i][j]=0.;
      }
    }

#if 0
    PrintVector( indxr, "indxr[4] Gauss-Jordan" );
    PrintVector( indxc, "indxc[4] Gauss-Jordan" );
    PrintVector( ipiv,  "ipiv[4] Gauss-Jordan" );
    PrintMatrix( Inv,   "Inverse Matrix" );
    PrintVector( fitp,  "Solution from Gauss-Jordan" );
    PrintVector( Sol,   "Solution from (M^-1)*Q_i" );
    PrintMatrix( Final, "(M^-1)*M" );
#endif

    return true;
  }

  //______________________________________________________________________________
  bool
  GaussElim( double **a, int n, double *b, int *indx, int *ipiv )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    double big, c, pivinv, sum, c2;
    int js   = 0;
    int irow = 0;

    for(int i=0; i<n; ++i) ipiv[i]=0;
    for(int i=0; i<n; ++i){
      big = 0.;
      for(int j=0; j<n; ++j){
	if( !ipiv[j] ){
	  if((c=std::abs(a[j][i]))>=big){ big=c; irow=j; }
	}
	else if(ipiv[j]>1){
#ifdef ERROROUT
	  hddaq::cerr << func_name << " Singular Matrix" << std::endl;
#endif
	  return false;
	}
      }
      ++(ipiv[irow]); indx[i]=irow;
      if(a[irow][i]==0.0){
#ifdef ERROROUT
	hddaq::cerr << func_name << " Singular Matrix" << std::endl;
#endif
	return false;
      }
      pivinv=1.0/a[irow][i];

      for(int j=0; j<n; ++j){
	if(ipiv[j]==0){
	  c=a[j][i]; a[j][i]=0.0;
	  for(int k=i+1; k<n; ++k)
	    a[j][k]-=a[irow][k]*pivinv*c;
	  b[j]-=b[irow]*pivinv*c;
	}
      }
    }

    b[indx[n-1]]/=a[indx[n-1]][n-1];
    for(int i=n-2; i>=0; --i){
      sum=b[indx[i]];
      for(int j=i+1; j<n; ++j)
	sum-=a[indx[i]][j]*b[indx[j]];
      b[indx[i]]=sum/a[indx[i]][i];
    }
    for(int i=0; i<n; ++i){
      if(indx[i]!=i){
	c2=b[i];
	for(int j=indx[i]; indx[j]!=j; j=js){
	  c=b[j]; b[j]=c2; c2=c; js=indx[j]; indx[j]=j;
	}
      }
    }
    return true;
  }

  //______________________________________________________________________________
  bool
  GaussJordan( double **a, // matrix a[n][n]
	       int n,      // dimension
	       double *b,  // vector b[n]
	       int *indxr, int *indxc, int *ipiv )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    for( int i=0; i<n; ++i )
      ipiv[i]=0;

    for( int i=0; i<n; ++i ){
      double big=0.0;
      int irow=-1, icol=-1;
      for( int j=0; j<n; ++j )
	if( ipiv[j]!=1 )
	  for( int k=0; k<n; ++k ){
	    if( ipiv[k]==0 ){
	      if( std::abs(a[j][k])>=big ){
		big=std::abs(a[j][k]);
		irow=j; icol=k;
	      }
	    }
	    else if( ipiv[k]>1 ){
#ifdef ERROROUT
	      hddaq::cerr << func_name << " Singular Matrix" << std::endl;
#endif
	      return false;
	    }
	  }
      ++(ipiv[icol]);

      if( irow!=icol ){
	for( int k=0; k<n; ++k ){
	  double ta=a[irow][k];
	  a[irow][k]=a[icol][k];
	  a[icol][k]=ta;
	}
	double tb=b[irow];
	b[irow]=b[icol];
	b[icol]=tb;
      }

      indxr[i]=irow; indxc[i]=icol;

      if(a[icol][icol]==0.0){
#ifdef ERROROUT
	hddaq::cerr << func_name << " Singular Matrix"  << std::endl;
#endif
	return false;
      }
      double pivinv=1./a[icol][icol];
      a[icol][icol]=1.;
      for(int k=0; k<n; ++k) a[icol][k]*=pivinv;
      b[icol]*=pivinv;
      for( int k=0; k<n; ++k ){
	if(k!=icol){
	  double d=a[k][icol];
	  a[k][icol]=0.;
	  for( int l=0; l<n; ++l ) a[k][l] -= a[icol][l]*d;
	  b[k] -= b[icol]*d;
	}
      }
    }

    for(int l=n-1; l>=0; --l){
      if( indxr[l]!=indxc[l] ){
	for(int k=0; k<n; ++k ){
	  double t=a[k][indxr[l]];
	  a[k][indxr[l]]=a[k][indxc[l]];
	  a[k][indxc[l]]=t;
	}
      }
    }
    return true;
  }

  //______________________________________________________________________________
  bool
  InterpolateRatio( int n, const double *xa, const double *ya,
		    double *w1, double *w2,
		    double x, double &y, double &dy )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    int i, m, ns=1;
    double w, t, hh, h, dd;

    hh=std::abs(x-xa[0]);
    for(i=1; i<=n; ++i){
      h=std::abs(x-xa[i-1]);
      if(h==0.0) { y=ya[i-1]; dy=0.0; return true; }
      else if(h<hh){ ns=i; hh=h; }
      w1[i-1]=ya[i-1]; w2[i-1]=ya[i-1]*(1.+Epsilon());
    }
    y=ya[ns-1]; ns--;
    for(m=1; m<n; ++m){
      for(i=1; i<=n-m; ++i){
	w=w1[i]-w2[i-1]; h=xa[i+m-1]-x;
	t=(xa[i-1]-x)*w2[i-1]/h; dd=t-w1[i];
	if(dd==0.0){
#ifdef ERROROUT
	  hddaq::cerr << func_name << ": Error" << std::endl;
#endif
	  y=Infinity(); dy=Infinity(); return false;
	}
	dd=w/dd; w2[i-1]=w1[i]*dd; w1[i-1]=t*dd;
      }
      if( 2*ns < (n-m) ) dy=w1[ns];
      else { dy=w2[ns-1]; ns--; }
      y+=dy;
    }
#if 0
    hddaq::cout << func_name << ": x=" << std::setw(10) << x
		<< " y=" << std::setw(10) << y << std::endl;
#endif
    return true;
  }

  //______________________________________________________________________________
  bool
  InterpolatePol( int n, const double *xa, const double *ya,
		  double *w1, double *w2,
		  double x, double &y, double &dy )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    int i, m, ns=1;
    double den, dif, dift, ho, hp, w;

    dif=std::abs(x-xa[0]);
    for(i=1; i<=n; ++i){
      if( (dift=std::abs(x-xa[i-1]))<dif ){ ns=i; dif=dift; }
      w1[i-1]=w2[i-1]=ya[i-1];
    }
    y=ya[ns-1]; --ns;
    for(m=1; m<n; ++m){
      for(i=1; i<=n-m; ++i){
	ho=xa[i-1]-x; hp=xa[i+m-1]-x;
	w=w1[i]-w2[i-1];
	den=ho-hp;
	if(den==0.0){
#ifdef ERROROUT
	  hddaq::cerr << func_name << ": Error" << std::endl;
#endif
	  y=Infinity(); dy=Infinity(); return false;
	}
	den=w/den;
	w2[i-1]=hp*den; w1[i-1]=ho*den;
      }
      if( 2*ns<(n-m) ) dy=w1[ns];
      else           { dy=w2[ns-1]; --ns; }
      y+=dy;
    }
    return false;
  }

  //______________________________________________________________________________
  bool
  SVDksb( double **u, const double *w, double **v,
	  int m, int n, const double *b, double *x, double *wv )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    for( int j=0; j<n; ++j ){
      double s=0.0;
      if( w[j]!=0.0 ){
	for( int i=0; i<m; ++i )
	  s += u[i][j]*b[i];
	s /= w[j];
      }
      wv[j]=s;
    }
    for( int i=0; i<n; ++i ){
      double s=0.0;
      for( int j=0; j<n; ++j )
	s += v[i][j]*wv[j];
      x[i]=s;
    }
    return true;
  }

  //______________________________________________________________________________
  inline double
  pythag( double a, double b )
  {
    double aa=std::abs(a), ab=std::abs(b);
    if( aa>ab )
      return aa*std::sqrt(1.+(ab/aa)*(ab/aa));
    else if( ab!=0. )
      return ab*std::sqrt(1.+(aa/ab)*(aa/ab));
    else
      return 0.0;
  }

  //______________________________________________________________________________
  bool
  SVDcmp( double **a, int m, int n, double *w, double **v, double *wv )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    double g     = 0.;
    double scale = 0.;
    double anorm = 0.;
    double s, f, h, c;
    int nm;

#ifdef DebugPrint
    for( int i=0; i<n; ++i ) {
      w[i]=wv[i]=0.0;
      for( int j=0; j<n; ++j ) v[j][i]=0.0;
    }

    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": A in SVDcmp 1" <<  std::endl;
      for( int ii=0; ii<m; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << a[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": V in SVDcmp 1" << std::endl;
      for( int ii=0; ii<n; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << v[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": W in SVDcmp 1" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << w[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;

      hddaq::cout << func_name << ": WV in SVDcmp 1" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << wv[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;
      hddaq::cout << std::endl;
    }
#endif

    // Householder method
    for( int i=0; i<n; ++i ){
      wv[i]=scale*g;
      g = scale = 0.0;
      if( i<m ){
	for( int k=i; k<m; ++k ) scale += std::abs(a[k][i]);
	if( scale!=0. ){
	  s = 0;
	  for( int k=i; k<m; ++k ){
	    a[k][i] /= scale;
	    s += a[k][i]*a[k][i];
	  }
	  f = a[i][i];
	  g = ( (f>0.0) ? -sqrt(s) : sqrt(s) );
	  h = f*g-s;
	  a[i][i] = f-g;
	  for( int j=i+1; j<n; ++j ){
	    s = 0.0;
	    for( int k=i; k<m; ++k ) s += a[k][i]*a[k][j];
	    f = s/h;
	    for( int k=i; k<m; ++k )  a[k][j] += f*a[k][i];
	  }
	  for( int k=i; k<m; ++k ) a[k][i] *= scale;
	}
      }     /* if( i<m ) */
      w[i] = scale*g;
      g = s = scale = 0.0;

      if( i<m && i!=n-1 ){
	for( int k=i+1; k<n; ++k ) scale += std::abs(a[i][k]);
	if( scale!=0.0 ){
	  for( int k=i+1; k<n; ++k ){
	    a[i][k] /= scale;
	    s += a[i][k]*a[i][k];
	  }
	  f = a[i][i+1];
	  g = ( (f>0.0) ? -sqrt(s) : sqrt(s) );
	  h = f*g-s;
	  a[i][i+1] = f-g;
	  for( int k=i+1; k<n; ++k ) wv[k] = a[i][k]/h;
	  for( int j=i+1; j<m; ++j ){
	    s = 0.0;
	    for( int k=i+1; k<n; ++k ) s += a[j][k]*a[i][k];
	    for( int k=i+1; k<n; ++k ) a[j][k] += s*wv[k];
	  }
	  for( int k=i+1; k<n; ++k ) a[i][k] *= scale;
	}
      }   /* if( i<m && i!=n-1 ) */
      double tmp=std::abs(w[i])+std::abs(wv[i]);
      if( tmp>anorm ) anorm = tmp;
    }     /* for( int i ... ) */

#if DebugPrint
    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": A in SVDcmp 2" <<  std::endl;
      for( int ii=0; ii<m; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << a[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": V in SVDcmp 2" << std::endl;
      for( int ii=0; ii<n; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << v[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": W in SVDcmp 2" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << w[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;

      hddaq::cout << func_name << ": WV in SVDcmp 2" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << wv[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;
      hddaq::cout << std::endl;
    }
#endif

    for( int i=n-1; i>=0; --i ){
      if( i<n-1 ){
	if( g!=0.0 ){
	  for( int j=i+1; j<n; ++j ) v[j][i] = (a[i][j]/a[i][i+1])/g;
	  for( int j=i+1; j<n; ++j ){
	    s = 0.0;
	    for( int k=i+1; k<n; ++k ) s += a[i][k]*v[k][j];
	    for( int k=i+1; k<n; ++k ) v[k][j] += s*v[k][i];
	  }
	}
	for( int j=i+1; j<n; ++j )
	  v[i][j] = v[j][i] = 0.0;
      }
      v[i][i]=1.0;  g=wv[i];
    }   /* for( int i= ... ) */

#ifdef DebugPrint
    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": A in SVDcmp 3" <<  std::endl;
      for( int ii=0; ii<m; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << a[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": V in SVDcmp 3" << std::endl;
      for( int ii=0; ii<n; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << v[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": W in SVDcmp 3" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << w[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;

      hddaq::cout << func_name << ": WV in SVDcmp 3" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << wv[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;
      hddaq::cout << std::endl;
    }
#endif

    int mn = ( (m<n) ? m : n );

    for( int i=mn-1; i>=0; --i ){
      g=w[i];
      for( int j=i+1; j<n; ++j ) a[i][j]=0.0;
      if( g!=0.0 ){
	g = 1./g;
	for( int j=i+1; j<n; ++j ){
	  s = 0.0;
	  for( int k=i+1; k<m; ++k ) s += a[k][i]*a[k][j];
	  f = (s/a[i][i])*g;
	  for( int k=i; k<m; ++k ) a[k][j] += f*a[k][i];
	}
	for( int j=i; j<m; ++j ) a[j][i] *= g;
      }
      else
	for( int j=i; j<m; ++j ) a[j][i] = 0.0;

      a[i][i] += 1.0;
    }   /* for( int i= ... ) */

#ifdef DebugPrint
    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": A in SVDcmp 4" <<  std::endl;
      for( int ii=0; ii<m; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << a[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": V in SVDcmp 4" << std::endl;
      for( int ii=0; ii<n; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << v[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": W in SVDcmp 4" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << w[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;

      hddaq::cout << func_name << ": WV in SVDcmp 4" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << wv[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;
      hddaq::cout << std::endl;
    }
#endif


    int ll=1;

    for( int k=n-1; k>=0; --k ){
      for( int its=1; its<=30; ++its ){
	int flag=1; nm=ll;
	for( ll=k; ll>=0; --ll ){
	  nm=ll-1;
	  if( std::abs(wv[ll])+anorm == anorm ){
	    flag=0; break;
	  }
	  if( std::abs(w[nm])+anorm == anorm )
	    break;
	}

	if(flag){
	  c=0.0; s=1.0;
	  for( int i=ll; i<=k; ++i ){
	    f = s*wv[i]; wv[i] *= c;
	    if( std::abs(f)+anorm == anorm )
	      break;
	    g=w[i]; h=pythag(f,g); w[i]=h;
	    h=1./h; c=g*h; s=-f*h;
	    for( int j=0; j<m; ++j ){
	      double y=a[j][nm], z=a[j][i];
	      a[j][nm]=y*c+z*s; a[j][i]=z*c-y*s;
	    }
	  }
	}   /* if(flag) */

	double z = w[k];
	if( ll==k ){
	  if( z<0. ){
	    w[k]=-z;
	    for( int j=0; j<n; ++j ) v[j][k]=-v[j][k];
	  }
	  break;
	}
#ifdef ERROROUT
	if( its==30 ){
	  // 	hddaq::cerr << func_name
	  // 		  << ": -- no convergence in 30 dvdcmp iterations --"
	  // 		  << std::endl;
	  return false;
	}
#endif
	nm=k-1;
	double x=w[ll], y=w[nm];
	g=wv[nm]; h=wv[k];
	f=((y-z)*(y+z)+(g-h)*(g+h))/(2.*h*y);
	g=pythag(f,1.0);
	double gtmp = ( (f>0.) ? g : -g );
	f=((x-z)*(x+z)+h*((y/(f+gtmp))-h))/x;
	c=s=1.0;
	for( int j=ll; j<=nm; ++j ){
	  g=wv[j+1]; y=w[j+1]; h=s*g; g=c*g;
	  z=pythag(f,h);
	  wv[j]=z; c=f/z; s=h/z;
	  f=x*c+g*s; g=g*c-x*s;
	  h=y*s; y=y*c;
	  for( int jj=0; jj<n; ++jj ){
	    x=v[jj][j]; z=v[jj][j+1];
	    v[jj][j]=x*c+z*s; v[jj][j+1]=z*c-x*s;
	  }
	  z=pythag(f,h);
	  w[j]=z;
	  if( z!=0.0 ){ z=1./z; c=f*z; s=h*z; }
	  f=c*g+s*y; x=c*y-s*g;
	  for( int jj=0; jj<m; ++jj ){
	    y=a[jj][j]; z=a[jj][j+1];
	    a[jj][j]=y*c+z*s; a[jj][j+1]=z*c-y*s;
	  }
	}
	wv[ll]=0.0; wv[k]=f; w[k]=x;
      }   /* for( int its ... ) */
    }     /* for( int k= ... ) */


#ifdef DebugPrint
    {
      PrintHelper helper( 3, std::ios::scientific );
      hddaq::cout << func_name << ": A in SVDcmp 5" <<  std::endl;
      for( int ii=0; ii<m; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << a[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": V in SVDcmp 5" << std::endl;
      for( int ii=0; ii<n; ++ii ){
	for( int ij=0; ij<n; ++ij ){
	  hddaq::cout << std::setw(12) << v[ii][ij];
	  if( ij!=n-1 ) hddaq::cout << ",";
	}
	hddaq::cout << std::endl;
      }
      hddaq::cout << func_name << ": W in SVDcmp 5" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << w[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;

      hddaq::cout << func_name << ": WV in SVDcmp 5" << std::endl;
      for( int ij=0; ij<n; ++ij ){
	hddaq::cout << std::setw(12) << wv[ij];
	if( ij!=n-1 ) hddaq::cout << ",";
      }
      hddaq::cout << std::endl;
      hddaq::cout << std::endl;
    }
#endif

    return true;
  }

  //______________________________________________________________________________
  template <typename T>
  void
  PrintMatrix( T *mat, const std::string& arg,
	       const int column, const int line )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    PrintHelper helper( 5, std::ios::scientific );

    hddaq::cout << func_name << " " << arg << std::endl;
    for(int l=0; l<line; ++l){
      for(int c=0; c<line; ++c){
	hddaq::cout << "  " << std::setw(12) << mat[l][c];
      }
      hddaq::cout << std::endl;
    }
  }

  //______________________________________________________________________________
  template <typename T>
  void
  PrintVector( T *vec, const std::string& arg, const std::size_t size )
  {
    static const std::string func_name("["+class_name+"::"+__func__+"()]");

    PrintHelper helper( 5, std::ios::scientific );

    hddaq::cout << func_name << " " << arg << std::endl;
    for( std::size_t i=0; i<size; ++i ){
      hddaq::cout << "  " << std::setw(12) << vec[i];
    }
    hddaq::cout << std::endl;
  }
}
