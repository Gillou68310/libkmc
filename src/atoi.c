/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int atoi(const char *s)
*/

#include "_kmclib.h"
#include <stdlib.h>

#include "ctype.h"

long atol(const char *s)
{
    return atoi(s);
}

int atoi(REG1 const char *s)
{
    REG2 int val;
    char sign,c;

    val=0;
    while(isspace(*s)) s++;
    if((sign=*s)=='-' || sign=='+') s++;
    while((c=*s++),isdigit(c)) val=val*10+(c-'0');
    if(sign=='-') val = -val;
    return val;
}


