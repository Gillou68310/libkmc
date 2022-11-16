/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

#include "_kmclib.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <explog.h>


#define SCAN_BUF_SIZE    0x80

#define    getc(x) scan_getc()
#define FILE char

static char *bufp_et;        /* sacnf buffer base */
static int buf_ct;        /* sacnf pointer counter */
static unsigned scanf_et;    /* 0.. sscanf , 1.. scanf , 2.. cscanf */
static back_ct;            /* scanf back pointer counter */

static char scan_getc()
{
    char c;
    char *bp;

    if(scanf_et==0){
    if((c=*(bufp_et++))=='\0'){
        --bufp_et;
        c=EOF;
    }
    return c;
    }
    bp=bufp_et+buf_ct;
    if(back_ct==0){
    c=(scanf_et==1 ? getchar():getch());
    *bp=c;
    }
    else{
    c=*bp;
    --back_ct;
    }
    buf_ct = (buf_ct+1) & ~(SCAN_BUF_SIZE-1);
    return c;
}

static back_file(FILE *fp,int n)
{
    unsigned b0,b1;

    if(scanf_et==0){
    bufp_et -= n;
    return;
    }
    else if(n<=SCAN_BUF_SIZE){
    back_ct=n;
    buf_ct = (buf_ct-n) & ~(SCAN_BUF_SIZE-1);
    }
    return;
}


static int val_ok;

#if FLOAT_LLONG_ON /* { */

double strtod(const char *s,char **endptr)
{
    double val;
    double n;
    double *tbl;
    int exp;
    int minus;
    int msk;
    extern double _div_data[];
    extern double _mul_data[];

    while(isspace(*s)) ++s;
    minus=0;
    val_ok=0;
    val=0.0;
    if(*s=='-'){
    minus=1;
    s++;
    }
    else if(*s=='+'){
    ++s;
    }
    if(isdigit(*s)){
    val_ok=1;
    val= *(s++)-'0';
    while(isdigit(*s)){
        val *= 10.0;
        val += *(s++)-'0';
    }
    }
    if(*s=='.'){
    ++s;
    n=0.1;
    if(isdigit(*s)){
        val_ok=1;
        val += (*(s++)-'0')*n;
        while(isdigit(*s)){
        n *= 0.1;
        val += (*(s++)-'0')*n;
        }
    }
    }
    if(val_ok==0) goto strtod_ret;
    if(toupper(*s)=='E'){
    s++;
    if(*s=='-'){
        minus |= 2;
        ++s;
    }
    else if(*s=='+'){
        ++s;
    }
    if(isdigit(*s)==0) goto strtod_ret;
    exp= *(s++)-'0';
    while(isdigit(*s)){
        exp *= 10;
        exp += *(s++)-'0';
    }
    if(minus & 2){
        if(exp>=512){
        val=0.0;
        goto strtod_ret;
        }
        tbl=_mul_data+8;
    }
    else{
        if(exp>=512){
        val=1e1000;
        goto strtod_ret0;
        }
        tbl=_div_data+8;
    }
    msk=0x100;
    do{
        if(exp & msk){
        val *= *tbl;
        }
        --tbl;
        msk >>= 1;
    }while(msk) ;
    }
strtod_ret0:
    if(minus & 1){
    val = -val;
    }
strtod_ret:
    if(endptr!=0){
    *endptr=(char *)s;
    }
    return val;
}

double atof(const char *s)
{
    return strtod(s,NULL);
}

#endif /* } */

static int n_ct;
static int v_len;
static int minus;


static int scanf_sign(FILE *fp)
{
    int  c;

    while(isspace(c=getc(fp))) ++n_ct;
    if(c==EOF) return EOF;
    ++v_len;
    if(c=='-'){
    minus=1;
    }
    else if(c!='+'){
    return c;
    }
    c=getc(fp);
    ++v_len;
    return c;
}

static int isodigit(int c)
{
    return (c>='0' && c<='7');
}

#define SCANF_INT    1
#define SCANF_LLONG    2
#define SCANF_FLOAT    4
#define SCANF_DOUBLE    8
#define SCANF_SKIP    0x10

#define SCANF_HFLG    0x20
#define SCANF_LFLG    0x40
#define SCANF_LLFLG    0x80
#define SCANF_USRSTR    0x100
#define SCANF_CHAR    0x100

