/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*

    char *strdup(char *s)

*/

#include "_kmclib.h"
#include <string.h>
#include <stdlib.h>


char *strdup(s)
const char *s;
{
    int i;
    char *p;
    i=strlen(s)+1;
    p= (char *)malloc(i);
    if (p) memcpy(p,s,i);
    return p;
}

    
    
