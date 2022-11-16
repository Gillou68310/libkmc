/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    -(double)
*/



.globl    __negdf2
.globl    __negsf2
    .align    4
__negdf2:
    move    $2,$4
    li    $3,0x7ff00000
    and    $3,$3,$2
    beq    $3,$0,negret
    move    $3,$5
    li    $25,0x80000000
    xor    $2,$2,$25
negret:
    j    $31

/*
    -(float)
*/

    .align 4
__negsf2:
    move    $2,$4
    li    $3,0x7f800000
    and    $3,$3,$2
    beq    $3,$0,negret
    li    $25,0x80000000
    xor    $2,$2,$25
    j    $31
