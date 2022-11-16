/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

.text



/*
    A .. $4:$5(argument) $8(exponent)
    B .. $6:$7(argument) $9(exponent)

    A.H..Upper 32 bit of A
    A.L..Lower 32 bit of A
    B.H..Upper 32 bit of B
    B.L..Lower 32 bit of B

    (A.H+A.L)*(B.H+B.L) = A.H*B.H+A.L*B.H+A.H*B.L+A.L*B.L
                = A.H*B.H+A.L*B.H+A.H*B.L ..... if A.L & B.L are smaller than A.H & B.H,
                                    then the last element can be ignored.
*/


    .align    4
    .globl    __muldf3
__muldf3:
    move    $8,$4    /* $8 = A.H[exponent + code] */
    move    $3,$6
    move    $9,$3    /* $9 = B.H[exponent + code] */

    xor    $3,$3,$8
    li    $11,0x80000000
    and    $3,$3,$11    /* $3 = code */

    li    $10,0x7ff00000
    and    $8,$8,$10    /* $8 = A.exponent [A.H & 0x7ff00000] */
    and    $9,$9,$10    /* $9 = B.exponent [B.H & 0x7ff00000] */
    beq    $8,$0,Zero_ret    /* A.H == 0 ? */
    beq    $9,$0,Zero_ret    /* B.H == 0 ? */
    addu    $8,$8,$9    /* $8 = A.exponent + B.exponent */


    move    $14,$3    /* save the code */
    move    $15,$8    /* save the exponent */

    srl    $25,$5,21
    sll    $4,$4,11
    or    $4,$4,$25
    sll    $5,$5,11    /* A[$4:$5] <<= 11 */
    or    $4,$4,$11    /* A.H[$4] |= 0x80000000[$11] */

    move    $8,$11
    srl    $25,$7,21
    sll    $6,$6,11
    or    $6,$6,$25
    sll    $7,$7,11    /* B[$6:$7] <<= 11 */
    or    $6,$6,$8    /* B.H[$6] |= 0x80000000 */

    multu    $5,$6    /* $8 = (A.L[$5] * B.H[$6])>>32  */
    mflo    $13
    mfhi    $8
    nop

    move    $5,$0
    multu    $4,$6    /* $6:$8 = A.H[$4] * B.H[$6] + $8 */
    mflo    $3
    mfhi    $6
    addu    $8,$8,$3
    sltu    $25,$8,$3
    addu    $6,$6,$5
    addu    $6,$6,$25

    multu    $4,$7    /* $6:$8 += (A.H[$4] * B.L[$7])>>32[$5] */
    mfhi    $3
    xor    $5,$5,$5
    addu    $8,$8,$3
    sltu    $25,$8,$3
    addu    $6,$6,$5
    addu    $6,$6,$25
/*
    .386off
    mflo    $3
    addu    #25,$3,#13
    sltu    #25,#25,$3
    addu    $8,$8,#25
    sltu    #25,$8,#25
    addu    $6,$6,#25
    .386on
*/
    j    d_norm




/*
    A .. $4:$5(argument) $8(exponent)
    B .. $6:$7(argument) $9(exponent)

    A.H..Upper 32 bit of A
    A.L..Lower 32 bit of A
    B.H..Upper 32 bit of B
    B.L..Lower 32 bit of B

    (A.H+A.L)/(B.H+B.L) = (A.H+A.L)/B.H*1/(1+B.L/B.H)
                = (A.H+A.L)/B.H*(1-B.L/B.H) ......... if B.L is smaller than B.H, 
                                        approximation would be consisted
                = A.H/B.H+A.L/B.H-(A.H/B.H+A.L/B.H)*B.L/B.H
                = A.H/B.H+A.L/B.H-A.H*B.L/B.H*B.H-A.L*B.L/B.H*B.H
                = A.H/B.H+A.L/B.H-A.H*B.L/B.H*B.H ... if the A.L & B.L are smaller than 
                                        B.H, then the last element can be 
                                        ignored(A.L*B.L/B.H*B.H)
                = (A.H+A.L-A.H*B.L/B.H)/B.H

    Note:  In order to get the quotient in a range of 32 bit with the division of the 
         64bit/32bit‚ it needs to be A.H<B.H.  Because of this, when normalizing the 
         internal representation of A has one less than B does to shift.
*/


    .align    4
    .globl    __divdf3
