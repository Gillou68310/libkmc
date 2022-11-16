/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double fmod(double ,double)
    double ceil(double)
    floor(double)
*/


#include "_kmclib.h"
#include <math.h>
#include <explog.h>


double __fint(x)    /* convert to an integer */
double x;
{
    DFLOAT d;
    int exp;
    
    d.df=x;
    exp= ((d.ui[EXP_INDEX]>>20)& 0x7ff)-0x3ff;    /* get exp */
    if(exp < 0) return 0.0;    /* x<1 */
    d.ull &= ((long long)0x8000000000000000LL) >> (exp+11);
    return d.df;
}


double fmod(x,y)    /* x%y */
double x,y;
{
    double i;
    if (y==0) {
/*
        return __matherr(_SING,"fmod",x,y,0.0);
*/
    return 0.0;
    }
    i=__fint(x/y);
    return x - i * y;
}

double ceil(x)
double x;
{
    double i;
    i = __fint(x);
    if (x>=0.0 && i!=x) return i+1;
    else return i;
}

double floor(x)
double x;
{
    double i;
    i = __fint(x);
    if (x<0.0 && i!=x) return i-1;
    else return i;
}



    
