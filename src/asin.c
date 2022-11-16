/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double asin(double)
    double acos(double)
*/

#include "_kmclib.h"
#include <errno.h>
#include <math.h>
#include <cordic.h>

double asin(d)
double d;
{
    if(d>1.0 || d<-1.0) {
        return __matherr(_DOMAIN,"asin",d,0.0,0.0);
    }
    d=atan2(d,sqrt(1-d*d));
    return d;
}

double acos(d)
double d;
{
    if(d>1.0 || d<-1.0) {
        return __matherr(_DOMAIN,"acos",d,0.0,0.0);
    }
    return (PI/2)-asin(d);
}


