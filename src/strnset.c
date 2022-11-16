/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strnset(char *dest, int ch,_size_t maxlen)

*/

#include "_kmclib.h"
#include <string.h>


#if FAST_SPEED /* { */

char *strnset(dest,ch,maxlen)
char *dest;
int ch;
size_t maxlen;
{
    REG3 UDWORD c;
    REG1 UDWORD da;
    REG2 char *d;

    c = (ch&0xff);
    
    d=dest;
    while((int)d&3) {            /* Allign 32bit */
    if ((maxlen-- ==0) || (*d == 0)) return dest;
    *d++ = c;
    }
    c |= c<<8;
    c |= c<<16;

    while(maxlen>=4) {
        da = *(UDWORD *)d;
        if ((char)da==0 || (da&0xff00)==0 ||
            (da&0xff0000)==0 || (da&0xff000000)==0) break;
        *((UDWORD *)d)++ = c;
    maxlen -= 4;
    }
    while(*d && maxlen--) {
        *d++ = c;
    }
    
    return dest;
}

#else /* }{ Normal */

char *strnset(dest,c,maxlen)
char *dest;
REG3 int c;
REG2 size_t maxlen;
{
    REG1 char *d;
    d=dest;
    while(*d && maxlen--) {
        *d++ = c;
    }
    return dest;
}

#endif /* } */


