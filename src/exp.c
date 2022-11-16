/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double exp(double )
*/


#include "_kmclib.h"
#include <math.h>
#include <explog.h>


#define CBIT 54


extern XLONG __etbl[];    /* log(1+2^-i) */

double __exp(x)
double x;    /* 0 <= x <= log2 (0.6931..) */
{
    XLONG xx,y,d;
    int i;
    y=1*MBIT;
    xx=x*MBIT;
    for(i=1;i<CBIT;++i) {
    d=__etbl[i]-xx;
    if (d<=0) {
        xx=-d;
        y=y+(y>>i);
    }
    }
    return (double)y/MBIT;
}



double exp(x)
double x;
{
    double __exp();
    double t,tint,tfra,X,y;
    unsigned long yexp;
    DFLOAT *ip;

    ip = (DFLOAT *)&y;
    if (x>=710) goto over;
    if (x<=-710) goto under;
    
    t=x*KL2B;
    tfra=modf(t,&tint);
    X=tfra*KL2;
    if (X>0) {
        y=__exp(X);
    }
    else if (X<0) {
        y=1.0/__exp(-X);
    }
    else y=1.0;
    yexp= ((ip->ui[EXP_INDEX]>>20)& 0x7ff);    /* get exp */
    yexp += (int)tint;
    if (yexp>0x7fe) {    /* Over */
over:
    ip = (DFLOAT *)&y;
    ip->ull = 0x7ff0000000000000LL;        /* set mugen */
    return __matherr(_OVERFLOW,"exp",x,0.0,y);
    }
    else if (yexp<1) {    /* Under */
under:
        return 0.0;
    }
    ip->ui[EXP_INDEX] = (ip->ui[EXP_INDEX]& ~0x7ff00000)
                | (yexp<<20);        /* set exp */
    return y;
}



