/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void _m_init(void * start,size_t size)
    initialization of the heep (malloc related)
*/

#include "_kmclib.h"
#include <_malloc.h>
#include <stdlib.h>
#include <memory.h>

struct mem_hdr *_heep_start;        /* heep start header */


/* initialization of the memory management variable */
void _m_init(start,size)
void *start;            /* heep start address */
size_t size;            /* heep largest size  */
{
    REG1 struct mem_hdr *p;
    void *sp;
    size_t si;
    
    sp= (void *)(((size_t)start+MH_SIZE-1)&(~(MH_SIZE-1)));    /* 16byte boundary */

    _heep_start=sp;
    si = size-((size_t)sp-(size_t)start);
    si = (si+MH_SIZE-1)&(~(MH_SIZE-1));
    p=sp;
    p->size = si | 1;                    /* free */
    p->prev = NULL;
    p->next = NULL;
}



