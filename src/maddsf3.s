/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text
.globl    __addsf3
.globl    __subsf3
/*
    (float)A + (float)B

    A .. (argument) (exponent or code)
    B .. (argument) (exponent or code)
*/


    .align    4
__addsf3:
f_add0:
    move    $8,$4
    move    $10,$5
    li    $2,0x7f800000
    and    $10,$10,$2    /* $10 = B.exponent */
    and    $8,$8,$2    /* $8 = A.exponent */
    beq    $10,$0,Zero_retA    /* B[$5] == 0 ? */
    beq    $8,$0,Zero_retB    /* A[$4] == 0 ? */
    sltu    $25,$8,$10
    beq    $25,$0,f_add1
    move    $25,$4
    move    $4,$5
    move    $5,$25    /* If the exponent part is A<B */
    move    $25,$10
    move    $10,$8
    move    $8,$25    /* A <-> B exchange */
f_add1:
    beq    $2,$8,Big_retA
    move    $15,$8    /* save the exponent */
    move    $2,$8
    subu    $2,$2,$10    /* $2 = A.exponent - B.exponent */
    srl    $2,$2,23
    sltiu    $25,$2,23
    beq    $25,$0,Zero_retA    /* if difference of exponents is more than 23 process like B==0 */

    li    $9,0x800000
    or    $4,$4,$9    /* append a hidden bit to A[$4] */
    or    $5,$5,$9    /* append a hidden bit to B[$5] */
    li    $9,0x80000000
    move    $8,$4
    and    $8,$8,$9    /* $8 = code of A */
    move    $10,$5
    and    $10,$10,$9    /* $10 = code of B */
    li    $9,0xffffff
    and    $4,$4,$9    /* limit A[$4] with argument only */
    and    $5,$5,$9    /* limit B[$5] with argument only */

    beq    $2,$0,f_add3
    move    $9,$2
    addiu    $9,$9,-1
    srlv    $5,$5,$9    /* B[$5] = B[$5]>>(differences of exponents)[$9] */
fadd_2:
    addiu    $5,$5,1        /* rounding */
    srl    $5,$5,1
f_add3:
    beq    $8,$10,f_add4        /* code of A == code of B */
    beq    $4,$5,Zero_ret
    sltu    $25,$5,$4
    bne    $25,$0,f_sub_A    /* if A[$4] > B[$5]‚ the resulting code is code of A */
                    /* if A[$4] < B[$5]‚ the resulting code is code of B */
f_sub_B:
    move    $8,$10    /* code of A = code of B */
    move    $25,$5
    move    $5,$4
    move    $4,$25    /* A <-> B exchange */
f_sub_A:
    subu    $4,$4,$5    /* A[$4] -= B[$5] */
    move    $5,$15    /* $5 = exponent */

    xor    $2,$2,$2
    li    $3,0x800000
f_sub0:
    and    $25,$3,$4
    bne    $25,$0,f_sub1    /* A.L[$4] search the starting bit */
    addiu    $2,$2,1
    srl    $3,$3,1
    j    f_sub0

f_sub1:
    move    $3,$2
    sll    $3,$3,23
    .set    noreorder
    sltu    $25,$5,$3
    bne    $25,$0,Zero_ret    /* $5 -= $3 [characteristic adjust] */
    subu    $5,$5,$3
    .set    reorder
    move    $9,$2
    sllv    $4,$4,$9    /* A[$4] <<= $2 */
    j    f_add5

f_add4:
    addu    $4,$4,$5    /* A[si] += B[$5] */
    move    $5,$15    /* $5 = exponent */
    li    $3,0x1000000
    and    $25,$3,$4
    beq    $25,$0,f_add5    /* carry check */
    addu    $4,$4,1        /* rounding */
    srl    $4,$4,1        /* A[$4] >>= 1 */
    li    $25,0x800000
    addu    $5,$5,$25    /* $5[exponent] += 1 */
    li    $25,0x7f800000
    sltu    $25,$5,$25
    beq    $25,$0,Big_ret
f_add5:
    li    $2,0x7fffff
    and    $2,$2,$4    /* $2 = A[$4] */
    or    $2,$2,$8    /* $2 |= $8[resulting code] */
    or    $2,$2,$5    /* $2 |= $5[resulting exponent] */
f_add6:
    j    $31

Zero_ret:
    xor    $2,$2,$2
    j    $31

Zero_retB:
    move    $2,$5
    j    $31

Big_retA:
Zero_retA:
    move    $2,$4
    j    $31

Big_ret:
    li    $2,0x7f800000
    or    $2,$2,$8
    j    $31

/*
    (double)A - (double)B
    = A + (-B)
*/
    .align    4
__subsf3:
    li    $25,0x80000000
    xor    $5,$5,$25 /* B = -B */
    j    f_add0
