/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int tolower(c)
*/

#include "_kmclib.h"
#include <ctype.h>

tolower(c)
int c;
{
    return (isupper(c) ? _tolower(c) : c);
}
