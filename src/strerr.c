/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    strerror( int )
*/

#include "_kmclib.h"
#include <string.h>


char *_sys_errmes[] = {
    "",    /* 0 */
    "",    /* 1 */
    "",    /* 2 */
    "",    /* 3 */
    "",    /* 4 */
    "",    /* 5 */
    "",    /* 6 */
    "",    /* 7 */
    "",    /* 8 */
    "",    /* 9 */
    "",    /* 10 */
    "",    /* 11 */
    "",    /* 12 */
    "",    /* 13 */
    "",    /* 14 */
    "",    /* 15 */
    "",    /* 16 */
    "",    /* 17 */
    "",    /* 18 */
    "",    /* 19 */
    "",    /* 20 */
    "",    /* 21 */
    "",    /* 22 */
    "",    /* 23 */
    "",    /* 24 */
    "",    /* 25 */
    "",    /* 26 */
    "",    /* 27 */
    "",    /* 28 */
    "",    /* 29 */
    "",    /* 30 */
    "",    /* 31 */
    "",    /* 32 */
    "#33 Math argument",    /* 33 EDOM */
    "#34 Result too large",    /* 34 ERANGE */
    ""    /* 35 */
};

static char _errbuf[100];

char *strerror(errnum)
int errnum;
{
    if ((unsigned) errnum>36) errnum=0;
    strcpy(_errbuf,_sys_errmes[errnum]);
    return _errbuf;
}


