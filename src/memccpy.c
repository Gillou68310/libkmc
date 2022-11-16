/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *memccpy(void *dest, void *src, int c, size_t n);

*/

#include "_kmclib.h"
#include <memory.h>

void *memccpy(dest,src,c,n)
REG1 void *dest;
REG2 void *src;
REG3 int c;
REG4 size_t n;
{
    while(n--) {
        if ((*((char *)dest)++ = *((char *)src)++)==(char)c) return dest;
    }
    return NULL;
}

    
