/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *strcat(char *dest, char *src);

*/

#include "_kmclib.h"
#include <string.h>


char *strcat(dest,src)
REG3 char *dest;
const REG4 char *src;
{
    REG1 char * d;
#if FAST_SPEED /* { */
    REG2 UDWORD data;

    d=(char *)dest;
    while((int)d&3) {            /* ALLIGN 32bit */
        if (*d == '\0') goto find;
    ++d;
    }
    for(;;) {
        data= *((UDWORD *)d);
        if ((data & 0xff000000)==0) break;
        if ((data & 0xff0000)==0) {
            ++d;
            break;
        }
        if ((data & 0xff00)==0) {
            d += 2;
            break;
        }
        if ((data & 0xff)==0) {
            d += 3;
            break;
        }
        d+=4;
    }

find:
    strcpy(d,src);

#else /* }{ */
    d=(char *)dest;
    while(*d) ++d;
    while( (*((char *)d)++ = *((char *)src)++ ) != '\0');
#endif /* } */
    return dest;
}



    
    