__divdf3:
    move    $3,$6
    xor    $3,$3,$4
    li    $11,0x80000000
    and    $3,$3,$11    /* $3 = code */
    move    $9,$3

    move    $8,$4    /* $8 = A.H[exponent + code] */
    move    $9,$6    /* $9 = B.H[exponent + code] */

    li    $10,0x7ff00000
    and    $8,$8,$10    /* $8 = A.exponent [A.H & 0x7ff00000] */
    and    $9,$9,$10    /* $9 = B.exponent [B.H & 0x7ff00000] */
    beq    $8,$0,Zero_ret        /* A.H == 0 ? */
    beq    $9,$0,Big_ret        /* B.H == 0 ? */
    beq    $8,$10,Big_ret    /* A == infinity ? */
    beq    $9,$10,Zero_ret    /* B == infinity ? */

    li    $25,0x7fd00000
    addu    $8,$8,$25
    subu    $8,$8,$9    /* exponent[$8] = A.exponent - B.exponent + 0x7fd00000 */

    move    $14,$3    /* save the code */
    move    $15,$8    /* save the exponent */
    srl    $11,$11,1        /* $11 = 0x40000000 */
    srl    $25,$5,22
    sll    $4,$4,10
    or    $4,$4,$25
    sll    $5,$5,10    /* A[$4:$5] <<= 10 */
    or    $4,$4,$11

    sll    $11,$11,1        /* $11 = 0x80000000 */
    move    $8,$11    /* $8 = 0x80000000 */
    or    $4,$4,$11
    xor    $4,$4,$11    /* clear the highest bit of A.H[$4] */


    srl    $25,$7,21
    sll    $6,$6,11
    or    $6,$6,$25
    sll    $7,$7,11    /* B[$6:$7] <<= 11 */
    or    $6,$6,$8    /* B.H[$6] |= 0x80000000[$8] */

/*
    A[$4:$5]/B[$6:$7]
*/

    move    $13,$5        /* save A.L */

/* $10=a/b.us[HH] */
    move    $3,$4
    li    $25,0xffff0000
    and    $3,$3,$25    /* x[$3] = a.us[HH]<<16 */
    move    $8,$6
    srl    $8,$8,16        /* y[$8] = b.us[HH] */
    divu    $10,$3,$8
    mfhi    $3            /* x[$3] = x % y */
    sll    $10,$10,16        /* c.us[HH][$10.hi] = x/y */
    sll    $3,$3,16        /* x[$3] <<= 16 */
    divu    $3,$3,$8        /* x[$3] = x/y */
    or    $10,$10,$3        /* c.us[HL][$10.lo] = x */
    move    $3,$4
    sll    $3,$3,16        /* x[$3] = a.us[HL]<<16 */
    divu    $3,$3,$8        /* x[$3] = x/y */
    addu    $10,$10,$3        /* c.ui[HI][$10] += x */

/* $11=a/(b.us[HH]+1) */
    addiu    $8,$8,1            /* y[$8] += 1 */
    move    $3,$4
    li    $25,0xffff0000
    and    $3,$3,$25    /* x[$3] = a.us[HH]<<16 */
    divu    $11,$3,$8
    mfhi    $3            /* x[$3] = x % y */
    sll    $11,$11,16        /* d.us[HH][$11.hi] = x/y */
    sll    $3,$3,16        /* x[$3] <<= 16 */
    divu    $3,$3,$8        /* x[$3] = x/y */
    or    $11,$11,$3        /* d.us[HL][$11.lo] = x */

    move    $3,$4
    sll    $3,$3,16        /* x[$3] = a.us[HL]<<16 */
    divu    $3,$3,$8        /* x[$3] = x/y */
    addu    $11,$11,$3        /* c.ui[HI][$11] += x */
NonDiv0:
    move    $8,$10
    subu    $10,$10,$11        /* $10 -= $11 */

    move    $3,$6
    andi    $3,$3,0xffff        /* $3 = b.ui[HI] & 0xffff */
    multu    $10,$3        /* $5:$3 = $3*$10 */
    mflo    $3
    mfhi    $5
    srl    $25,$3,16
    sll    $5,$5,16
    or    $5,$5,$25
    sll    $3,$3,16        /* $5:$3 <<= 16 */

    move    $10,$8        /* g.ll[$10:$11] = $10:0 - $5:$3 */
    xor    $11,$11,$11
    sltu    $25,$11,$3
    subu    $11,$11,$3
    subu    $10,$10,$5
    subu    $10,$10,$25

    multu    $10,$6        /* $8:$9 = g.ui[HI]*b.ui[HI] = $10*$6 */
    mflo    $9
    mfhi    $8
    nop
    nop
    multu    $10,$7        /* ax = g.ui[HI]*b.ui[LO]>>32 = $10*$7>>32 */
    mfhi    $3
    xor    $5,$5,$5
    addu    $9,$9,$3
    sltu    $25,$9,$3
    addu    $8,$8,$5
    addu    $8,$8,$25
    multu    $11,$6        /* ax = g.ui[LO]*b.ui[HI]>>32 = $11*$6>>32 */
    mfhi    $3
    addu    $9,$9,$3
    sltu    $25,$9,$3
    addu    $8,$8,$5
    addu    $8,$8,$25    /* c.ll[$8:$9] */
    move    $5,$13        /* $5 = A.L */

    sltu    $25,$5,$9
    subu    $5,$5,$9
    subu    $4,$4,$8
    subu    $4,$4,$25    /* a.ll[$4:$5] -= c.ll[$8:$9] */
    xor    $9,$9,$9        /* sign[$9] = 0 */
    li    $25,0x80000000
    and    $25,$25,$4
    beq    $25,$0,BigA
    li    $3,0xffffffff    /* a.ll[$4:$5] = -a.ll */
    xor    $4,$4,$3
    xor    $5,$5,$3
    addu    $5,$5,1
    sltu    $25,$5,1
    addu    $4,$4,$25
    addiu    $9,$9,1            /* sign[$9] = 1 */
