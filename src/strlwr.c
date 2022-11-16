/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strlwr(char *s);

*/

#include "_kmclib.h"
#include <string.h>

#include "ctype.h"


char *strlwr(s1)
char *s1;
{
    REG1 char *s;
    REG2 char c;
    s=s1;
    while((c= *s)!=0) {
        *s++ = tolower(c);
    }
    return s1;
}


    
    
