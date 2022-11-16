/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int putch(int c)
*/

#include "_kmclib.h"
#include <conio.h>

int putch(c)
int c;
{
    int i;
    _pt_dsp(c);
/*    for(i=0;i<10000;++i) ;        /* for PARTNER-ET Wait */
    return c;
}


