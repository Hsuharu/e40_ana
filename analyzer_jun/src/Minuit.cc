/**
 *  file: Minuit.cc
 *  date: 2017.04.10
 *
 */

#include "Minuit.hh"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include <std_ostream.hh>

namespace
{
  const std::string& class_name("Minuit");
}

//______________________________________________________________________________
Minuit::Minuit( MinuitFCN *fcn )
  : FCN(fcn), maxint(15), maxext(30)
{
}

//______________________________________________________________________________
Minuit::~Minuit( void )
{
}

//______________________________________________________________________________
inline int
max0( int a, int b )
{
  if( a>b ) return a;
  else      return b;
}

//______________________________________________________________________________
bool
Minuit::Fit( int np, double *param, double *error,
	     const double *lowBand, const double *upperBand,
	     int MaxCall, double eps, double& f )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  int nfcn = 1;
  MNdat( np, param, error, lowBand, upperBand );
  MNinto( x );
  amin = (*FCN)(npar,g,u,1);

  if( MaxCall<=0 )
    nfcnmx = 1000;
  else
    nfcnmx = MaxCall;

  epsi = eps;
  if(epsi<=0.0) epsi = 0.1*up;

  newmin=itaur=isw[0]=0;
  vtest=0.01;

  int nf=nfcn;

  apsi=epsi;
  MNgrad();
  if( isw[1]<=2 && isw[0]!=1 ){
    nfcnmx += (nf-nfcn);
    nf = nfcn;
    MNsmpl();
    if( isw[0]!=1 ){
      nfcnmx += (nf-nfcn);
      MNgrad();
    }
  }

  // let FCN know it has converged
  f=(*FCN)(npar,g,u,3);

  MNerr();
  for( int j=0; j<npar; ++j ){
    param[j]=u[j];
    error[j]=werr[j];
  }
  return true;
}

//______________________________________________________________________________
void
Minuit::MNdat( int n, double *uk, double *wk,
	       const double *a, const double *b )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  nblock=1;
  //  double versn=3.;
  for( int i=0; i<7; ++i ) isw[i]=0;
  sigma=0.;
  npfix=nu=npar=0;
  int nint_=0, ifatal=0;
  for( int i=0; i<maxext; ++i ){
    u[i]=erp[i]=ern[i]=0.;
    nam[i]=lcode[i]=lcorsp[i]=0;
  }
  up=1.0;
  isw[4]=1;

  isw[1]=0;
  nu=n;
  if(nu>maxext){
    hddaq::cerr << func_name << ": Fatal Nu>MaxExt" << std::endl;
    exit(-1);
  }

  for( int k=0; k<nu; ++k ){
    u[k]=uk[k];
    werr[k]=wk[k];
    if(wk[k]<=0.0){
      lcode[k]=0;
      continue;
    }
    ++nint_;
    double aa=a[k], bb=b[k];
    if( aa==0. && bb==0. ){
      lcode[k]=1;
      continue;
    }
    else {
      if( aa==bb ){
	++ifatal;
	hddaq::cerr << func_name
		    << ": Fatal Error: Upper and lower limits are equal."
		    << std::endl;
      }
      else if(bb<aa){
	double sav=bb;
	bb=aa; aa=sav;
      }
      alim[k]=aa; blim[k]=bb; lcode[k]=4;
      if( ( (bb-u[k])<0 && (u[k]-aa)>0 ) ||
	  ( (bb-u[k])>0 && (u[k]-aa)<0 ) ){
	++ifatal;
	hddaq::cerr << func_name
		    << ": Fatal Error: Parameter outside limits"
		    << std::endl;
      }
    }
  }

  if(nint_>maxint){
    ++ifatal;
    hddaq::cerr << func_name
		<< ": Too many variable parameters. You request " << nint_ << "\n"
		<< "This version of Minuit in only dimensioned for "
		<< maxint << std::endl;
  }
  if(ifatal){
    hddaq::cerr << func_name
		<< ": Fatal errors on parameter cards. Abort."
		<< std::endl;
    exit(-1);
  }
  npar=0;
  for( int k=0; k<nu; ++k ){
    if(lcode[k]<=0) continue;
    lcorsp[k]=npar+1;
    double sav=u[k];
    x[npar] = MNpint(sav,k);
    xt[npar]=x[npar];
    double sav2=sav+werr[k];
    double vplu=MNpint(sav2,k)-x[npar];
    sav2=sav-werr[k];
    double vminu=MNpint(sav2,k)-x[npar];
    dirin[npar]=0.5*(std::abs(vplu)+std::abs(vminu));
    ++npar;
  }

}

