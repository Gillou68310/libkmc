/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int getchar()
*/

#include "_kmclib.h"
#include <conio.h>
#include <stdio.h>

char __std_buf[BUFSIZ+2];
int __std_idx,__std_last;


getchar()
{
    int c,i;
    if (__std_idx==__std_last) {
    __std_idx=0;
     i = __xgets(BUFSIZ,__std_buf);
     __std_buf[i]='\n';
     __std_last = i+1;
     }
    c= __std_buf[__std_idx];
    if (c==0x1a) return EOF;
    else ++__std_idx;
    return c;
}

