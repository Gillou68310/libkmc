/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int _putw(int c)
*/

#include "_kmclib.h"
#include <stdio.h>



_putw(c)
int c;
{
    char *p;
    p= (char *)&c;        /* for both endian */
    putchar(*p++);
    putchar(*p);
    return c;
}
