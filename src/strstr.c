/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*

    char *strstr(char *s1, char *s2)

*/

#include "_kmclib.h"
#include <string.h>


char *strstr(s1,s2)
const char *s1;
const char *s2;
{
    REG4 char *s21;
    REG3 char *s11;
    REG1 char c1;
    REG2 char c2;
    
    for(;;) {
        s11 = (char *)s1;
        s21 = (char *)s2;
        for(;;) {
            if ((c2=*s21++)==0) return (char *)s1;
        if ((c1= *s11++)==0) return NULL;
            if (c1 != c2) break;
        }
        ++s1;
    }
}

    
    
