/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/


/*
    (double)a!=(double)b

    !((double)a==(double)b)
*/
.text
    .align 4
.globl __nedf2
.globl __eqdf2
__nedf2:
__eqdf2:
    bne    $4,$6,d_neq1    /* A.H[$4] != B.H[$6] */
    bne    $5,$7,d_neq1    /* A.L[$5] != B.L[$7] */
    xor    $2,$2,$2
    j    $31
d_neq1:
    li    $2,1
    j    $31


/*
    $4:$5[A] > $6:$7[B]
*/

.globl __gtdf2
.globl __ledf2
__gtdf2:
__ledf2:
reg_gt:
    li    $2,0x80000000
    and    $25,$2,$4
    bne    $25,$0,rgt1        /* A.. - */
    and    $25,$2,$6
    bne    $25,$0,True_val    /* A..+ , B.. -  */
/* A.. + , B.. + */
    sltu    $25,$6,$4
    bne    $25,$0,True_val    /* A.H[$4],B.H[$6] */
    bne    $4,$6,False_val
    sltu    $25,$7,$5
    bne    $25,$0,True_val    /* A.L[$5],B.L[$7] */
False_val:
    xor    $2,$2,$2
    j    $31

rgt1:
    and    $25,$2,$6
    beq    $25,$0,False_val    /* A..- , B.. +  */
/* A.. - , B.. - */
    sltu    $25,$6,$4
    bne    $25,$0,False_val    /* A.H[$4],B.H[$6] */
    bne    $4,$6,True_val
    sltu    $25,$5,$7
    beq    $25,$0,False_val    /* A.L[$5],B.L[$7] */
True_val:
    li    $2,1
    j    $31



/*
    ((double)a>=(double)b) - 1

    -((double)a<(double)b)

    a   b
    1   1   0
    1   0   0
    0   1  -1
*/

    .align 4
.globl __gedf2
.globl __ltdf2
__gedf2:
__ltdf2:
    li    $2,0x80000000
    and    $25,$2,$6
    bne    $25,$0,rlt1        /* A.. - */
    and    $25,$2,$4
    bne    $25,$0,True_val1    /* A..+ , B.. -  */
/* A.. + , B.. + */
    sltu    $25,$4,$6
    bne    $25,$0,True_val1    /* A.H[$6],B.H[$4] */
    bne    $6,$4,False_val1
    sltu    $25,$5,$7
    bne    $25,$0,True_val1    /* A.L[$7],B.L[$5] */
False_val1:
    xor    $2,$2,$2
    j    $31

rlt1:
    and    $25,$2,$4
    beq    $25,$0,False_val1    /* A..- , B.. +  */
/* A.. - , B.. - */
    sltu    $25,$4,$6
    bne    $25,$0,False_val1    /* A.H[$6],B.H[$4] */
    bne    $6,$4,True_val1
    sltu    $25,$7,$5
    beq    $25,$0,False_val1    /* A.L[$7],B.L[$5] */
True_val1:
    li    $2,0xffffffff
    j    $31
