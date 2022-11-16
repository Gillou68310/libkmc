/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    long labs(l)
*/

#include "_kmclib.h"
#include <stdlib.h>

long labs(l)
long l;
{
    return (l>=0L ? l : -l);
}

