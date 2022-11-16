/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text
    .align 4
.globl setjmp
setjmp:
    sw    $16,0($4)
    sw    $17,4($4)
    sw    $18,8($4)
    sw    $19,0xc($4)
    sw    $20,0x10($4)
    sw    $21,0x14($4)
    sw    $22,0x18($4)
    sw    $23,0x1c($4)
    sw    $29,0x20($4)
    sw    $30,0x24($4)
    sw    $31,0x28($4)
    xor    $2,$2,$2
    j    $31

    .align 4
.globl longjmp
longjmp:
    lw    $16,0($4)
    lw    $17,4($4)
    lw    $18,8($4)
    lw    $19,0xc($4)
    lw    $20,0x10($4)
    lw    $21,0x14($4)
    lw    $22,0x18($4)
    lw    $23,0x1c($4)
    lw    $29,0x20($4)
    lw    $30,0x24($4)
    lw    $31,0x28($4)
    move    $2,$5
    bne    $2,$0,.L0
    li    $2,1
.L0:
    j    $31