//______________________________________________________________________________
void
Minuit::MNgrad( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const double slamin = 0.2,  slamax = 3.0;
  static const double tlamin = 0.05, tlamax = 6.0;

  double gs[30], r[15], xxs[15], flnu[15], vg[15], vii[15];
  double f;
  double slam, tlam;
  int iter, matgd;
  int npard, negg2, ntry;
  double gvg, delgam;

  if(npar<=0) return;
  int iswtr = isw[4]-itaur;
  int npfn  = nfcn;
  double parn = double(npar);
  double rho2 = 10.*apsi, rostop = 1.E-5*apsi;
  double trace=1.;
  int iflag=4;
  if( isw[2]==1 ) iflag=2;
  double fs=amin;

 label1:
 label2:
  npard=npar;
  for( int i=0; i<npar; ++i ){
    double d=0.02*std::abs(dirin[i]);
    if( isw[1]>=1 ) d=0.02*sqrt(std::abs(v[i][i]*up));
    if( d<1.E-8*std::abs(x[i]) ) d=1.e-8*x[i];
    dirin[i]=d;
  }
  ntry=0;

 label4:
  negg2=0;
  for( int id=0; id<npard; ++id ){
    int i=id+npar-npard;
    double d=dirin[i];
    double xtf=x[i];
    x[i]=xtf+d;  MNinto(x);
    double fs1=(*FCN)(npar,g,u,4); ++nfcn;
    x[i]=xtf-d; MNinto(x);
    double fs2=(*FCN)(npar,g,u,4); ++nfcn;
    x[i]=xtf;
    gs[i]=(fs1-fs2)*0.5/d;
    g2[i]=(fs1+fs2-2.*amin)/(d*d);
    if(g2[i]>1.E-30) continue;

    ++negg2; ++ntry;
    if(ntry>4){ MNinto(x); return; }

    d=50.*std::abs(dirin[i]);
    double xbeg=xtf;
    if( gs[i]<0. ) dirin[i]=-dirin[i];
    int kg=0, nf=0, ns=0;

  label5:
    x[i]=xtf+d;  MNinto(x);
    f=(*FCN)(npar,g,u,4); ++nfcn;
    if( f<amin ) goto label6;
    if( kg==1 ) goto label8;
    kg=-1; ++nf;  d=-0.4*d;
    if( nf<10 ) goto label5;
    d *= 1000.;
    goto label7;

  label6:
    xtf=x[i]; d=3.*d; amin=f;
    kg=1; ++ns;
    if( ns<10 ) goto label5;
    if( amin<fs ) goto label8;
    d *= 0.001;

  label7:
    xtf=xbeg; g2[i]=1.; --negg2;

  label8:
    x[i]=xtf; dirin[i]=0.1*d; fs=amin;
  }

  if( negg2>=1 ) goto label4;
  ntry=0;
  matgd=1;

  if( isw[1]>1 ) goto label15;

 label11:
  ntry=1; matgd=0;
  for( int i=0; i<npar; ++i ){
    for( int j=0; j<npar; ++j ) v[i][j]=0.;
    v[i][i]=2./g2[i];
  }

 label15:
  sigma=0.;
  for( int i=0; i<npar; ++i ){
    if( v[i][i]<0.0 ) goto label11;
    xxs[i]=x[i];
    double ri=0.0;
    for( int j=0; j<npar; ++j )
      ri += (v[i][j]*gs[j]);
    sigma += (gs[i]*ri*0.5);
  }
  if( sigma<0.0 ){
    if( ntry==0 ) goto label11;
    isw[1]=0;
    //    goto label230;
    MNinto(x);
    return;
  }
  isw[1]=1;
  iter=0;
  MNinto(x);

  // label24:
  while(1){
    double gdel=0.;
    for( int i=0; i<npar; ++i ){
      double ri=0.0;
      for( int j=0; j<npar; ++j )
	ri += (v[i][j]*gs[j]);
      dirin[i]=-0.5*ri;
      gdel += (dirin[i]*gs[i]);
      x[i]=xxs[i]+dirin[i];
    }
    MNinto(x);
    f=(*FCN)(npar,g,u,4); ++nfcn;
    double denom=2.0*(f-amin-gdel);
    if(denom<=0.0)
      slam = slamax;
    else{
      slam = -gdel/denom;
      if( slam<slamin ) slam=slamin;
      if( slam>slamax ) slam=slamax;
    }
    if( std::abs(slam-1.)>=0.1 ){
      for( int i=0; i<npar; ++i )
	x[i] = xxs[i]+slam*dirin[i];
      MNinto(x);
      double f2=(*FCN)(npar,g,u,4); ++nfcn;
      double aa=fs/slam, bb=f/(1.-slam),
	cc=f2/(slam*(slam-1.));
      denom=2*(aa+bb+cc);
      if( denom<=0.0 ) tlam=tlamax;
      else{
	tlam=(aa*(slam+1.)+bb*slam+cc)/denom;
	if( tlam<tlamin ) tlam=tlamin;
	if( tlam>tlamax ) tlam=tlamax;
      }
      for( int i=0; i<npar; ++i )
	x[i]=xxs[i]+tlam*dirin[i];
      MNinto(x);
      double f3=(*FCN)(npar,g,u,4); ++nfcn;
      if( f>=amin && f2>=amin && f3>=amin ) goto label200;
      if( f<f2 && f<f3 ) slam=1.;
      else{
	if( f2<f3 ) f=f2;
	else{ f=f3; slam=tlam; }
      }
      for( int i=0; i<npar; ++i ){
	dirin[i] *= slam;
	x[i]=xxs[i]+dirin[i];
      }
    }
    amin=f; isw[1]=2;
    if( sigma+fs-amin < rostop )        break;
    if( sigma+rho2+fs-amin <= apsi ){
      if( trace<vtest )                 break;
    }
    if( nfcn-npfn >= nfcnmx ){
      isw[0]=1; MNinto(x); return;
    }

    ++iter;
    if( isw[2]==1 ){
      MNinto(x);
      amin=(*FCN)(npar,g,u,iflag); ++nfcn;
    }
    MNderiv(g,g2);

    rho2=sigma; sigma=0.; gvg=0.0; delgam=0.0;
    for( int i=0; i<npar; ++i ){
      double ri=0., vgi=0.;
      for( int j=0; j<npar; ++j ){
	vgi += (v[i][j]*(g[j]-gs[j]));
	ri  += (v[i][j]*g[j]);
      }
      r[i]=ri*0.5; vg[i]=vgi*0.5;
      gvg += ((g[i]-gs[i])*vg[i]);
      delgam += (dirin[i]*(g[i]-gs[i]));
      sigma += (g[i]*r[i]);
    }

    if( sigma<0. ) goto label1;
    if( gvg<=0. || delgam<=0. ){
      if( sigma<0.1*rostop ) break;
      goto label1;
    }

    for( int i=0; i<npar; ++i ){
      vii[i]=v[i][i];
      for( int j=0; j<npar; ++j ){
	double d=dirin[i]*dirin[j]/delgam-vg[i]*vg[j]/gvg;
	v[i][j] += (2.*d);
      }
    }
    if( delgam>gvg ){
      for( int i=0; i<npar; ++i )
	flnu[i]=dirin[i]/delgam-vg[i]/gvg;
      for( int i=0; i<npar; ++i )
	for( int j=0; j<npar; ++j )
	  v[i][j] += (2.*gvg*flnu[i]*flnu[j]);
    }
    //label135:
    trace=0.;
    for( int i=0; i<npar; ++i ){
      xxs[i]=x[i]; gs[i]=g[i];
      double a5=(v[i][i]-vii[i])/(v[i][i]+vii[i]);
      trace += (a5*a5);
    }
    trace = sqrt(trace/parn); fs=f;
  }

 label170:
  isw[1]=3; iswtr-=(3*itaur);
  if( itaur>0 ) return;
  if( matgd>0 ) return;
  if( nfcn-npfn>=npar*(npar+5)/2 ) return;
  MNhese();
  if( isw[1]>=2 ) isw[1]=3;
  return;

 label200:
  for( int i=0; i<npar; ++i ) x[i]=xxs[i];

  isw[1]=1;
  if( sigma<rostop ) goto label170;
  if( matgd>0 ) goto label2;

  return;
}

