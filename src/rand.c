/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    int rand(void);
*/
#include "_kmclib.h"
#include <stdlib.h>

static long next;

int rand()
{
/*   long next; */

    next = next * 1103515245 + 12345;
    return ((unsigned int)((next+1)>>16) & RAND_MAX);

    return 0;
}

void srand(seed)
unsigned seed;
{
   next = seed;
}

