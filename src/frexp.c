/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    double frexp(double ,int *)
*/


#include "_kmclib.h"
#include <math.h>
#include <explog.h>

double frexp(x,ep)
double x;
int *ep;
{
    DFLOAT *p;
    int exp;
    if (x==0.0) {
        *ep=0;
        return 0.0;
    }
    p = (DFLOAT *)&x;
    exp= ((p->ui[EXP_INDEX]>>20)& 0x7ff)-0x3ff;    /* get exp */
    *ep= exp+1;
    p->ui[EXP_INDEX] = (p->ui[EXP_INDEX]& ~0x7ff00000)
                | (0x3fe<<20);        /* set exp */
    return x;
}