//______________________________________________________________________________
void
Minuit::MNinto( const double *pint )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( int i=0; i<nu; ++i ){
    int j=lcorsp[i]-1;
    if( j<0 ) continue;
    if( lcode[i]==1 ){
      u[i]=pint[j];
    }
    else{
      double al=alim[i];
      u[i]=al+0.5*(sin(pint[j])+1.)*(blim[i]-al);
    }
  }
  return;
}

//______________________________________________________________________________
void
Minuit::MNsmpl( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const double alpha=1., beta=0.5, gamma=2.;
  static const double rhomin=4.0, rhomax=8.0;
  double ynpp1, absmin, sig2;
  int ignal, ncycl;

  if(npar<=0) return;
  int npfn=nfcn, nparp1=npar+1;
  double rho1=1.+alpha, rho2=rho1+alpha*gamma;
  double wg=1./double(npar);
  int iflag=4;

  for( int i=0; i<npar; ++i ){
    if( isw[1]>=1 ) dirin[i]=sqrt(v[i][i]*up);
    if( std::abs(dirin[i])<1.E-10*std::abs(x[i]) )
      dirin[i]=1.E-8*x[i];
    if( itaur<1 ) v[i][i]=dirin[i]*dirin[i]/up;
  }
  if( itaur<1 ) isw[1]=1;

 label1:
  ynpp1=amin;
  jl=nparp1-1; y[nparp1-1]=amin;
  absmin=amin;
  for( int i=0; i<npar; ++i ){
    double aming=amin, bestx=x[i];
    pbar[i]=x[i];
    int kg=0, ns=0, nf=0;
  label4:
    x[i]=bestx+dirin[i];
    MNinto(x);
    double f=(*FCN)(npar,g,u,4); ++nfcn;
    if( f<aming	) goto label6;
    if( kg==1 ) goto label8;
    kg=-1; ++nf; dirin[i] *= -0.4;
    if( nf<3 ) goto label4;
    ns=6;
  label6:
    bestx=x[i]; dirin[i] *= 3.;
    aming=f; kg=1; ++ns;
    if( ns<6 ) goto label4;
  label8:
    y[i]=aming;
    if( aming<absmin ){
      jl=i; absmin=aming;
    }
    x[i]=bestx;
    for( int k=0; k<npar; ++k ) p[k][i]=x[k];
  }

  jh=nparp1-1; amin=y[jl];
  MNraza( ynpp1, pbar );
  for( int i=0; i<npar; ++i ) x[i]=p[i][jl];
  MNinto(x);
  sigma *= 10.;
  sig2=sigma; ignal=0; ncycl=0;

  // label50:
  while(1){
    if( ignal>=10 ) goto label1;
    if( sig2<epsi && sigma<epsi ) break;
    sig2=sigma;
    if(( nfcn-npfn)>nfcnmx ){
      isw[0]=1;                   break;
    }
    for( int i=0; i<npar; ++i ){
      double pb=0.;
      for( int j=0; j<nparp1; ++j )
	pb += (wg*p[i][j]);
      pbar[i]=pb-wg*p[i][jh];
      pstar[i]=(1.+alpha)*pbar[i]-alpha*p[i][jh];
    }
    MNinto(pstar);
    double ystar=(*FCN)(npar,g,u,4); ++nfcn;
    if( ystar<amin ){
      for( int i=0; i<npar; ++i )
	pstst[i]=gamma*pstar[i]+(1.-gamma)*pbar[i];
      MNinto(pstst);
      double ystst=(*FCN)(npar,g,u,4); ++nfcn;
      double y1=(ystar-y[jh])*rho2, y2=(ystst-y[jh])*rho1;
      double rho=0.5*(rho2*y1-rho1*y2)/(y1-y2);
      if( rho>= rhomin ){
	if( rho>rhomax ) rho=rhomax;
	for( int i=0; i<npar; ++i )
	  prho[i]=rho*pstar[i]+(1.-rho)*p[i][jh];
	MNinto(prho);
	double yrho=(*FCN)(npar,g,u,4); ++nfcn;
	if( yrho<y[jl] && yrho<ystst ){
	  MNraza(yrho,prho); ignal=max0(ignal-2,0); ++ncycl;
	}
	else{
	  if( ystst<y[jl] ){
	    ignal=max0(ignal-2,0); MNraza(ystst,pstst); ++ncycl;
	  }
	  else if( yrho>y[jl] ){
	    if( ystst>=y[jl] ){
	      ignal=max0(ignal-1,0); MNraza(ystar,pstar); ++ncycl;
	    }
	    else{
	      ignal=max0(ignal-2,0); MNraza(ystst,pstst); ++ncycl;
	    }
	  }
	  else {
	    MNraza(yrho,prho); ignal=max0(ignal-2,0); ++ncycl;
	  }
	}
      }
      else{ /* if( rho>=rhomin ) */
	if( ystst<y[jl] ){
	  ignal=max0(ignal-2,0); MNraza(ystst,pstst); ++ncycl;
	}
	else{
	  ignal=max0(ignal-1,0); MNraza(ystar,pstar); ++ncycl;
	}
      }
    }
    else{   /* if( ystar<amin ) */
      if( ystar<y[jh] ){
	int jhold=jh;
	MNraza(ystar,pstar);
	if( jhold!=jh ) continue;
      }
      for( int i=0; i<npar; ++i )
	pstst[i]=beta*p[i][jh]+(1.-beta)*pbar[i];
      MNinto(pstst);
      double ystst=(*FCN)(npar,g,u,4); ++nfcn;
      if( ystst>y[jh] ) goto label1;
      if( ystst<amin ){
	MNraza(ystst,pstst); ++ncycl;
      }
      else{
	MNraza(ystst,pstst); ++ignal;
      }
    }
  } /* while(1) */

  for( int i=0; i<npar; ++i ){
    double pb=0.;
    for( int j=0; j<nparp1; ++j )
      pb += (wg*p[i][j]);
    pbar[i]=pb-wg*p[i][jh];
  }
  MNinto(pbar);
  double ypbar=(*FCN)(npar,g,u,iflag); ++nfcn;
  if( ypbar<amin ) MNraza(ypbar,pbar);
  MNinto(x);

  if( nfcnmx+npfn-nfcn>=3*npar &&
      sigma>2.*epsi ) goto label1;

  return;
}

