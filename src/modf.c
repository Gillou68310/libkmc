/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

#include "_kmclib.h"
#include <math.h>
#include <explog.h>

double modf(double x,double *ipart)
{
    int exp;
    int msk_index;
    int msk_byte;
    DFLOAT *ip;

    ip=(DFLOAT *)ipart;
    ip->df=x;
    exp=((ip->ui[EXP_INDEX]>>20) & 0x7ff)-0x3ff;
    if(exp<0){
    ip->df=0;
    return x;
    }
    else if(exp>=52){
    ip->df=x;
    return 0.0;
    }
    else{
    exp+= 12;
    msk_byte=(exp>>3);
    ip->ub[msk_byte] &= 0xff<<(8-(exp & 0x7));
    while(msk_byte<7){
        ip->ub[++msk_byte]=0;
    }
    return x-ip->df;
    }
}
