/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strupr(char *s);

*/

#include "_kmclib.h"
#include <string.h>

#include "ctype.h"


char *strupr(s1)
char *s1;
{
    REG1 char *s;
    REG2 char c;
    s=s1;
    while((c= *s)!=0) {
        *s++ = toupper(c);
    }
    return s1;
}


    
    