//______________________________________________________________________________
void
Minuit::MNderiv( double *gg, double *gg2 )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const double epsmac=1.E-5;

  if( isw[2]==1 ){
    for( int i=0; i<nu; ++i ){
      int lc=lcorsp[i]-1;
      if(lc<0) continue;
      if( lcode[i]>1 ){
	double dd=(blim[i]-alim[i])*0.5*cos(x[lc]);
	gg[lc]=gg[i]*dd;
      }
      else{
	gg[lc]=gg[i];
      }
    }
  }
  else{
    int iflag=4;
    double gy[30];
    for( int i=0; i<npar; ++i ){
      double eps=0.1*std::abs(dirin[i]);
      if( isw[1]>=1 ) eps += (0.005*sqrt(v[i][i]*up));
      if( eps<epsmac*std::abs(x[i]) ) eps=epsmac*x[i];
      double xtf=x[i];
      x[i] = xtf+eps; MNinto(x);
      double fs1=(*FCN)(npar,gy,u,iflag); ++nfcn;
      x[i] = xtf-eps; MNinto(x);
      double fs2=(*FCN)(npar,gy,u,iflag); ++nfcn;
      gg[i] =(fs1-fs2)/eps*0.5;
      gg2[i]=(fs1+fs2-2.*amin)*0.5/eps;
      x[i]=xtf;
    }
    MNinto(x);
  }
  return;
}

