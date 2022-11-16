/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *memcfr(void *s, int c, size_t n);

*/

#include "_kmclib.h"
#include <memory.h>

void *memchr(s,c,n)
void *s;
int c;
size_t n;
{
#if FAST_SPEED /* { */
int n1;
    while((int)s & 3) {            /* Allign 32bit */
    if (n-- == 0) return NULL;
    if ( *(char *)s == (char)c) return s;
    ++s;
    }
    n1=n&3;
    n >>= 2;
    while(n--) {
    REG1 DWORD d;
        d= *(DWORD *)s;
    if (((char)(d>>24)) == (char)c) return s;
    if (((char)(d>>16)) == (char)c) return s+1;
    if (((char)(d>>8)) == (char)c) return s+2;
    if (((char)d) == (char)c) return s+3;
    s += 4;
    }
    while(n1--) {
    if ( *(char *)s == (char)c) return s;
    ++s;
    }

#else /* { */
    while(n--) {
        if (*((char *)s++) == (char)c) return s-1;
    }
#endif /* } */
    return NULL;
}

    
