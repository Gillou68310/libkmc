/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    long strtol(const char *s,char **endptr,int radix);
*/

#include "_kmclib.h"
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

#include "ctype.h"

static int _cval(c)
int c;
{
    if(isdigit(c)) return (c-'0');
    if(isalpha(c)) return (toupper(c)-'A'+10);
    return 37;

}

unsigned long strtoul(const char *s,char **endptr,int radix)
{
    return (unsigned long)strtol(s,endptr,radix);
}

long strtol(s,endptr,radix)
REG1 const char *s;
char **endptr;
int radix;
{
    long val;
    REG2 int d;
    char sign;

    val=0L;

    if(radix>=36 || radix==1 || radix <0){
    if(endptr != NULL) *endptr = (char *)s;
    return 0;
    }

    while(isspace(*s)) s++;
    if((sign=*s)=='-' || sign=='+') s++;

    if(radix==0){
    if(*s=='0') radix = ((toupper(*(s+1))=='X')?16:8);
    else radix=10;
    }
    if((radix==16) && (*s=='0') && (toupper(*(s+1))=='X')) s+=2;

    {
    while((d=_cval(*s++))<radix){
/*
        if(val>(LONG_MAX/radix)){
        errno=ERANGE;
        val=LONG_MAX;
        break;
        }
*/
        val*=radix;
/*
        if(d>(LONG_MAX-val)){
        errno=ERANGE;
        val=LONG_MAX;
        break;
        }
*/
        val+=d;
    }
    if(endptr!=NULL) *endptr = (char *)s-1;
    }

    if(sign=='-') val = -val;
    return val;
}