//______________________________________________________________________________
void
Minuit::MNhese( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const double dfwant=0.01, dfzero=0.00000001,
    dfmin=0.001, dfmax=0.1;

  double yy[15],gy[30];
  int iflag=4, npfn=nfcn, npard=npar;

  int mdiag=0;
  for( int id=0; id<npard; ++id ){
    int i=id+npar-npard;
    double d=0.02*std::abs(dirin[i]);
    if( isw[1]>=1 ) d=0.02*sqrt(std::abs(v[i][i]*up));
    double dirmin=dfzero*std::abs(x[i]);
    if( d<dirmin ) d=dirmin;
    for( int j=0; j<npar; ++j ) v[i][j]=0.;
    int icyc=0;
    double fs1, fs2;
    while(1){
      dirin[i]=d;
      double xtf=x[i];
      x[i]=xtf+d; MNinto(x);
      fs1=(*FCN)(npar,gy,u,iflag); ++nfcn;
      x[i]=xtf-d; MNinto(x);
      fs2=(*FCN)(npar,gy,u,iflag); ++nfcn;
      x[i]=xtf;

      ++icyc;
      if( icyc>=4 ) break;
      double df1=std::abs(fs1-amin), df2=std::abs(fs2-amin);
      double df;
      if( df1>df2 ) df=df1/up;
      else          df=df2/up;
      if( df>dfmin && df<dfmax ) break;
      else if( df>dfzero && df<=dfmin ){
	double c=sqrt(dfwant/df);
	if( c<0.001 ) c=0.001;
	d *= c;
      }
      else{
	d*=1000.;
      }
    }

    g[i] =(fs1-fs2)*0.5/d;
    g2[i]=(fs1+fs2-2.*amin)/(d*d);
    yy[i]=fs1;

    if( std::abs(g[i])+std::abs(g2[i])>1.E-30 ){
      if( g2[i]<=1.E-30 ) mdiag=1;
      v[i][i]=g2[i];
    }
    else if( itaur>=1 ){
      mdiag=1; v[i][i]=g2[i];
    }
    else{
      isw[1]=0;
      int ifix;
      MNfxpr(i,1,ifix);
      if( npar==0 ) mdiag=1;
    }
  }

  MNinto(x);
  if( mdiag==1 ){
    isw[1]=0;
    return;
  }
  isw[1]=1;
  if( npar!=1 ){
    int nparm1=npar-1;
    for( int i=0; i<nparm1; ++i ){
      for( int j=i+1; j<npar; ++j ){
	if( nfcnmx-nfcn+npfn<npar ) goto label210;
	double xti=x[i], xtj=x[j];
	x[i]+=dirin[i]; x[j]+=dirin[j]; MNinto(x);
	double fs1=(*FCN)(npar,gy,u,iflag); ++nfcn;
	x[i]=xti; x[j]=xtj;
	double elem=(fs1+amin-yy[i]-yy[j])/(dirin[i]*dirin[j]);
	if( elem*elem>=g2[i]*g2[j] ) elem=0.;
	v[i][j]=v[j][i]=elem;
      }
    }
  }
 label210:
  MNinto(x);
  if( MNvrmn(&v[0][0],maxint,maxint,npar)<1 )
    isw[1]=2;
  else {
  label216:
    isw[1]=1;
    for( int i=0; i<npar; ++i ){
      for( int j=0; j<npar; ++j ) v[i][j]=0.;
      v[i][i]=1./g2[i];
    }
    mdiag=0;
  }

  for( int i=0; i<npar; ++i )
    for( int j=0; j<npar; ++j )
      v[i][j]*=2.;

  sigma=0.;
  for( int i=0; i<npar; ++i ){
    if( v[i][i]<=0. ) mdiag=1;
    double r=0.0;
    for( int j=0; j<npar; ++j ){
      if( i!=j && v[i][j]*v[i][j]>=std::abs(v[i][i]*v[j][j]) )
	v[i][j]=v[j][i]=0.0;
      r += (v[i][j]*g[j]);
    }
    sigma += (0.5*r*g[i]);
  }
  if( mdiag==1 ){
    isw[1]=0;
    return;
  }
  if( sigma>0. ) return;
  goto label216;

}

