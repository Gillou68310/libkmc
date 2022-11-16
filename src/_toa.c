/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *_toa(unsigned long val,char *s,int radix);
*/

#include "_kmclib.h"

char *_toa(val,s,radix)
unsigned long val;
REG1 char *s;
int radix;
{
    REG2 char rem;

    rem=val%radix;
    if((val/=radix) != 0) s = _toa(val,s,radix);
    *s = (rem<10) ? (rem+'0') : (rem-10+'a');
    return s+1;
}
