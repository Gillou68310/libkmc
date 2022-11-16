/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int ungetch(int c)
*/

#include "_kmclib.h"
#include <conio.h>

int ungetch(c)
int c;
{
    if (_keybuf) return EOF;
    _keybuf=c;
}


