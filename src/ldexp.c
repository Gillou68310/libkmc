/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double ldexp(double,int)
*/

#include "_kmclib.h"
#include <math.h>
#include <explog.h>

double ldexp(x,exp)
double x;
int exp;
{
    int e;
    DFLOAT d;
    d.df=x;
    e= ((d.ui[EXP_INDEX]>>20)& 0x7ff);        /* get exp */
    e += exp;
    if (e<=0) return 0.0;
    if (e>=0x7ff) {        /* +mugen */
    d.ull = (d.ull &0x8000000000000000LL) | (0x7ff0000000000000LL);
    return __matherr(_OVERFLOW,"ldexp",x,0.0,d.df);
    }

    d.ui[EXP_INDEX] = (d.ui[EXP_INDEX]& ~0x7ff00000)
                | (e<<20);        /* set exp */
    return d.df;
}

 
