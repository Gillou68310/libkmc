/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int cputs(char *s)
*/

#include "_kmclib.h"
#include <conio.h>

int cputs(s)
char *s;
{
    int c;
    _pt_puts(s);
    c=0;
    while(*s) {
        c= *s++;
    }
    return c;
}
