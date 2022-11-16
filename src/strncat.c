/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strncat(char *dest, char *src,size_t maxlen);

*/

#include "_kmclib.h"
#include <string.h>


char *strncat(dest,src,maxlen)
char *dest;
const REG2 char *src;
REG3 size_t maxlen;
{
    REG1 char * d;

    if (maxlen==0) return dest;
    d = dest + strlen(dest);
    while( (*d++ = *((char *)src)++ ) != '\0') {
    if(--maxlen ==0) {
        *d = '\0';
        break;
    }
    }
    return dest;
}



    
    
