/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *stpcpy(char *dest, char *src);

*/

#include "_kmclib.h"
#include <string.h>


char *stpcpy(REG1 char *dest,REG2 const char *src)
{
#if FAST_SPEED    /* { */
    UDWORD data;

    if (((char *)src-(char *)dest)&BUS_ERR_ALLIGN) {
    while( (*((char *)dest)++ = *((char *)src)++ ) != '\0');
    return --dest;
    }

    while((int)dest&3) {            /* ALLIGN 32bit */
        if ((*((BYTE *)dest)++ = *((BYTE *)src)++)==0) {
            return --dest;
    }
    }


    for(;;) {
        data= *((DWORD *)src)++;        /* 32bit copy */
    if ((data&0xff000000)==0) {
        *dest = 0;
        return dest;
    }
    if ((data&0xff0000)==0) {
        *(WORD *)dest = data>>16;
        return dest+1;
    }
    if ((data&0xff00)==0) {
        *((WORD *)dest)++ = data>>16;
        *dest=0;
        return dest;
    }
    *((DWORD*)dest)++ = data;
    if ((data & 0xff)==0) return dest-1;
    }


#else /* }{ */
    while( (*((char *)dest)++ = *((char *)src)++ ) != '\0');
    return --dest;
#endif /* } */
}


    
    
