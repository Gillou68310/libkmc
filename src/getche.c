/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int getche(void)
*/

#include "_kmclib.h"
#include <conio.h>

int getche()
{
    int c;
    while(_keybuf ==0) {
    _keybuf= _pt_key();
/*    for(c=0;c<30000;++c) ;        /* for PARTNER-ET Wait */
    }

    c= _keybuf;
    _keybuf=0;
    _pt_dsp(c);
    return c;
}


