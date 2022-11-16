/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    void *bsearch(const void *key,const void *base,size_t n,size_t w,int (*cmp)(const void *,const void *));
*/

#include "_kmclib.h"
#include <stdlib.h>

void *bsearch(key,base,n,w,cmp)
const void *key;
const void *base;
size_t n;
size_t w;
int (*cmp)(const void *,const void *);
{
    int low;
    int high;
    int mid;
    int c;

    if(n==0) return;
    low = 0;
    high = n-1;
    while(low<=high){
    mid = (low+high)/2;
    if((c=(*cmp)(key,(char *)(base+w*mid)))<0){
        high = mid-1;
    }
    else if(c>0){
        low = mid+1;
    }
    else{
        return ((void *)(base+w*mid));
    }
    }
    return (void *)NULL;

}