//______________________________________________________________________________
void
Minuit::MNraza( double ynew, const double *pnew )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( int i=0; i<npar; ++i ) p[i][jh]=pnew[i];
  y[jh]=ynew;
  if( ynew<amin ){
    for( int i=0; i<npar; ++i ) x[i]=pnew[i];
    MNinto(x); amin=ynew; jl=jh;
  }
  jh=0;
  int nparp1=npar+1;
  for( int j=1; j<nparp1; ++j ){
    if( y[j]>y[jh] ) jh=j;
  }
  sigma = y[jh]-y[jl];
  if( sigma>0. ){
    double us=1./sigma;
    for( int i=0; i<npar; ++i ){
      double pbig=p[i][0], plit=pbig;
      for( int j=1; j<nparp1; ++j ){
	if( p[i][j]>pbig ) pbig=p[i][j];
	if( p[i][j]<plit ) plit=p[i][j];
      }
      dirin[i]=pbig-plit;
      if( itaur<1 )
	v[i][i]=0.5*(v[i][i]+us*dirin[i]*dirin[i]);
    }
  }
  else{
    hddaq::cerr << func_name
		<< ": Function value does not seem to depend on any on the "
		<< npar << " variable parameters \n"
		<< " Veryfy that step sizes are big enough and check FCN logic"
		<< std::endl;
  }
  return;
}

