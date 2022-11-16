/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text
.globl    __adddf3
.globl    __subdf3


/*
    (double)A + (double)B

    A .. $4:$5(argument) $8(exponent)
    B .. $6:$7(argument) $9(exponent)

    A.H..upper 32 bits of A
    A.L..lower 32 bits of A
    B.H..upper 32 bits of B
    B.L..lower 32 bits of B

*/
    .align    4
__adddf3:
d_add0:
    move    $8,$4
    move    $9,$6
    li    $3,0x7ff00000
    and    $9,$9,$3    /* $9 = B.exponent */
    and    $8,$8,$3    /* $8 = A.exponent */
    beq    $9,$0,Zero_retA    /* B.H == 0 ? */
    beq    $8,$0,Zero_retB    /* A.H == 0 ? */
    sltu    $25,$8,$9
    beq    $25,$0,d_add1
    move    $25,$6
    move    $6,$4
    move    $4,$25    /* if the characteristic of the exponent part is A<B */
    move    $25,$7
    move    $7,$5
    move    $5,$25    /* A <-> B exchange */
    move    $25,$9
    move    $9,$8
    move    $8,$25
d_add1:
    beq    $3,$8,Big_retA
    move    $15,$8    /* save the exponent */
    move    $3,$8
    subu    $3,$3,$9    /* $3 = A.exponent-B.exponent */
    srl    $3,$3,20
    sltiu    $25,$3,52
    beq    $25,$0,Zero_retA    /* If difference of exponents is more than 52 process like B==0 */

    li    $8,0x100000
    or    $4,$4,$8    /* append a hidden bit to A.H[$4] */
    or    $6,$6,$8    /* append a hidden bit to B.H[$6] */
    li    $8,0x80000000
    move    $9,$4
    and    $9,$9,$8
    move    $14,$9    /* save the code of A */
    move    $9,$6
    and    $9,$9,$8
    move    $13,$9    /* save the code of B */
    li    $8,0x1fffff
    and    $4,$4,$8    /* limit the A.H[$4] with the argument only */
    and    $6,$6,$8    /* limit the B.H[$6] with the argument only */

    move    $9,$4    /* $9 = A.H[$4] */
    beq    $3,$0,d_add3
    addiu    $3,$3,-1
    beq    $3,$0,d_add21
    .set    noreorder
    sltiu    $25,$3,32
    bne    $25,$0,d_add2    /* If the difference of exponents is more than 32 */
    addiu    $3,$3,-32
    .set    reorder

    move    $7,$6    /* B.L[$7]=B.H[$6] */
    xor    $6,$6,$6    /* B.H[$6]=0 */
    move    $4,$3
    srlv    $7,$7,$4    /* B.L[$7] = B.L>>(difference of exponents - 32)[$4] */
    j    d_add21

d_add2:
    addu    $3,$3,32
    move    $4,$3
    li    $25,32
    subu    $25,$25,$4
    sll    $25,$6,$25
    srl    $7,$7,$4
    or    $7,$7,$25
    srl    $6,$6,$4    /*B[$6:$7] >>= $4 */
d_add21:
    addu    $7,$7,1
    sltu    $25,$7,1
    addu    $6,$6,$25    /* rounding B[$6:$7] += 1 */
    sll    $25,$6,31
    srl    $7,$7,1
    or    $7,$7,$25
    srl    $6,$6,1    /* B[$6:$7] >>= 1 */
d_add3:
    move    $4,$9    /* A.H[$4] = $9 */
    move    $8,$14    /* $8 = code of A */
    move    $9,$13    /* $9 = code of B */

    beq    $8,$9,d_add4        /* code of A == code of B */
    sltu    $25,$6,$4
    bne    $25,$0,d_sub_A        /* If A[$4:$5] > B[$6:$7]‚ resulting code is code of A */
    bne    $4,$6,d_sub_B        /* If A[$4:$5] < B[$6:$7]‚ resulting code is code of B */
    beq    $5,$7,Zero_ret
    sltu    $25,$7,$5
    bne    $25,$0,d_sub_A
d_sub_B:
    move    $8,$9    /* code of A= code of B */
    move    $25,$7
    move    $7,$5
    move    $5,$25    /* A <-> B exchange */
    move    $25,$6
    move    $6,$4
    move    $4,$25