int vfscanf (FILE *fp,const char *f,va_list argp)
{
    int cf,c;
    int scanf_ct;
    int sign;
    int width;
    int v_mode;
    char *p;
#if FLOAT_LLONG_ON /* { */
    union{
    unsigned long long l;
    double    d;
    } val;
#else /* }{ */
    union{
    unsigned long l;
    } val;
#endif /* } */
    extern char _asc_buf[];

    scanf_ct=n_ct=0;
    for(;;){
    if((cf=*(f++))!='%'){
        if(cf=='\0'){
        return scanf_ct;
        }
        if(isspace(cf)){
        while(isspace(c=getc(fp))) ++n_ct;
        if(c==EOF) return EOF;
        back_file(fp,1);
        }
        else{
        if(iskanji(cf)){
            if(cf!=getc(fp)){
            back_file(fp,1);
              return scanf_ct;
            }
            ++n_ct;
            cf=*(f++);
        }
char_chk:
        if(cf!=getc(fp)){
            back_file(fp,1);
              return scanf_ct;
        }
        ++n_ct;
        }
    }
    else{
        sign=0;
        minus=0;
        v_len=0;
        v_mode=SCANF_INT;
        width=0x7fffffff;
/* scanf width */
        if((cf=*(f++))=='*'){
        cf=*(f++);
        v_mode |= SCANF_SKIP;
        }
        if(isdigit(cf)){
        width= cf-'0';
        cf=*(f++);
        while(isdigit(cf)){
            width=width*10+(cf-'0');
            cf=*(f++);
        }
        }
        val.l=0;
scanf_loop:
        switch(cf){
        case 'i':
        case 'd':
        case 'u':
        case 'U':
        c=scanf_sign(fp);
        if(c==EOF) return EOF;
        if(v_len>width) goto width_over;
        if(isdigit(c)==0) goto back_ret;
        if(c=='0'){
            c=getc(fp);
            ++v_len;
            if(toupper(c)=='X'){
            c=getc(fp);
            ++v_len;
            goto scanf_hex;
            }
            if(isodigit(c)==0){
            back_file(fp,1);
            val.l=0;
            break;
            }
            goto scanf_oct;
        }
        val.l=c-'0';
        for(;;){
            if(v_len>=width) break;
            if((c=getc(fp))==EOF) break;
            if(isdigit(c)==0){
            back_file(fp,1);
            break;
            }
            ++v_len;
            val.l=val.l*10+c-'0';
        }
        break;
        case 'x':
        case 'X':
        case 'p':
        c=scanf_sign(fp);
        if(c==EOF) return EOF;
scanf_hex:
        if(v_len>width) goto width_over;
        if(isxdigit(c)==0) goto back_ret;
        for(;;){
            int hex;

            if(isdigit(c)){
            hex=c-'0';
            }
            else{
            hex=toupper(c)-'A'+10;
            }
            val.l= (val.l<<4) + hex;
            if(v_len>=width) break;
            if((c=getc(fp))==EOF) break;
            if(isxdigit(c)==0){
            back_file(fp,1);
            break;
            }
            ++v_len;
        }
        break;
        case 'o':
        c=scanf_sign(fp);
        if(c==EOF) return EOF;
scanf_oct:
        if(v_len>width) goto width_over;
        if(isodigit(c)==0) goto back_ret;
        val.l=c-'0';
        for(;;){
            if(v_len>=width) break;
            if((c=getc(fp))==EOF) break;
            if(isodigit(c)==0){
            back_file(fp,1);
            break;
            }
            ++v_len;
            val.l=(val.l<<3)+c-'0';
        }
        break;
#if FLOAT_LLONG_ON /* { */
        case 'g':
        case 'G':
        case 'e':
        case 'E':
        case 'f':
        {
            char *p,*q;
            char bak_flg;

            p=_asc_buf;
            bak_flg=0;
            for(;;){
            ++v_len;
            switch(c=getc(fp)){
            case '+':
            case '-':
            case 'E':
            case 'e':
            case '.':
                *(p++)=c;
                break;
            case EOF:
                if(p==_asc_buf){
                return EOF;
                }
                --v_len;
                goto scan_next;
            default:
                if(isdigit(c)){
                *(p++)=c;
                break;
                }
                if(p==_asc_buf){
                if(isspace(c)){
                    --v_len;
                    ++n_ct;
                    break;
                }
                goto back_ret;
                }
                bak_flg=1;
                --v_len;
                goto scan_next;
            }
            if(v_len>=width) break;
            if(v_len>ABUFSIZE-1) break;
            }
scan_next:
            *p='\0';
            val.d=strtod(_asc_buf,&q);
            back_file(fp,p-q+bak_flg);
            if(val_ok==0){
            return scanf_ct;
            }
            if(v_mode & (SCANF_LLFLG | SCANF_LFLG)){
            v_mode=SCANF_DOUBLE;
            }
            else{
            v_mode=SCANF_FLOAT;
            }
        }
        break;
#endif /* } */
        case '[':
        {
            unsigned char cf0,cf1;
            int chk;

            chk=1;
            if((cf=*(f++))=='^'){
            chk=0;
            cf=*(f++);
            }
            memset(_asc_buf,chk ^ 1,256);
            while(cf!=']'){
            if(cf=='\0') return scanf_ct;
            cf0=cf;
            if((cf=*(f++))=='-'){
                cf1=cf=*(f++);
                if(cf1<cf0){
                cf1=cf0;
                cf0=cf;
                }
                while(cf0!=cf1){
                _asc_buf[cf0++]=chk;
                }
                cf=*(f++);
            }
            _asc_buf[cf0]=chk;
            }
            v_mode |= SCANF_USRSTR;
            c=getc(fp);
        }
        case 's':
        {
            if((v_mode & (SCANF_USRSTR | SCANF_CHAR))==0){
            while(isspace(c=getc(fp))) ++n_ct;
            }
scanf_str:
            if(c==EOF) return EOF;
            if((v_mode & SCANF_SKIP)==0){
            p=va_arg(argp,char *);
            }
            if(width==0){
            back_file(fp,1);
            }
            else{
            for(;;){
                if((v_mode & SCANF_SKIP)==0){
                    *(p++)=c;
                }
                ++v_len;
                if(--width==0) break;
                if((c=getc(fp))==EOF) break;
                if(c=='\0') break;
                if((v_mode & (SCANF_USRSTR | SCANF_CHAR))==0){
                if(isspace(c)){
                    back_file(fp,1);
                    break;
                }
                }
                else if(v_mode &  SCANF_USRSTR){
                if(_asc_buf[(unsigned char)c]==0){
                    back_file(fp,1);
                    break;
                }
                }
            }
            }
            if((v_mode & SCANF_SKIP)==0){
            *p='\0';
            }
        }
        v_mode |= SCANF_SKIP;
        break;
        case 'c':
        if(width==0x7fffffff){
            width=1;
        }
        c=getc(fp);
        goto scanf_str;
        case 'n':
        *va_arg(argp,int *)=n_ct;
        v_mode |= SCANF_SKIP;
        break;
        case 'h':
        v_mode |= SCANF_HFLG;
        cf=*(f++);
        goto scanf_loop;
        case 'l':
        if(*f=='l'){
            v_mode |= SCANF_LLFLG;
        }
        else{
            v_mode |= SCANF_LFLG;
        }
        cf=*(f++);
        goto scanf_loop;
        default:
        return scanf_ct;
        }
        n_ct += v_len;
        ++scanf_ct;
        if((v_mode & SCANF_SKIP)==0){
        if(v_mode & SCANF_INT){    /* int */
             if(minus){
            val.l = -val.l;
             }
             if((v_mode & SCANF_LLFLG)==0){
            if(v_mode & SCANF_HFLG){
                *va_arg(argp,short int *)=(short int)val.l;
            }
            else{
                *va_arg(argp,int *)=val.l;
            }
            }
            else{
#if FLOAT_LLONG_ON /* { */
            *va_arg(argp,long long *)=val.l;
#endif /* } */
            }
        }
#if FLOAT_LLONG_ON /* { */
        else if(v_mode & SCANF_DOUBLE){    /* double */
            *va_arg(argp,double *)=val.d;
        }
        else if(v_mode & SCANF_FLOAT){
           *va_arg(argp,float *)=(float)val.d;
        }
#endif /* } */
        }
    }
    }
back_ret:
    width=v_len-1;
width_over:
    back_file(fp,v_len-width);
    return scanf_ct;
}


int scanf(const char *format, ...)
{
    char buf[SCAN_BUF_SIZE*2];
    va_list argp;

    scanf_et=1;
    bufp_et=(char *)((unsigned)(buf+SCAN_BUF_SIZE-1) & ~(SCAN_BUF_SIZE-1));
    buf_ct=back_ct=0;
    va_start(argp,format);
    return vfscanf(0,format,argp);
}

int cscanf(const char *format, ...)
{
    char buf[SCAN_BUF_SIZE*2];
    va_list argp;

    scanf_et=2;
    bufp_et=(char *)((unsigned)(buf+SCAN_BUF_SIZE-1) & ~(SCAN_BUF_SIZE-1));
    buf_ct=back_ct=0;
    va_start(argp,format);
    return vfscanf(0,format,argp);
}


int sscanf(const char *str,const char *format, ...)
{
    va_list argp;

    va_start(argp,format);
    scanf_et=0;
    bufp_et=(char *)str;
    return vfscanf(0,format,argp);
}

