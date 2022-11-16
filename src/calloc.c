/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *calloc(size_t n,size_t s)
    size_t n;     Element number
    size_t s;     Element size
    return: memory pointer
    
*/

#include "_kmclib.h"
#include <_malloc.h>
#include <stdlib.h>
#include <memory.h>

void *calloc(n,s)
size_t n,s;
{
    size_t bytes;
    void *p;

    bytes=n*s;
    p=malloc(bytes);
    if (p) memset(p,0,bytes);
    return p;
}
