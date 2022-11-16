/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

    .include    "mips_as.h"
.text
    .align 4
/*
    double->float
*/


.globl __truncdfsf2
__truncdfsf2:
    move    $2,$4
    li    $25,0x7ff00000
    and    $2,$2,$25
    li    $25,0x38100000
    sltu    $25,$2,$25
    bne    $25,$0,Zero_ret
    li    $25,0x47f00000
    sltu    $25,$2,$25
    beq    $25,$0,Big_ret
    move    $3,$4
    li    $25,0x38000000
    subu    $3,$3,$25 /* $3 -= 0x380[0x3ff-0x7f] (exponent adjust) */
    sll    $3,$3,3         /* $3 = (exponent + argument.H) << 3 */
    li    $25,0x80000000
    and    $4,$4,$25
    or    $3,$3,$4    /* $3 |= code[$4] */
    move    $2,$5
    srl    $2,$2,29    /* $2 = argument.L >> (32-3) */
    or    $2,$2,$3
__tr_ret:
    .if    FPU
    subu    $sp,$sp,8
    sw    $2,0($sp)
    nop
    l.s    $f0,0($sp)
    addu    $sp,$sp,8
    .endif
    j    $31

Zero_ret:
    xor    $2,$2,$2
    j    __tr_ret

Big_ret:
    li    $25,0x80000000
    and    $2,$2,$25
    li    $25,0x7f800000
    or    $2,$2,$25
    j    __tr_ret
