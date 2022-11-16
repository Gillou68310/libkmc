/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strrchr(char *s, int c);

*/

#include "_kmclib.h"
#include <string.h>


char *strrchr(s,c)
const REG1 char *s;
REG2 int c;
{
    REG3 char d;
#if FAST_SPEED /* { */
    REG1 DWORD c1;
    char *p;
    p=NULL;
    while((int)s & 3) {            /* Allign 32bit */
    if ((d= *(char *)s) == (char)c) p=(char *)s;
    if (d==0) return p;
    ++s;
    }
    c1 = c & 0xff;
    c1 |= c1<<8;
    c1 |= c1<<16;            /* dup 32bit */

    for(;;) {
        REG3 DWORD d,d1;
        d= *(DWORD *)s;
    d1 = d ^ c1;
    if ((d1 &0xff000000)==0) p=s;
    if ((d & 0xff000000) ==0) return p;
    if ((d1 &0xff0000)==0) p=s+1;
    if ((d & 0xff0000) ==0) return p;
    if ((d1 &0xff00)==0) p=s+2;
    if ((d & 0xff00) ==0) return p;
    if ((d1 &0xff)==0) p=s+3;
    if ((d & 0xff) ==0) return p;
    s += 4;
    }
#else /* }{ */
    char *p;
    p=NULL;
    for(;;) {
    if ((d= *(char *)s) == (char)c) p=(char *)s;
    if (d==0) return p;
    ++s;
    }
#endif /* } */
}



    
    
