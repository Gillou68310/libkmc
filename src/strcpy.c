/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strcpy(char *dest, char *src);

*/

#include "_kmclib.h"
#include <string.h>

char *strcpy(dest,src)
char *dest;
REG2 char *src;
{
#if FAST_SPEED
    REG1 char * d;
    UDWORD data;


    d=dest;
    if (((char *)src-(char *)d)&BUS_ERR_ALLIGN) {
    while( (*((char *)d)++ = *((char *)src)++ ) != '\0');
    return dest;
    }

    while((int)d&3) {            /* ALLIGN 32bit */
        if ((*((BYTE *)d)++ = *((BYTE *)src)++)==0) {
            return dest;
    }
    }


    for(;;) {
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


#else
    REG1 char * d;
    d=(char *)dest;
    while( (*((char *)d)++ = *((char *)src)++ ) != '\0');
    return dest;
#endif
}


    
    
