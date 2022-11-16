/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text
/*
    (float) -> (int)
*/

    .align 4
.globl __fixsfsi
.globl __fixunssfsi
__fixsfsi:
__fixunssfsi:
    move    $2,$4
    srl    $4,$4,23
    andi    $4,$4,0xff
    .set    noreorder
    sltiu    $25,$4,0x7f
    bne    $25,$0,Zero_ret
    addiu    $4,$4,-0x7f
    .set    reorder
    sltiu    $25,$4,32
    beq    $25,$0,Big_ret
    move    $3,$2
    li    $25,0x7fffff
    and    $3,$3,$25
    li    $25,0x800000
    or    $3,$3,$25    /* $3 = fixed-point part */
    .set    noreorder
    sltiu    $25,$4,23
    bne    $25,$0,fixsf0
    addiu    $4,$4,-23
    .set    reorder
    beq    $4,$0,fixsf1
    sllv    $3,$3,$4
    j    fixsf1
fixsf0:
    subu    $4,$0,$4
    srlv    $3,$3,$4
fixsf1:
    li    $25,0x80000000
    and    $25,$25,$2
    beq    $25,$0,fixsf2
    subu    $3,$0,$3
fixsf2:
    move    $2,$3
    j    $31

Big_ret:
    li    $2,0x80000000
    j    $31

Zero_ret:
    xor    $2,$2,$2
    j    $31


/*
    (int) -> (float)
*/

    .align 4
.globl __floatsisf
__floatsisf:
    move    $2,$4
    beq    $2,$0,Zero_ret
    xor    $3,$3,$3        /* $3 = code */
    li    $4,0x80000000
    and    $25,$4,$2
    beq    $25,$0,fls0
    subu    $2,$0,$2
    move    $3,$4
fls0:
    li    $4,0x96        /* 0x96 = 0x7f+23 , $4 = exponent */
    li    $25,0xff800000
    and    $25,$25,$2
    beq    $25,$0,fls2
fls1:
    li    $25,0xff000000
    and    $25,$25,$2
    beq    $25,$0,fls4
    srl    $2,$2,1
    addiu    $4,$4,1
    j    fls1
fls2:
    sll    $2,$2,1
    addiu    $4,$4,-1
    li    $25,0x800000
    and    $25,$25,$2
    beq    $25,$0,fls2
fls4:
    li    $25,0x7fffff
    and    $2,$2,$25
    sll    $4,$4,23
    or    $2,$2,$4
    or    $2,$2,$3
    j    $31
