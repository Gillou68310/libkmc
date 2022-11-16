/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double sqrt(double )
*/


#include "_kmclib.h"
#include <math.h>

#define R2    1.414213562373095634    /* sqrt(2) */



#define EXP_INDEX    0
#define SIG_INDEX       0


typedef union {
    double df;
    unsigned int ui[2];
    unsigned char ub[8];
    long long ll;
} DFLOAT;

typedef union {
    float sf;
    unsigned int ui;
} SFLOAT;



#define LOOP 3


double sqrt(x)
double x;
{
    int i,exp,iexp;
    DFLOAT xx,x0;
    SFLOAT sxx,sx0;
    double x1;
    float sx1;

    x0.df=xx.df=x;
    if (x0.ub[SIG_INDEX]&0x80) {    /* x < 0 */
    return __matherr(_DOMAIN,"sqrt",x,0.0,0.0);
    }


    exp=((x0.ui[EXP_INDEX]>>20) & 0x7ff);
    if (exp==0) return 0.0;
    exp -= 0x3ff;

    x0.ui[EXP_INDEX] = ((x0.ui[EXP_INDEX]) & (~0x7ff00000))
                | (((0x3ff-2) & 0x7ff)<<20);
    sx0.sf=x0.df;
    sx1=sx0.sf;
    sx0.ui = (sx0.ui & (~0x3f800000)) | ((0x7f-5)<<23);

    if (exp&1) {
        iexp=exp=(exp-1)>>1;
        sx0.sf = sx1+sx0.sf+0.4375;
    xx.ui[EXP_INDEX] = ((xx.ui[EXP_INDEX]) & (~0x7ff00000))
                | (((0x3ff-1) & 0x7ff)<<20);
    }
    else {
        iexp=exp=exp>>1;
        sx0.sf = sx1-sx0.sf+0.28125;
    xx.ui[EXP_INDEX] = ((xx.ui[EXP_INDEX]) & (~0x7ff00000))
                | (((0x3ff-2) & 0x7ff)<<20);
    }
    sxx.sf=xx.df;

/* newton 1kaime (single float) */
    sx0.sf=(sx0.sf+sxx.sf/sx0.sf);
    exp=sx0.ui & 0x3f800000;
    sx0.ui = (sx0.ui &(~0x3f800000))
        | ((exp-0x800000)&0x3f800000);        /* exp -1 */
    x0.df=sx0.sf;

    for(i=0;i<LOOP-1;++i) {
        x0.df=(x0.df+xx.df/x0.df);
    exp=((x0.ui[EXP_INDEX]) & 0x7ff00000);
    x0.ui[EXP_INDEX] = ((x0.ui[EXP_INDEX]) & (~0x7ff00000))
        | (((exp-0x100000)) & 0x7ff00000);    /* set exp -1 */
    }



    x0.ui[EXP_INDEX] = ((x0.ui[EXP_INDEX]) & (~0x7ff00000))
                | (((iexp+0x3ff) & 0x7ff)<<20);
    return x0.df;
}





