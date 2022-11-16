/*
    Copyright (c) 1995,1996 by Kiyoto Micro Copmuter Co. Ltd.
    All Rights Reserved.
*/

#include <stdlib.h>

void abort()
{
    asm(".word    0x0000000d");    /* debugger break (illegal instruction) */
    for(;;) ;
}
