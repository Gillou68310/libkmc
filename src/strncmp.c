/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int strncmp(char *s1, char *s2,size_t maxlen);

*/

#include "_kmclib.h"
#include <memory.h>


int strncmp(s1,s2,maxlen)
REG4 char *s1;
REG3 char *s2;
size_t maxlen;
{
    REG1 UDWORD c,c1;
    REG2 int d,n;
#if FAST_SPEED /* { */

    if (((char *)s1-(char *)s2)&BUS_ERR_ALLIGN) {
epilogue:
    while(maxlen--) {
        c= *((unsigned char *)s1)++;
        d= c - *((unsigned char *)s2)++;
        if (d || c==0) return d;
        }
    return 0;
    }


    while ((int)s1&3) {            /* Allign 32bit */
    if (maxlen-- ==0) return 0;
    c= *((unsigned char *)s1)++;
        d= c - *((UBYTE *)s2)++;    /* ALLIGN 16bit */
    if (d || c==0) return d;
    }
    n=maxlen>>2;
    while(n--) {
    c= *((UDWORD *)s1)++;
        d= c - (c1=*((UDWORD *)s2)++);    /* 32bit cmp */
    if(d){
        if ((c & 0xff000000)==0){
        d= 0xff000000;
        }
        else if ((c&0xff0000)==0){
        d = 0xffff0000;
        }
        else if ((c&0xff00)==0){
        d= 0xffffff00;
        }
        else{
        return d;
        }
        return (int)((c & d)-(c1 & d));
    }
    if ((char)c==0 || (c&0xff00)==0 || (c&0xff0000)==0 || (c&0xff000000)==0){
        return d;
    }
    }
    maxlen &= 3;
    goto epilogue;
    
#else /* }{ */
    while(maxlen--) {
    c= *((unsigned char *)s1)++;
    d= c - *((unsigned char *)s2)++;
    if (d || c==0) return d;
    }
    return 0;
#endif /* } */
}

