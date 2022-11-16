/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    char *cgets(char *s)
*/

#include "_kmclib.h"
#include <conio.h>

_bs_dsp()
{
    _pt_dsp('\b');
    _pt_dsp(' ');
    _pt_dsp('\b');
}

_col(s)
char *s;
{
    int col;
    char c;
    col=0;
    while((c=*s++)!=0) {
        ++col;
        if (c=='\t') {
        while(col&7) {
        ++col;
        }
    }
    }
}



int __xgets(max,s)
char *s;
int max;
{
    int in,col,colx;
    char *p;
    char c;

    col=in=0;
    p=s;
    for(;;) {
    *p = '\0';
    c=getch();
        if (max==in+1) {    /* buffer full (wait CR) */
        if (c=='\b') goto bs;
        if (c=='\r') break;
        else continue;
    }
    if (c=='\r') break;
    else if (c=='\t') {
        *p++ =c;
        ++in;
        c=' ';
        putch(c);
        ++col;
        while(col&7) {
            putch(c);
        ++col;
        }
        continue;
    }
    else if (c=='\b') {        /* BS */
bs:
        if (in) {
            --in;
            --p;
        c= *p;
        *p='\0';
            _bs_dsp();
            --col;
            if (c=='\t') {
                colx=_col(s+2);
                while(colx!=col) {
            _bs_dsp();
            --col;
            }
            }
        }
        continue;
    }
    putch(c);
    *p++ = c;
    ++in;
    ++col;
    }
    return in;
}


char *cgets(s)
char *s;
{
    int max,num;
    max= *(unsigned char *)s;

    if (max==0) {
        num=0;
    }
    else  num=__xgets(max,s+2);
    *(s+1)=num;
    return s+2;
}

