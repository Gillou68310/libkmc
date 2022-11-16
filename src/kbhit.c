/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int kbhit(void)
*/

#include "_kmclib.h"
#include <conio.h>

unsigned char _keybuf;    /* key buffer */

int kbhit()
{
    if (_keybuf ==0) {
    _keybuf= _pt_key();
    }
    return _keybuf;
}


