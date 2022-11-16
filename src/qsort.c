/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void qsort(void *b,size_t n,size_t w,int (*cmp)(const void *,const void *));
*/

#include "_kmclib.h"
#include <stdlib.h>


void _swapfnc(REG4 size_t w,REG2 char *x,REG3 char *y)
{
    REG1 char tmp;

    for(;w!=0;w--){
    tmp = *x;
    *x = *y;
    *y = tmp;
     x++;
    y++;
    }
}

void qsort(b,n,w,cmp)
void *b;
size_t n;
size_t w;
int (*cmp)(const void *,const void *);
{
    REG4 char *p;
    REG3 char *q;
    REG6 char *e;
    REG1 unsigned int g1;
    REG2 unsigned int g2;

    if(n<=1) return;
    if(n==2){
    if((*cmp)(b,b+w)>0) _swapfnc(w,b,b+w);
    return;
    }
    for(g1=1;g1<n;g1=2*g1+1);
    e = b+n*w;

    while((g1/=2) != 0){
    g2 = g1*w;
    for(p=b+g2;p<e;p+=w){
        for(q=p-g2;(unsigned)b<=(unsigned)q && (unsigned)q<(unsigned)e && (*cmp)(q,q+g2)>0;q-=g2){
        _swapfnc(w,q,q+g2);
        }
    }
    }

}

