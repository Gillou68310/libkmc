/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strchr(char *s, int c);

*/

#include "_kmclib.h"
#include <string.h>


char *strchr(const char *src,REG2 int c)
{
    REG1 char *s;
    REG3 char d;
#if FAST_SPEED /* { */
    REG1 DWORD c1;

    s=(char *)src;
    while((int)s & 3) {            /* Allign 32bit */
    if ((d= *s) == (char)c) return s;
    if (d==0) return NULL;
    ++s;
    }
    c1 = c & 0xff;
    c1 |= c1<<8;
    c1 |= c1<<16;            /* dup 32bit */

    for(;;) {
        REG3 DWORD d,d1;
        d= *(DWORD *)s;
    d1 = d ^ c1;
    if ((d1 &0xff000000)==0) return s;
    if ((d & 0xff000000) ==0) return NULL;
    if ((d1 &0xff0000)==0) return s+1;
    if ((d & 0xff0000) ==0) return NULL;
    if ((d1 &0xff00)==0) return s+2;
    if ((d & 0xff00) ==0) return NULL;
    if ((d1 &0xff)==0) return s+3;
    if ((d & 0xff) ==0) return NULL;
    s += 4;
    }
#else /* }{ */
    s=(char *)src;
    for(;;) {
    if ((d= *s) == (char)c) return s;
    if (d==0) return NULL;
    ++s;
    }
#endif /* } */
}



    
    
