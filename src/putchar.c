/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int putchar(int c)
*/

#include "_kmclib.h"
#include <conio.h>
#include <stdio.h>

/*
Define the number of characters(except 0) of the buffer in BUF.  In this case, the putchar
buffers the data for these characters by setting a screen output that can be done at high
speed.  The screen won't be updated until either the buffer becomes full or the \n 
outputs.
If 0 is defined in BUF, it doesn't buffer.
*/


/**/#define BUF 0

#if BUF
static char _pt_putchar_buf[BUF+1];
static unsigned _buf_idx;
#endif

putchar(c)
int c;
{
#if BUF==0
    if (c=='\n') {
        putch('\r');
    }
    putch(c);
    return c;
#endif
#if BUF
    if (c==0) return c;
    if (c=='\n') putchar('\r');
    _pt_putchar_buf[_buf_idx++]=c;
    if (c=='\n' || (_buf_idx==BUF)) {
    _pt_putchar_buf[_buf_idx]=0;
    _pt_puts(_pt_putchar_buf);
    _buf_idx=0;
    }
    return c;
#endif
}


