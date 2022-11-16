/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*

    size_t     strspn(char *s1, char *s2)

*/

#include "_kmclib.h"
#include <string.h>


#if FAST_SPEED /* { */
size_t strspn(s1,s2)
const char *s1;
const char *s2;
{
    REG1 unsigned char *p;
    REG2 unsigned char c;
    REG3 size_t i;
    int tbuf[256/sizeof(int)];
    char *tbl= (char* )tbuf;
    
    for(p=tbl,i=0;i<256/sizeof(int);++i) *((int *)p)++ = 0;
    for(p=(char *)s2;*p;++p) {
        tbl[*p] = 1;
    }

    p=(char *)s1;
    for(i=0;(c=*p)!=0;++p,++i) {
    if (tbl[c]==0) return i;
    }
    return i;
}

#else /* }{ Normal */

size_t strspn(s1,s2)
const REG4 char *s1;
const char *s2;
{
    REG1 char c;
    REG2 char c1;
    REG3 char *p;
    size_t index;

    for(index=0;(c=*s1)!=0;++s1,++index) {
    for(p=(char *)s2;(c1= *p)!=0;++p) {
        if(c == c1) goto found;
    }
    return index;
found:
;
    }
    return index;
}
#endif /* } */

    
    
