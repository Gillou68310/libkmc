/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *ltoa(long val,char *s,int radix);

            NOT ANSI

*/

#include "_kmclib.h"
#include <stdlib.h>

extern char *_toa(unsigned long val,char *s,int radix);

char *ltoa(val,s,radix)
long val;
char *s;
int radix;
{
    REG1 char *p;

    if(radix<2 || radix>36){
    *s = '\0';
    }
    else{
    p=s;
    if((radix==10) && val<0){
        *p++ = '-';
        val=-val;
    }
    *(_toa((unsigned long)val,p,radix)) = '\0';
    }
    return s;
}




