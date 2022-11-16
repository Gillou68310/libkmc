/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    (float) -> (long long)
*/
    .include    "mips_as.h"

    .align 4
.globl __fixsfdi
.globl __fixunssfdi
__fixsfdi:
__fixunssfdi:
    .if    FPU
    subu    $sp,$sp,8
    s.s    $f12,0($sp)
    nop
    lw    $4,0($sp)
    addu    $sp,$sp,8
    .endif
    move    $3,$4
    srl    $4,$4,23
    andi    $4,$4,0xff
    .set    noreorder
    sltiu    $25,$4,0x7f
    bne    $25,$0,Zero_ret
    addiu    $4,$4,-0x7f
    .set    reorder
    sltiu    $25,$4,64
    beq    $25,$0,Big_ret
    move    $6,$3
    li    $25,0x7fffff
    and    $3,$3,$25
    li    $25,0x800000
    or    $3,$3,$25    /* $3 = fixed-point part */
    .set    noreorder
    sltiu    $25,$4,23
    bne    $25,$0,fixsf1
    addiu    $4,$4,-23
    .set    reorder
    beq    $4,$0,fixsf2
    move    $7,$4
    .set    noreorder
    sltiu    $25,$4,32
    bne    $25,$0,fixsf0
    addiu    $4,$4,-32
    .set    reorder
    xor    $3,$3,$3
    srlv    $2,$2,$4
    j    fixsf3

fixsf0:
    subu    $4,$0,$4
    move    $2,$3
    srlv    $2,$2,$4    /* A.H[$2] = fixed-point part>>(32-$5) */
    move    $4,$7
    sllv    $3,$3,$4    /* A.L[$3] = fixed-point part<<$5 */
    j    fixsf3

fixsf1:
    subu    $4,$0,$4
    srlv    $3,$3,$4
fixsf2:
    xor    $2,$2,$2
fixsf3:
    li    $25,0x80000000
    and    $25,$25,$6
    beq    $25,$0,fixsf4
    li    $6,0xffffffff
    xor    $3,$3,$6
    xor    $2,$2,$6
    addu    $3,$3,1
    sltu    $25,$3,1
    addu    $2,$2,$25
fixsf4:
    j    $31

Big_ret:
    li    $3,0x00000000
    li    $2,0x80000000
    j    $31

Zero_ret:
    xor    $2,$2,$2
    xor    $3,$3,$3
    j    $31

/*
    (long long) -> (float)
*/


    .align 4
.globl __floatdisf
__floatdisf:
    move    $2,$5        /* $2 = A.L */
    move    $3,$4        /* $3 = A.H */
    or    $4,$4,$5
    .if    FPU
    bne    $4,$0,loc0
    subu    $sp,$sp,8
    sw    $2,0($sp)
    nop
    l.s    $f0,0($sp)
    addu    $sp,$sp,8
    j    $31
loc0:
    .else
    beq    $4,$0,Zero_ret
    .endif
    xor    $6,$6,$6        /* $6 = code */
    li    $4,0x80000000
    and    $25,$4,$3
    beq    $25,$0,fld0
    li    $7,0xffffffff
    xor    $2,$2,$7
    xor    $3,$3,$7
    addu    $2,$2,1
    sltu    $25,$2,1
    addu    $3,$3,$25
    move    $6,$4
fld0:
    li    $4,0xb6        /* 0xb6=0x7f+55 $4 = exponent */
    li    $25,0xff000000
    and    $25,$25,$3
    beq    $25,$0,fld2
fld1:
    sll    $25,$3,31
    srl    $2,$2,1
    or    $2,$2,$25
    srl    $3,$3,1
    addiu    $4,$4,1
    li    $25,0xff000000
    and    $25,$25,$3
    bne    $25,$0,fld1
    j    fld5
fld2:
    li    $25,0x800000
    and    $25,$25,$3
    bne    $25,$0,fld5
    srl    $25,$2,31
    sll    $3,$3,1
    or    $3,$3,$25
    sll    $2,$2,1
    addiu    $4,$4,-1
    j    fld2
fld5:
    li    $2,0x7fffff
    and    $2,$2,$3
    sll    $4,$4,23
    or    $2,$2,$4
    or    $2,$2,$6
    .if    FPU
    subu    $sp,$sp,8
    sw    $2,0($sp)
    nop
    l.s    $f0,0($sp)
    addu    $sp,$sp,8
    .endif
    j    $31
