/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text
/*
    (double) -> (int)
*/


    .align 4
.globl __fixdfsi
.globl __fixunsdfsi
__fixdfsi:
__fixunsdfsi:
    move    $2,$4
    srl    $4,$4,20
    andi    $4,$4,0x7ff
    .set    noreorder
    sltiu    $25,$4,0x3ff
    bne    $25,$0,Zero_ret
    addiu    $4,$4,-0x3ff
    .set    reorder
    sltiu    $25,$4,32
    beq    $25,$0,Big_ret
    move    $3,$2
    li    $25,0xfffff
    and    $3,$3,$25
    li    $25,0x100000
    or    $3,$3,$25    /* $3 = fixed-point part */
    .set    noreorder
    sltiu    $25,$4,20
    bne    $25,$0,fixdf0
    addiu    $4,$4,-20
    .set    reorder
    beq    $4,$0,fixdf1
    sllv    $3,$3,$4
    subu    $4,$4,32
    subu    $4,$0,$4
    srlv    $5,$5,$4
    or    $3,$3,$5
    j    fixdf1
fixdf0:
    subu    $4,$0,$4
    srlv    $3,$3,$4
fixdf1:
    li    $25,0x80000000
    and    $25,$25,$2
    beq    $25,$0,fixdf2
    subu    $3,$0,$3
fixdf2:
    move    $2,$3
    j    $31

Big_ret:
    li    $2,0x80000000
    j    $31

Zero_ret:
    xor    $3,$3,$3
    xor    $2,$2,$2
    j    $31



/*
    (int) -> (double)
*/

    .align 4
.globl __floatsidf
__floatsidf:
    move    $3,$4
    beq    $3,$0,Zero_ret
    xor    $2,$2,$2        /* $2 = code */
    li    $5,0x80000000
    and    $25,$5,$3
    beq    $25,$0,fld0
    subu    $3,$0,$3
    move    $2,$5
fld0:
    xor    $7,$7,$7
    xor    $5,$5,$5    /* $5 = exponent */
    li    $25,0xffe00000
    and    $25,$25,$3
    beq    $25,$0,fld2
    move    $7,$3
fld1:
    srl    $3,$3,1
    addiu    $5,$5,1
    li    $25,0xffe00000
    and    $25,$25,$3
    bne    $25,$0,fld1
    or    $2,$2,$3
    move    $3,$5
    subu    $5,$5,32
    subu    $5,$0,$5
    sllv    $7,$7,$5
    move    $5,$3
    j    fld5
fld2:
    li    $25,0x100000
    and    $25,$25,$3
    bne    $25,$0,fld4
    sll    $3,$3,1
    addiu    $5,$5,-1
    j    fld2
fld4:
    or    $2,$2,$3
fld5:
    li    $25,0x800fffff
    and    $2,$2,$25
    addu    $5,$5,0x413        /* 0x413==0x3ff+20 , $5 = exponent */
    sll    $5,$5,20
    or    $2,$2,$5
    move    $3,$7
    j    $31
