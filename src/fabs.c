/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double fabs(double)
*/


#include "_kmclib.h"
#include <math.h>
#include <explog.h>

double fabs(x)        /* |x| */
double x;
{
    DFLOAT d;
    
    d.df=x;
    d.ub[SIG_INDEX] &= 0x7f;
    return d.df;
}
