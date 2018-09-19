/**
 *  file: Minuit.hh
 *  date: 2017.04.10
 *
 */

#ifndef MINUIT_HH
#define MINUIT_HH

//______________________________________________________________________________
class MinuitFCN
{
public:
  MinuitFCN( void ) {}
  virtual ~MinuitFCN( void ) {}

  virtual double operator()( int np, double *g, double *u, int flag ) = 0;

};

//______________________________________________________________________________
class Minuit
{
public:
  Minuit( MinuitFCN *fcn );
  ~Minuit( void );

public:
  bool Fit( int np, double *param, double *error,
	    const double *lowBand, const double *upperBand,
	    int MaxCall, double eps, double & f );

private:
  MinuitFCN *FCN;

  // MINERR
  double erp[30], ern[30];
  // PARINT
  double x[15], xt[15], dirin[15];
  int maxint, npar;
  // PAREXT
  double u[30];
  int nam[30];
  double werr[30];
  int maxext, nu;
  // LIMITS
  double alim[15], blim[30];
  int lcode[30], lcorsp[30], limset;
  // VARIAN
  double v[15][15];
  // FIX
  double xs[15], xts[15], wts[15];
  int ipfix[15], npfix;
  // CASC
  int jh, jl;
  double y[16];
  // DERIVA
  double g[30], g2[30];
  // SIMVEC
  double p[15][16], pstar[15], pstst[15], pbar[15], prho[15];
  // VARIAT
  double vt[15][15];

  // TITLE
  double title[13], data[2];
  int isw[7], nblock;
  // CONVER
  double epsi, apsi, vtest;
  int nstepq, nfcn, nfcnmx;

  // MINIMA
  double amin, up;
  int newmin, itaur;
  double sigma;

private:
  void   MNdat( int n, double *uk, double *wk,
	      const double *a, const double *b );
  void   MNgrad( void );
  void   MNinto( const double *pint );
  void   MNsmpl( void );
  void   MNderiv( double *gg, double *gg2 );
  void   MNhese( void );
  void   MNraza( double ynew, const double *pnew );
  double MNpint( double &pexti, int i );
  void   MNfxpr( int i2, int kode, int & ilax );
  int    MNvrmn( double *a1, int l, int m, int n );
  void   MNerr( void );


};

#endif
