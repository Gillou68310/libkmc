/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *ultoa(unsigned long val,char *s,int radix);

            NOT ANSI

*/

#include "_kmclib.h"
#include <stdlib.h>

extern char *_toa(unsigned long val,char *s,int radix);

char *ultoa(val,s,radix)
REG3 unsigned long val;
REG2 char *s;
REG1 int radix;
{
    if(radix<2 || radix>36){
    *s = '\0';
    }
    else{
    *(_toa((unsigned long)val,s,radix)) = '\0';
    }
    return s;
}




