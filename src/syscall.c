/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

int __syscall(fnc,para)
int fnc;
int para;
{
    register int retval;

/* process to pass the value from C to the assembler */
    asm(".set noat");
    asm("move    $1,%0"::"r"(fnc));
    asm("move    $2,%0"::"r"(para));

/* assembler processing unit */
    asm(".globl __sysc_et");
    asm("__sysc_et:");
    asm("nop");        /* becomes a system call entry */
            /* being processed by the PARTNER‚ and returned value enters d0 */

/* process to return the value from the assembler to C */
    asm("move    %0,$1":"=r"(retval):);
    return retval;
}

_pt_dsp(c)
char c;
{
    __syscall(0xfe00,c);
}

_pt_key()
{
    return __syscall(0xfe01);
}

_pt_puts(str)
char *str;
{
    __syscall(0xfe02,str);
}
