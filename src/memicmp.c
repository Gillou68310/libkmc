/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int memicmp(void *s1, void *s2, size_t n);

*/

#include "_kmclib.h"
#include <memory.h>
#include "ctype.h"        /* use the macro version toupper */

int memicmp(s1,s2,n)
REG1 void *s1;
REG2 void *s2;
REG3 size_t n;
{
int d;
    while(n--) {
    d= toupper(*(unsigned char *)s1) - toupper(*(unsigned char *)s2);
    if (d) return d;
    ++s1;
    ++s2;
    }
    return 0;
}

