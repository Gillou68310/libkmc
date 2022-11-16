/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    div_t div(int numerator,int denominator)
*/

#include "_kmclib.h"
#include <stdlib.h>

div_t div(n,d)
int n;
int d;
{
    static div_t x;

    x.quot = n / d;
    x.rem = n % d;
    return x;
}

