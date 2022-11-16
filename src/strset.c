/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strset(char *dest, int ch)

*/

#include "_kmclib.h"
#include <string.h>


#if FAST_SPEED /* { */

char *strset(dest,ch)
char *dest;
int ch;
{
    REG3 UDWORD c;
    REG1 UDWORD da;
    REG2 char *d;

    c = (ch&0xff);
    
    d=dest;
    while((int)d&3) {            /* Allign 32bit */
    if (*d) *d++ = c;
    else return dest;
    }
    c |= c<<8;
    c |= c<<16;

    for(;;) {
        da = *(UDWORD *)d;
        if ((char)da==0 || (da&0xff00)==0 ||
            (da&0xff0000)==0 || (da&0xff000000)==0) break;
        *((UDWORD *)d)++ = c;
    }
    while(*d) {
        *d++ = c;
    }
    
    return dest;
}

#else /* }{ Normal */

char *strset(dest,c)
REG5 char *dest;
REG2 int c;
{
    REG1 char *d;
    d=dest;
    while(*d) {
        *d++ = c;
    }
    return dest;
}

#endif /* } */


