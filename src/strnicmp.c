/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int strnicmp(char *s1, char *s2,size_t maxlen);

*/

#include "_kmclib.h"
#include <string.h>
#include "ctype.h"        /* use the macro version toupper */

int strnicmp(s1,s2,maxlen)
REG4 const char *s1;
REG5 const char *s2;
size_t maxlen;
{
    REG3 int d;
    REG1 unsigned char c1;
    REG2 unsigned char c2;
    while(maxlen--) {
    c1= *(unsigned char *)s1;
    c2= *(unsigned char *)s2;
    d=toupper(c1)-toupper(c2);
    if (d || c1==0) return d;
    ++s1;
    ++s2;
    }
    return 0;
}

