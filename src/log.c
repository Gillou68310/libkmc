/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double log(double )
*/


#include "_kmclib.h"
#include <math.h>
#include <explog.h>


#define CBIT 54



extern XLONG __etbl[];    /* log(1+2^-i) */




double __log(x)
double x;    /* 0.5 <= x < 1 */
{
    XLONG xx,y,d;
    int i;
    y=0;
    xx=x*MBIT;
    for(i=1;i<CBIT;++i) {
    d=xx+(xx>>i);
    if (d<1*MBIT) {
        xx=d;
        y=y-__etbl[i];
    }
    }
    return (double)y/MBIT;
}




double log(x)
double x;
{
    double y;
    double __log(),frexp();
    DFLOAT *ip;
    int xint;

    if (x<0.0) {
        return __matherr(_DOMAIN,"log",x,0.0,0.0);
    }
    if (x==0) {
    ip = (DFLOAT *)&y;
    ip->ull = 0xfff0000000000000LL;        /* set -mugen */
    return __matherr(_OVERFLOW,"log",x,0.0,y);
    }
    if (x==1) return 0.0;
    x=frexp(x,&xint);
    y=__log(x);
    y=y+xint*KL2;
    return y;
}

double log10(x)
double x;
{
    return KL10E * log(x);
}

