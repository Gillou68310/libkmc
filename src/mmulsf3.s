/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text



/*
    A .. $4(argument) $8(exponent)
    B .. $5(argument) $10(exponent)
*/

    .align    4
    .globl    __mulsf3
__mulsf3:
    move    $8,$4
    move    $10,$5
    li    $2,0x7f800000
    and    $8,$8,$2    /* $8 = A.exponent */
    and    $10,$10,$2    /* $10 = B.exponent */
    beq    $8,$0,Zero_ret    /* A[$4] == 0 ? */
    beq    $10,$0,Zero_ret    /* B[$5] == 0 ? */

    addu    $8,$8,$10    /* $8 = A.exponent + B.exponent */

    li    $10,0x80000000
    move    $2,$4
    xor    $2,$2,$5
    and    $10,$10,$2    /* $10 = code */

    li    $9,0x800000
    or    $4,$4,$9    /* add the hidden bit to A[$4] */
    or    $5,$5,$9    /* add the hidden bit to B[$5] */
    li    $9,0xffffff
    and    $4,$4,$9    /* limit A[$4] with argument only */
    and    $5,$5,$9    /* limit B[$5] with argument only */
    sll    $4,$4,8        /* A[$4] <<= 8 */
    sll    $5,$5,2        /* B[$5] <<= 2 */

    multu    $4,$5    /* $2 = A[$4]*B[$5] */
    mfhi    $2
    j    f_norm



/*
    A .. $4(argument) $8(exponent)
    B .. $5(argument) $3(exponent)
*/

    .align    4
    .globl    __divsf3
__divsf3:

    li    $10,0x80000000
    move    $2,$4
    xor    $2,$2,$5
    and    $10,$10,$2    /* $10 = code */

    move    $8,$4
    move    $3,$5
    li    $2,0x7f800000
    and    $8,$8,$2    /* $8 = A.exponent */
    and    $3,$3,$2    /* $3 = B.exponent */
    beq    $8,$0,Zero_ret        /* A[$4] == 0 ? */
    beq    $3,$0,Big_ret        /* B[$5] == 0 ? */

    beq    $2,$8,Big_ret    /* A == infinity ? */
    beq    $2,$3,Zero_ret    /* B == infinity ? */

    li    $25,0x7e800000
    addu    $8,$8,$25
    subu    $8,$8,$3    /* $8 = A.exponent - B.exponent + 0x7e800000 */

    li    $9,0x800000
    or    $4,$4,$9    /* add the hidden bit to A[$4] */
    or    $5,$5,$9    /* add the hidden bit to B[$5] */
    li    $9,0xffffff
    and    $4,$4,$9    /* limit A[$4] with the argument */
    and    $5,$5,$9    /* limit B[$5] with the argument */

    move    $3,$4
    move    $2,$4
    srl    $3,$3,7        /* $3 >>= 7(=32-25) */
    sll    $2,$2,25    /* $2 <<= 25 */

    move    $2,$4
    sll    $2,$2,8

    move    $11,$4    /* a[$4:$11] */
    srl    $4,$4,7
    sll    $11,$11,25

    move    $9,$5    /* b[$5] */
    srl    $9,$9,17
    xor    $3,$3,$3
    addiu    $9,$9,1
    divu    $2,$2,$9

    move    $9,$2    /* c1[$9] */

    multu    $2,$5
    mflo    $2
    mfhi    $3

    sltu    $25,$11,$2
    subu    $11,$11,$2
    subu    $4,$4,$3
    subu    $4,$4,$25

divsf0:
    beq    $4,$0,divsf2

    move    $2,$11    /* a1[$3:$2] = a[$4:$11] */
    move    $3,$4

    move    $12,$5    /* b1[edp] = b[$5] */

divsf1:
    sll    $25,$3,31
    srl    $2,$2,1
    or    $2,$2,$25
    srl    $3,$3,1    /* a1[$3:$2] >>= 1 */
    srl    $12,$12,1        /* b1[$12] >>= 1 */

    bne    $3,$0,divsf1

    addiu    $12,$12,1
    divu    $2,$2,$12        /* $2 = a1[$3:$2]/(b1[$12]+1) */

    addu    $9,$9,$2    /* c1[$9] += $2 */

    multu    $2,$5
    mflo    $2
    mfhi    $3
    sltu    $25,$11,$2
    subu    $11,$11,$2
    subu    $4,$4,$3
    subu    $4,$4,$25
    j    divsf0

divsf2:
    move    $2,$11    /* $2 = c1[$9]+a1[$3:$2]/b[$5] */
    move    $3,$4
    divu    $2,$2,$5
    addu    $2,$2,$9

f_norm:
    li    $3,0x2000000
    addiu    $2,$2,1        /* rounding */
    and    $25,$3,$2
    beq    $25,$0,f_norm0
    addiu    $2,$2,1        /* rounding */
f_norm0:
    and    $25,$3,$2
    beq    $25,$0,f_norm1
    srl    $2,$2,1
    li    $25,0x800000
    addu    $8,$8,$25    /* exponent[$8] += 1[0x800000] */
f_norm1:
    srl    $2,$2,1

    .set    noreorder
    li    $24,0x3f800000
    sltu    $25,$8,$24
    bne    $25,$0,Zero_ret
    subu    $8,$8,$24
    .set    reorder

    li    $25,0x7f800000
    sltu    $25,$8,$25
    beq    $25,$0,Big_ret

    li    $3,0x7fffff
    and    $2,$2,$3    /* $2 = $3[resulting argument] & 0x7fffff */
    or    $2,$2,$10    /* $2 |= $10[resulting code] */
    or    $2,$2,$8    /* $2 |= $8[resulting exponent] */
f_norm2:
    j    $31

Zero_ret:
    xor    $2,$2,$2
    j    $31

Big_ret:
    li    $2,0x7f800000
    or    $2,$2,$10
    j    $31

