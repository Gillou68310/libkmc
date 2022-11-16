/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double pow(double ,double)
*/


#include "_kmclib.h"
#include <math.h>
#include <explog.h>

double pow(x,y)        /* x^y */
double x,y;
{
    int sign=1;
    int i;

    if(x==1.0 || y==1.0){    /* @@97/3/10 tsuka fix */
    return x;
    }
    if (x==0.0) {
        if (y<=0.0) {
            return __matherr(_SING,"pow",x,y,0.0);
     }
        return 0.0;
    }
    if (x<0) {
    i=y;
    if (y!=i) {        /* x=negative y!=integer */
            return __matherr(_SING,"pow",x,y,0.0);
    }
    if(i & 1) sign = -1;
    x = fabs(x);
    }
    x=log(x);
    x=x*y;
    y=exp(x);
    y=y*sign;
    return y;
}


 
