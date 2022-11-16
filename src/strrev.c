/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strrev(char *s);

*/

#include "_kmclib.h"
#include <string.h>


char *strrev(s)
char *s;
{
    REG1 char *f;
    REG2 char *b;
    REG3 char c;

    f=s;
    b=f+strlen(f)-1;
    while(f<b) {
        c= *f;
        *f++= *b;
        *b-- = c;
    }
    return s;
}


    
    
