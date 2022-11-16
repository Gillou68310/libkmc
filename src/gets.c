/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *gets(char *s)
*/

#include "_kmclib.h"
#include <stdio.h>

char *gets(s)
char *s;
{
    int c;
    char *p;
    p=s;
    for(p=s;;++p) {
        c=getchar();
        if (c=='\n') {
            *p='\0';
            return s;
        }
        if (c==EOF) {
            *p = '\0';
        }
        else *p=c;
        if (c==EOF) {
            if (p==s) return NULL;
            else return s;
        }
    }
}
