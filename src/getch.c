/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int getch(void)
*/

#include "_kmclib.h"
#include <conio.h>

int getch()
{
    int c;
    while(_keybuf ==0) {
    _keybuf= _pt_key();
    }
    while((_pt_key() & 0xff) != 0);

    c= _keybuf;
    _keybuf=0;
    return c;
}
