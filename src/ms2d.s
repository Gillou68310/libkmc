/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

    .include    "mips_as.h"
.text
    .align 4
/*
    float -> double
*/


.globl __extendsfdf2
__extendsfdf2:
    .if    FPU
    subu    $sp,$sp,8
    s.s    $f12,0($sp)
    nop
    lw    $4,0($sp)
    addu    $sp,$sp,8
    .endif
    move    $3,$4
    li    $2,0x7f800000
    and    $3,$3,$2
    beq    $3,$0,Zero_ret
    sltu    $25,$3,$2
    beq    $25,$0,Big_ret
    move    $2,$4
    li    $25,0x7fffffff
    and    $2,$2,$25 /* $2 = (exponent + argument) */
    srl    $2,$2,3         /* $2 = (exponent + argument) >> 3 */
    li    $25,0x38000000
    addu    $2,$2,$25 /* $2 += 0x380[0x3ff-0x7f] (exponent adjust) */
    move    $3,$4
    sll    $3,$3,29    /* $3 = argument << (32-3) */
    li    $25,0x80000000
    and    $4,$4,$25
    or    $2,$2,$4    /* $2 |= code[$4] */
    j    $31

Zero_ret:
    xor    $2,$2,$2
    xor    $3,$3,$3
    j    $31

Big_ret:
    li    $25,0x80000000
    and    $4,$4,$25
    li    $2,0x7ff00000
    or    $2,$2,$4        /* code[$4] */
    xor    $3,$3,$3
    j    $31
