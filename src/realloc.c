/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *realloc(void *q,size_t size)
    void *q;         memory block
    size_t size;     byte count
    return: memory block
*/

#include "_kmclib.h"
#include <_malloc.h>
#include <stdlib.h>
#include <memory.h>

static void _mk_newblk(p,size,prev,next)
struct mem_hdr *p;
struct mem_hdr *prev;
struct mem_hdr *next;
size_t size;
{
    p->size=size;
    p->next=next;
    p->prev=prev;
}



void *realloc(q,size)
void *q;
size_t size;
{
    REG1 struct mem_hdr *m;
    REG2 struct mem_hdr *p;
    size_t oldsize;
    void *qn;

    if (q==NULL) return malloc(size);    /* memory block == NULL memory allocation */
    if (size==0) {
        free(q);
        return NULL;
    }

    m= (struct mem_hdr *)((char *)q-MH_SIZE);
    if (size <= m->size) {        /* contraction or the same*/
        if (size <= m->size-MH_SIZE) {    /* possible to insert the Free block */
        size = (size+MH_SIZE-1)&(~(MH_SIZE-1));
            p= (struct mem_hdr *)((char *)m+size+MH_SIZE);
            _mk_newblk(p,m->size - size - MH_SIZE,m,m->next);
            m->next=p;
            if (p->next) p->next->prev = p;
            m->size=size;
            free((void *)((char *)p+MH_SIZE));
        }
    return q;
    }
    else {                /* expansion */
    p=m->next;
    if (p && (p->size&1)) {        /* the next block is free */
        if (size< m->size + p->size + MH_SIZE) {    /* possible to resize */
        oldsize=m->size;
            m->size=(size+MH_SIZE-1)&(~(MH_SIZE-1));
            m->next= (struct mem_hdr *)((char *)m+m->size+MH_SIZE);
            if (m->next != p->next) {    /* Free block insertion */
                _ins_block(m->next,p->size+oldsize-m->size,m,p->next);
            }
        return q;
        }
    }
    }
    qn=malloc(size);
    if (qn) {
        memcpy(qn,q,m->size);
        free(q);
    }
    return qn;
}
