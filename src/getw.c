/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int _getw()
*/

#include "_kmclib.h"
#include <stdio.h>

_getw()
{
    int c,d,e;
    char *p=(char *)&e;
    c=getchar();
    if (c!=EOF) {
        d=getchar();
        if (d==EOF) c=EOF;
        else {
            *p++= c;    /* for both endian */
        *p=d;
    }
     }
     return e;
}
