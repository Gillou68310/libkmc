/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*

    char *strtok(char *s1, char *s2)

*/

#include "_kmclib.h"
#include <string.h>


char *strtok(s1,s2)
REG4 char *s1;
const char *s2;
{
    REG1 char c;
    REG2 char c1;
    REG3 char *p;
    static char *ns=NULL;
    
    if (s1==NULL) s1=ns;
    else ns=s1;
    if (s1==NULL) return s1;
    if (*s1=='\0') return NULL;

    for(;;) {
    p=strpbrk(s1,s2);
        if (p!=s1) break;
        s1++;
    }
    if (p) {
        *p = '\0';
        ns=p+1;
        return s1;
    }
    else ns=NULL;
    return s1;
}