//______________________________________________________________________________
double
Minuit::MNpint( double& pexti, int i )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const double big=1.570796326795, small=-1.570796326795;

  int igo=lcode[i];
  if( igo<=1 || igo>4 )
    return pexti;
  else{
    double alimi=alim[i], blimi=blim[i];
    if( pexti-alimi<0. ){
      pexti=alimi+0.5*(blimi-alimi)*(sin(small)+1.);
      limset=1;
      return small;
    }
    else if( pexti-alimi==0. ){
      return small;
    }
    if( blimi-pexti>0.0 ){
      double yy=2.*(pexti-alimi)/(blimi-alimi)-1.;
      return atan(yy/sqrt(1.-yy*yy));
    }
    else if( blimi-pexti<0.0 ){
      pexti=alimi+0.5*(blimi-alimi)*(sin(big)+1.);
      limset=1;
      return big;
    }
    else{
      return big;
    }
  }
}

//______________________________________________________________________________
void
Minuit::MNfxpr( int i2, int kode, int &ilax )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  static const double epsmac=1.E-5;

  double yy[15];
  int it=0;

  if( kode>=0 ){
    int i=-1;
    if( kode==0 ) i=i2;
    else{
      for( int iq=0; iq<nu; ++iq ){
	if( lcorsp[iq]-1==i2 ){
	  i=iq;
	  break;
	}
      }
    }
    if( i>=nu || i<0 || lcorsp[i]<=0 ){
      ilax=0;
      hddaq::cerr << func_name << ": Error. Parameter "
		  << i2 << " was not variable" << std::endl;
      return;
    }
    int lc=lcorsp[i]-1;
    it=lc;
    lcorsp[i]=0; ilax=i; --npar; ++npfix;
    ipfix[npfix-1]=i; xs[npfix-1]=x[lc]; xts[npfix-1]=xt[lc];
    double eps=std::abs(dirin[lc])*10.;
    if( isw[1]>=1 ) eps += sqrt(std::abs(v[lc][lc])*up);
    if( eps<epsmac*std::abs(x[lc]) ) eps=epsmac*x[lc];
    wts[npfix-1]=eps*0.1;
    for( int ik=i; ik<nu; ++ik ){
      if(lcorsp[ik]>0){
	lc = lcorsp[ik]-2; --lcorsp[ik];
	x[lc]=x[lc+1]; xt[lc]=xt[lc+1];
	dirin[lc]=dirin[lc+1];
      }
    }
    if( isw[1]<=1 ){
      isw[1]=0;
      return;
    }
  }

  int kon=0;
  if( npar<=0 ) return;
  int kon2=0, mpar=npar+1;
  for( int i=0; i<mpar; ++i ) yy[i]=v[i][it];
  for( int i=0; i<mpar; ++i ){
    if( i==it ) continue;
    ++kon2;
    for( int j=0; j<mpar; ++j ){
      if( j==it ) continue;
      ++kon;
      double *v1=&v[0][0];
      v1[kon]=v[j][i]-yy[j]*yy[i]/yy[it];
    }
    kon=maxint*kon2;
  }

  for( int i=0; i<npar; ++i ){
    if( v[i][i]<=0.0 ){
      isw[1]=0;
      hddaq::cerr << func_name
		  << ": Covariance matrix was ill-conditioned and "
		  << "has been destroyed." << std::endl;
      return;
    }
    for( int j=0; j<npar; ++j ){
      if( i!=j && v[i][j]*v[i][j]>=v[i][i]*v[j][j] )
	v[i][j]=0.;
    }
  }
  return;
}

