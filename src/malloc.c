/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *malloc(size_t size)
    size_t size;         byte count
    return: memory block
*/

#include "_kmclib.h"
#include <_malloc.h>
#include <stdlib.h>
#include <memory.h>

extern struct mem_hdr *_heep_start;        /* heep start header */

void _ins_block(p,size,prev,next)
struct mem_hdr *p;
struct mem_hdr *prev,*next;
size_t size;
{
    p->size=size;
    p->prev=prev;
    p->next=next;
    if (next) next->prev=p;
}


void *malloc(size)
size_t size;
{
    REG1 struct mem_hdr *p;
    struct mem_hdr *pp,*next2;
    size_t newsize,oldsize;
    

    if (size==0) return NULL;

    p=_heep_start;
    pp=NULL;
    for(;;) {
        if (p->size&1) {        /* this block is free */
            if (p->size > size) {    /* find memory block */
        oldsize=p->size & 0xfffffffe;
                newsize=(size+MH_SIZE-1)&(~(MH_SIZE-1));
        if (oldsize >= newsize+MH_SIZE) {    /* block partitioning */
                    p->size=newsize;
            next2 = p->next;
                    p->next=(struct mem_hdr *)((char *)p+newsize+MH_SIZE);
            _ins_block(p->next,oldsize-newsize-MH_SIZE,p,next2);
            free((char *)(p->next)+MH_SIZE);    /* insert block free */
        }
        else { /* no insert free block */
            p->size=oldsize;
        }
        return (void *)((char *)p+MH_SIZE);
            }
        }
    if (p->next==NULL) break;
    pp=p;
        p=p->next;
    }
    return NULL;
}