d_sub_A:
    sltu    $25,$5,$7
    subu    $5,$5,$7
    subu    $4,$4,$6
    subu    $4,$4,$25    /* A[$4:$5] -= B[$6:$7] */
    move    $6,$15    /* $6 = exponent */
    bne    $4,$0,d_sub3    /* A.H[$4] != 0 ? */
    beq    $5,$0,Zero_ret

    li    $3,21
    li    $9,0x80000000
d_sub0:
    and    $25,$9,$5
    bne    $25,$0,d_sub1    /* A.L[$5] search the string bit */
    addiu    $3,$3,1        /* $3 = the number of 0's in $4:$5 + 1 */
    srl    $9,$9,1
    j    d_sub0

d_sub1:
    move    $9,$3
    sll    $9,$9,20
    .set    noreorder
    sltu    $25,$6,$9
    bne    $25,$0,Zero_ret    /* $6 -= $9 [characteristic adjust] */
    subu    $6,$6,$9
    .set    reorder
    .set    noreorder
    sltiu    $25,$3,32
    beq    $25,$0,d_sub2
    addiu    $3,$3,-32
    .set    reorder

    subu    $3,$0,$3
    move    $4,$3
    move    $7,$5
    srlv    $7,$7,$4    /* $7 = A.L[$5]>>$3 */
    li    $4,32
    subu    $4,$4,$3
    sllv    $5,$5,$4    /* A.L[$5] = (A.L[$5]<<(32-$3)) */
    move    $4,$7    /* A.H[$4] = $7 */
    j    d_add5

d_sub2:
    move    $4,$3
    sllv    $5,$5,$4
    move    $4,$5    /* A.H[$4] = A.L[$5]<<$3 */
    xor    $5,$5,$5    /* A.L[$5] = 0 */
    j    d_add5

d_sub3:
    xor    $3,$3,$3
    li    $9,0x100000
d_sub4:
    and    $25,$9,$4
    bne    $25,$0,d_sub5    /* A.H[$4] search the starting bit */
    addiu    $3,$3,1
    srl    $9,$9,1
    j    d_sub4
d_sub5:
    beq    $3,$0,d_add5
    move    $9,$3
    sll    $9,$9,20
    .set    noreorder
    sltu    $25,$6,$9
    bne    $25,$0,Zero_ret    /* $6 -= $9 [characteristic adjust] */
    subu    $6,$6,$9
    .set    reorder

    move    $9,$4    /* $9 = A.H[$4] */
    move    $4,$3

    li    $25,32
    subu    $25,$25,$4
    srl    $25,$5,$25
    sll    $9,$9,$4
    or    $9,$9,$25
    sll    $5,$5,$4    /* A[$9:$5] <<= $4 */

    move    $4,$9    /* A.H[$4] = $9 */
    j    d_add5

d_add4:
    addu    $5,$5,$7
    sltu    $25,$5,$7
    addu    $4,$4,$6
    addu    $4,$4,$25    /* A[$4:$5] += B[$6:$7] */
    move    $6,$15    /* $6 = exponent */
    li    $25,0x200000
    and    $25,$25,$4
    beq    $25,$0,d_add5    /* carry check */
    addu    $5,$5,1
    sltu    $25,$5,1
    addu    $4,$4,$25    /* rounding B[$4:$5] += 1 */
    sll    $25,$4,31
    srl    $5,$5,1
    or    $5,$5,$25
    srl    $4,$4,1    /* A[$4:$5] >>= 1 */
    li    $25,0x100000
    addu    $6,$6,$25    /* $6[exponent] += 1 */
    li    $25,0x7f800000
    sltu    $25,$6,$25
    beq    $25,$0,Big_ret
d_add5:
    move    $3,$5    /* $3 = A.L[$5] */
    li    $2,0xfffff
    and    $2,$2,$4    /* $2 = A.H[$4] */
    or    $2,$2,$8    /* $2 |= $8[resulting code] */
    or    $2,$2,$6    /* $2 |= $6[resulting exponent] */
d_add6:
    j    $31

Zero_ret:
    xor    $3,$3,$3
    xor    $2,$2,$2
    j    $31

Zero_retB:
    move    $3,$7
    move    $2,$6
    j    $31

Big_retA:
Zero_retA:
    move    $3,$5
    move    $2,$4
    j    $31

Big_ret:
    li    $2,0x7ff00000
    or    $2,$2,$8        /* code */
    xor    $3,$3,$3
    j    $31



/*
    (double)A - (double)B
    = A + (-B)
*/
    .align    4
__subdf3:
    li    $25,0x80000000
    xor    $6,$6,$25 /* B = -B */
    j    d_add0
