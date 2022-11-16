/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    size_t *strchr(char *s);

*/

#include "_kmclib.h"
#include <string.h>



size_t strlen(s1)
REG3 char *s1;
{
    REG2 char *s;
    s=s1;
#if FAST_SPEED /* { */
    while((int)s & 3) {            /* Allign 32bit */
    if (*s == 0) return s-s1;
    ++s;
    }
    for(;;) {
        REG1 DWORD d;
        d= *(DWORD *)s;
    if ((d & 0xff000000) ==0) return s-s1;
    if ((d & 0xff0000)==0) return s+1-s1;
    if ((d & 0xff00)==0) return s+2-s1;
    if ((d & 0xff)==0) return s+3-s1;
    s += 4;
    }
#else /* }{ */
    for(;;) {
    if (*s==0) return s-s1;
    ++s;
    }
#endif /* } */
}



    
    
