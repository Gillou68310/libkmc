/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void free(void *q)
    void *q;
*/

#include "_kmclib.h"
#include <_malloc.h>
#include <stdlib.h>
#include <memory.h>


/* put the Free Block together */

static void _add_free(p1,p2)
REG1 struct mem_hdr *p1;    /* 1st Block */
REG2 struct mem_hdr *p2;    /* 2'nd Block */
{
    struct mem_hdr *np;
    p1->size += (p2->size & 0xfffffffe)+MH_SIZE;
    np=p1->next = p2->next;
    if (np) np->prev = p1;
}


void free(q)
void *q;
{
    REG1 struct mem_hdr *m;
    REG2 struct mem_hdr *pp;
    REG3 struct mem_hdr *np;

    if (q==NULL) return;
    m=(struct mem_hdr *)((char *)q-MH_SIZE);
    pp=m->prev;
    np=m->next;
    m->size |= 1;                /* free mark */
    if (pp && (pp->size&1)) {        /* the block right before is free */
        _add_free(pp,m);
        m=pp;
    }
    if (np && (np->size&1)) {        /* the block right after is free */
        _add_free(m,np);
    }
}
