/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int stricmp(char *s1, char *s2);

*/

#include "_kmclib.h"
#include <string.h>
#include "ctype.h"        /* use the macro version toupper */

int stricmp(s1,s2)
const REG4 char *s1;
const REG5 char *s2;
{
    REG3 int d;
    REG1 unsigned char c1;
    REG2 unsigned char c2;
    for(;;) {
    c1= *(unsigned char *)s1;
    c2= *(unsigned char *)s2;
    d=toupper(c1)-toupper(c2);
    if (d || c1==0) return d;
    ++s1;
    ++s2;
    }
    return 0;
}