//______________________________________________________________________________
int
Minuit::MNvrmn( double *a1, int l, int m, int n )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  double pp[15], q[15], s[15];
  double *a[100];

  for( int i=0; i<l; ++i ) a[i]=&a1[i*m];

  int ifail=0;
  if( n<1 || n>maxint )  return ++ifail;

  for( int i=0; i<n; ++i ){
    double si=a[i][i];
    if( si<=0.0 ) return ++ifail;
    s[i]=1./sqrt(si);
  }
  for( int i=0; i<n; ++i )
    for( int j=0; j<n; ++j )
      a[i][j] *= (s[i]*s[j]);

  for( int i=0; i<n; ++i ){
    int k=i;
    q[k]=1./a[k][k]; pp[k]=1.; a[k][k]=0.;
    int kp1=k+1, km1=k-1;
    if( k!=0 ){
      for( int j=0; j<km1; ++j ){
	pp[j]=a[j][k]; q[j]=a[j][k]*q[k]; a[j][k]=0.;
      }
    }
    if( k!=n-1 ){
      for( int j=kp1; j<n; ++j ){
	pp[j]=a[k][j]; q[j]=-a[k][j]*q[k]; a[k][j]=0.;
      }
    }

    for( int j=0; j<n; ++j )
      for( int l=j; l<=j; ++l )
	a[j][l] += (pp[j]*q[l]);
  }

  for( int j=0; j<n; ++j )
    for( int l=0; l<=j; ++l ){
      a[l][j] *= (s[l]*s[j]);
      a[j][l] = a[l][j];
    }

  return ifail;
}

//______________________________________________________________________________
void
Minuit::MNerr( void )
{
  static const std::string func_name("["+class_name+"::"+__func__+"()]");

  for( int i=0; i<nu; ++i ){
    int l=lcorsp[i]-1;
    if( l==-1 || isw[1]<1 ) return;
    double dx=sqrt(std::abs(v[l][l])*up);
    if( lcode[i]>1 ){
      double al=alim[i], ba=blim[i]-al;
      double du1=al+0.5*(sin(x[l]+dx)+1.)*ba-u[i];
      double du2=al+0.5*(sin(x[l]-dx)+1.)*ba-u[i];
      if( dx>1. ) du1=ba;
      dx= 0.5*(std::abs(du1)+std::abs(du2));
    }
    werr[i]=dx;
  }
  return;
}