BigA:
    xor    $8,$8,$8        /* shift[$8] = 0 */
    li    $3,0x80000000
loop0:
    bne    $4,$0,Ashift        /* a.ui[HI] != 0 */
    and    $25,$5,$3
    beq    $25,$0,loop0_next    /* (a.ui[LO] & 0x80000000)==0 */
Ashift:
    sll    $25,$4,31
    srl    $5,$5,1
    or    $5,$5,$25
    srl    $4,$4,1        /* a.ll[$4:$5] >>= 1 */
    addiu    $8,$8,1
    j    loop0
loop0_next:

    move    $3,$5        /* x[$3] = A.L */
    li    $25,0xffff0000
    and    $3,$3,$25
    move    $7,$6
    srl    $6,$6,16        /* y[$6] = b.us[HH] */
    divu    $4,$3,$6
    mfhi    $3            /* x[$3] = x % y */
    sll    $4,$4,16        /* c.us[HH][$4.hi] = x/y */
    sll    $3,$3,16        /* x[$3] <<= 16 */
    divu    $3,$3,$6        /* x[$3] = x/y */
    or    $4,$4,$3
    move    $3,$5        /* x[$3] = A.L */
    sll    $3,$3,16        /* x[$3] <<= 16 */
    divu    $3,$3,$6        /* x[$3] = x/y */
    addu    $4,$4,$3

    addiu    $6,$6,1            /* y += 1 */
    move    $3,$5        /* x[$3] = A.L */
    move    $13,$5        /* save A.L */
    li    $25,0xffff0000
    and    $3,$3,$25
    divu    $5,$3,$6
    mfhi    $3            /* x[$3] = x % y */
    sll    $5,$5,16        /* d.us[HH][$5.hi] = x/y */
    sll    $3,$3,16        /* x[$3] <<= 16 */
    divu    $3,$3,$6        /* x[$3] = x/y */
    or    $5,$5,$3
    move    $3,$13        /* $3 = A.L */
    sll    $3,$3,16        /* x[$3] <<= 16 */
    divu    $3,$3,$6        /* x[$3] = x/y */
    addu    $5,$5,$3
NonDiv1:
    move    $6,$4
    subu    $6,$6,$5        /* e[si] = c[$4]-d[$5] */
    andi    $7,$7,0xffff
    multu    $6,$7        /*  $5:$3 = e.ui[LO]*(b.ui[HI] & 0xffff) */
    mflo    $3
    mfhi    $5
    sll    $25,$5,16
    srl    $3,$3,16
    or    $3,$3,$25
    srl    $5,$5,16
    subu    $4,$4,$3
    xor    $5,$5,$5
    beq    $8,$0,NotShift
    li    $25,32
    subu    $25,$25,$8
    srl    $25,$4,$25
    sll    $5,$5,$8
    or    $5,$5,$25
    sll    $4,$4,$8
NotShift:
    beq    $9,$0,AddVal
    sltu    $25,$11,$4
    subu    $11,$11,$4
    subu    $10,$10,$5
    subu    $10,$10,$25
    j    AddSub
AddVal:
    addu    $11,$11,$4
    sltu    $25,$11,$4
    addu    $10,$10,$5
    addu    $10,$10,$25
AddSub:
    move    $8,$11
    move    $6,$10


d_norm:
    move    $9,$14    /* $9 = code */
    li    $5,0x80000000
    li    $3,0x400
    and    $25,$5,$6
    bne    $25,$0,d_div1
    li    $3,0x200
d_div1:
    xor    $4,$4,$4
    addu    $8,$8,$3
    sltu    $25,$8,$3
    addu    $6,$6,$4
    addu    $6,$6,$25    /* rounding */

    li    $4,11
    li    $3,0x3fe00000
    and    $25,$5,$6
    bne    $25,$0,d_div2
    li    $4,10
    li    $3,0x3ff00000
d_div2:

    move    $2,$15    /* $2 = exponent */

    .set    noreorder
    sltu    $25,$2,$3
    bne    $25,$0,Zero_ret    /* $2 = $2-$4 [characteristic adjust] */
    subu    $2,$2,$3
    .set    reorder
    li    $25,0x7ff00000
    sltu    $25,$2,$25
    beq    $25,$0,Big_ret
    move    $3,$4
    li    $25,32
    subu    $25,$25,$4
    sll    $25,$6,$25
    srl    $8,$8,$4
    or    $8,$8,$25
    srl    $6,$6,$4    /* $6:$8 >>= $3 */

    li    $25,0xfffff
    and    $6,$6,$25
    or    $2,$2,$6
    or    $2,$2,$9
    move    $3,$8
d_div3:
    j    $31

Zero_ret:
    xor    $2,$2,$2
    xor    $3,$3,$3
    j    $31

Big_ret:
    li    $2,0x7ff00000
    or    $2,$2,$9        /* code[$9] */
    xor    $3,$3,$3
    j    $31

