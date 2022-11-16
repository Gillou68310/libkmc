/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int toupper(c)
*/

#include "_kmclib.h"
#include <ctype.h>
toupper(c)
int c;
{
    return (islower(c) ? _toupper(c) : c);
}
