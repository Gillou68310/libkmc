/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/


/*
    A[$4:$5]
    B[$6:$7]
*/


.text
    .align 4
.globl __cmpdi2
__cmpdi2:
    slt    $25,$4,$6    /* A.H[$4]<%B.H[$6] */
    bne    $25,$0,b_big
    beq    $4,$6,a_big
    slt    $25,$5,$7    /* A.L[$5]<%B.L[$7] */
    bne    $25,$0,b_big
    beq    $5,$7,a_big
    li    $2,1
    j    $31

b_big:
    xor    $2,$2,$2
    j    $31

a_big:
    li    $2,2
    j    $31

.globl __ucmpdi2
__ucmpdi2:
    sltu    $25,$4,$6
    bne    $25,$0,b_big    /* A.H[$4]<%B.H[$6] */
    bne    $6,$4,a_big
    sltu    $25,$5,$7
    bne    $25,$0,b_big    /* A.L[$5]<%B.L[$7] */
    bne    $7,$5,a_big
    li    $2,1
    j    $31
