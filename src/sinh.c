/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double sinh(double ),cosh(double),tanh(double)
*/

#include "_kmclib.h"
#include <math.h>


/*** for Turboc ***/
/**** for GCC ****/
#define GCC 1
#define MBIT 0x4000000000000000LL
#define CBIT 52
#define NR 1.0e-8
#define XLONG long long



#define  PI 3.14159265358979312
#define KH 1.20749706776307231

XLONG _ahtbl[]={                /* atanhh (2^-i) */
  0,                /* i=0 not use */
  0.549306144334054891*MBIT,        /* i=1 */
  0.255412811882995361 *MBIT,
  0.125657214140453083 *MBIT,
  0.0625815714770029952 *MBIT,
  0.031260178490666965 *MBIT,
  0.0156262717520522648 *MBIT,
  0.00781265895154040733 *MBIT,
  0.00390626986839681233 *MBIT,
  0.00195312748353260526 *MBIT,
  0.000976562810441035075 *MBIT,
  0.000488281288805085122 *MBIT,
  0.000244140629850637741 *MBIT,
  0.000122070313106329792 *MBIT,
  6.10351563257773428e-05 *MBIT,
  3.05175781344730335e-05 *MBIT,
  1.52587890636841826e-05 *MBIT,
  7.62939453139802578e-06 *MBIT,
  3.81469726558799271e-06 *MBIT,
  1.90734863280787414e-06 *MBIT,
  9.53674316405671794e-07 *MBIT,
  4.76837158203052738e-07 *MBIT,
  2.38418579101553474e-07 *MBIT,
  1.19209289550780125e-07 *MBIT,
  5.9604644775390486e-08 *MBIT,
  2.9802322387695296e-08 *MBIT,
  1.49011611938476546e-08 *MBIT,
  7.45058054141267772e-09 *MBIT,
  3.72529028458412625e-09 *MBIT,
  1.86264514576151008e-09 *MBIT,
  9.31322573748116778e-10 *MBIT,
  4.65661287090898823e-10 *MBIT,
  2.3283064359965952e-10 *MBIT,
  1.16415321813382287e-10 *MBIT,
  5.82076609100792754e-11 *MBIT,
  2.91038304558866707e-11 *MBIT,
  1.45519152281550936e-11 *MBIT,
  7.27595761413048634e-12 *MBIT,
  3.63797880707847806e-12 *MBIT,
  1.81898940354254775e-12 *MBIT,
  9.09494701772101057e-13 *MBIT,
  4.54747350886257324e-13 *MBIT,
  2.27373675443180361e-13 *MBIT,
  1.13686837721603105e-13 *MBIT,
  5.68434188608047837e-14 *MBIT,
  2.84217094304031996e-14 *MBIT,
  1.42108547152018018e-14 *MBIT,
  7.10542735760095137e-15 *MBIT,
  3.55271367880048831e-15 *MBIT,
  1.77635683940024731e-15 *MBIT,
  8.88178419700124444e-16 *MBIT,
  4.44089209850062419e-16 *MBIT,
  2.22044604925031259e-16 *MBIT,
  1.11022302462515642e-16 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT,
  0 *MBIT    /* 63 */
};



_xsinhcosh(th,sinhp,coshp)
double th;        /* -pi/2 <= th <= pi/2 */
double *sinhp,*coshp;    /* sinh , cosh */
{
    int i,retry;
    XLONG x,xx,y,z;
    
    x=(double)KH*MBIT;
    y=0;
    z=th*MBIT;
    retry=0;
    for(i=1;i<CBIT;++i) {
        if (z>=0) {
            xx=x+(y>>i);
            y=y+(x>>i);
            z=z-_ahtbl[i];
        }
        else {
            xx=x-(y>>i);
            y=y-(x>>i);
            z=z+_ahtbl[i];
        }
        x=xx;
    if (retry==0) {
        if (i==4 || i==13 || i==40) {
            retry=1;
            --i;
        }
    }
    else retry=0;
    }
    *sinhp = (double)y/MBIT;
    *coshp = (double)x/MBIT;
}

double sinh(th)
double th;
{
    double s,c;
    int ti,sign;


    if (th>1 || th <-1) {
    return (exp(th)-exp(-th))/2;
    }
    _xsinhcosh(th,&s,&c);
    return s;
}

double cosh(th)
double th;
{
    double s,c;
    int ti;
    
    ti = (th / PI)+(th>=0 ? 0.5 : -0.5);
    th = th - ti*PI;

    _xsinhcosh(th,&s,&c);
    return (ti&1 ? -c : c);
}


double tanh(th)
double th;
{
    double s,c;
    int ti;
    
    ti = (th / PI)+(th>=0 ? 0.5 : -0.5);
    th = th - ti*PI;

    if(th < NR && th >-NR) return th;

    _xsinhcosh(th,&s,&c);
    return s/c;
}






