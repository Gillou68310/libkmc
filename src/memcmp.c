/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int memcmp(void *s1, void *s2, size_t n);

*/

#include "_kmclib.h"
#include <memory.h>

int memcmp(s1,s2,n)
REG1 void *s1;
REG2 void *s2;
REG3 size_t n;
{
    REG4 int d;
#if FAST_SPEED /* { */
    size_t n1;

    if (n==0) return 0;
    if (((char *)s1-(char *)s2)&BUS_ERR_ALLIGN) {
    while(n--) {
        d= *((unsigned char *)s1)++ - *((unsigned char *)s2)++;
        if (d) return d;
        }
    return 0;
    }


    if ((int)s1&1) {
        d=*((UBYTE *)s1)++ - *((UBYTE *)s2)++;    /* ALLIGN 16bit */
    if (d) return d;
        --n;
    }
    if (n>=2) {
    if ((int)s1&2) {
        d= *((UWORD *)s1)++ - *((UWORD *)s2)++;    /* ALLIGN 32bit */
        if (d) return d;
        n -= 2;
    }
    }
    n1=n;
    n = n>>2;
    while(n--) {
        d= *((UDWORD *)s1)++ - *((UDWORD *)s2)++;    /* 32bit copy */
    if (d) return d;

    }
    if ((int)n1&2) {
        d= *((UWORD *)s1)++ - *((UWORD *)s2)++;
    if (d) return d;
    }
    if ((int)n1&1) {
        d= *(UBYTE *)s1 - *(UBYTE *)s2;
    if (d) return d;
    }
#else /* }{ */
    while(n--) {
    d= *((unsigned char *)s1)++ - *((unsigned char *)s2)++;
    if (d) return d;
    }
#endif /* } */
    return 0;
}

