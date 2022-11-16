/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    (float)a!=(float)b

    !((float)a==(float)b)
*/

.text
    .align 4



/*
    A[$4]
    B[$5]
*/

.globl __nesf2
.globl __eqsf2
__nesf2:
__eqsf2:
    bne    $4,$5,s_neq1
    xor    $2,$2,$2
    j    $31
s_neq1:
    li    $2,1
    j    $31


/*
    (float)a>(float)b

    1-((float)a<=(float)b)

    a   b
    1   1   0
    1   0   1
    0   1   0
*/
    .align 4
.globl __gtsf2
.globl __lesf2
__gtsf2:
__lesf2:
    li    $2,0x80000000
    and    $25,$2,$4
    bne    $25,$0,srgt1        /* A.. - */
    and    $25,$2,$5
    bne    $25,$0,True_val    /* A..+ , B.. -  */
/* A.. + , B.. + */
    sltu    $25,$5,$4
    bne    $25,$0,True_val    /* A[$4],B[$5] */
False_val:
    xor    $2,$2,$2
    j    $31

srgt1:
    and    $25,$2,$5
    beq    $25,$0,False_val    /* A..- , B.. +  */
/* A.. - , B.. - */
    sltu    $25,$4,$5
    beq    $25,$0,False_val    /* A.H[$4],B.H[$5] */
True_val:
    li    $2,1
    j    $31

/*
    ((float)a>=(float)b) - 1

    -((float)a<(float)b)

    a   b
    1   1   0
    1   0   0
    0   1  -1
*/


    .align 4
.globl __gesf2
.globl __ltsf2
__gesf2:
__ltsf2:
    li    $2,0x80000000
    and    $25,$2,$5
    bne    $25,$0,srlt1        /* A.. - */
    and    $25,$2,$4
    bne    $25,$0,True_val1    /* A..+ , B.. -  */
/* A.. + , B.. + */
    sltu    $25,$4,$5
    bne    $25,$0,True_val1    /* A[$5],B[$4] */
False_val1:
    xor    $2,$2,$2
    j    $31

srlt1:
    and    $25,$2,$4
    beq    $25,$0,False_val1    /* A..- , B.. +  */
/* A.. - , B.. - */
    sltu    $25,$5,$4
    beq    $25,$0,False_val1    /* A.H[$5],B.H[$4] */
True_val1:
    li    $2,0xffffffff
    j    $31
