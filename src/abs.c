/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int abs(i)
*/

#include "_kmclib.h"
#include <stdlib.h>

int abs(i)
int i;
{
    return (i>=0 ? i : -i);
}

