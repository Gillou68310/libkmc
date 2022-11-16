/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int puts(char *s)
*/

#include "_kmclib.h"
#include <stdio.h>


puts(s)
char *s;
{
    while(*s) {
        putchar(*s++);
    }
    putchar('\n');
    return 0;
}
