/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *memcpy(void *dest, void *src, size_t n);

*/


#include "_kmclib.h"

#include <memory.h>

void *memcpy(dest,src,n)
REG5 void *dest;
REG1 void *src;
REG4 size_t n;
{
    REG2 char *d;
#if FAST_SPEED /* { */
    REG3 size_t n1;

    if (n==0) return dest;
    d=dest;
    if (((char *)src-(char *)dest)&BUS_ERR_ALLIGN) {
    while(n--) {
            *((BYTE *)d)++ = *((BYTE *)src)++;
        }
    return dest;
    }

    if ((int)d&1) {
        *((BYTE *)d)++ = *((BYTE *)src)++;    /* ALLIGN 16bit */
        --n;
    }
    if (n>=2) {
    if ((int)d&2) {
        *((WORD *)d)++ = *((WORD *)src)++;        /* ALLIGN 32bit */
        n -= 2;
    }
    }
    n1 = n>>2;
    while(n1--) {
        *((DWORD *)d)++ = *((DWORD *)src)++;        /* 32bit copy */
    }
    if ((int)n&2) *((WORD *)d)++ = *((WORD *)src)++;
    if ((int)n&1) *(BYTE *)d = *(BYTE *)src;
#else /* }{ */
    d=dest;
    while(n--) {
        *((BYTE *)d)++ = *((BYTE *)src)++;
    }
#endif /* } */
    return dest;
}


