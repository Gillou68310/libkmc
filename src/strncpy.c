/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strncpy(char *dest, char *src,size_t maxlen);

*/

#include "_kmclib.h"
#include <string.h>

#if FAST_SPEED /* { */
char *strncpy(dest,src,maxlen)
char *dest;
const REG3 char *src;
size_t maxlen;
{
    REG1 char * d;
    REG2 UDWORD data;
    size_t m;

    d=dest;
    if (((char *)src-(char *)d)&BUS_ERR_ALLIGN) {
epilogue:
    while( maxlen--) {
            if ((*d++ = *src++ ) == '\0') break;
    }
        return dest;
    }

    while((int)d&3) {            /* ALLIGN 32bit */
    if (maxlen-- == 0) return dest;
        if ((*((BYTE *)d)++ = *((BYTE *)src)++)==0) {
            return dest;
    }
    }

    m = maxlen >> 2;
    while(m--){
        data= *((DWORD *)src)++;        /* 32bit copy */
    if ((data&0xff000000)==0) {
        *d = 0;
        return dest;
    }
    if ((data&0xff0000)==0) {
        *(WORD *)d = data>>16;
        return dest;
    }
    if ((data&0xff00)==0) {
        *((WORD *)d)++ = data>>16;
        *d=0;
        return dest;
    }
    *((DWORD*)d)++ = data;
    if ((data & 0xff)==0) return dest;
    }
    maxlen &= 3;
    goto epilogue;
}

#else /* }{ Normal Speed */


char *strncpy(dest,src,maxlen)
char *dest;
const REG2 char *src;
REG3 size_t maxlen;
{
    REG1 char * d;
    d=(char *)dest;
    while( maxlen--) {
        if ((*d++ = *src++ ) == '\0') break;
    }
    return dest;
}
#endif /* } */

