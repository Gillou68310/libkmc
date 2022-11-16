/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    ldiv_t ldiv(long numerator,long denominator)
*/

#include "_kmclib.h"
#include <stdlib.h>

ldiv_t ldiv(n,d)
long n;
long d;
{
    static ldiv_t x;

    x.quot = n / d;
    x.rem = n % d;
    return x;
}

