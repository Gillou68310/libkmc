/*
    Copyright (c) 1995,1996 by Kyoto Micro Computer Co. Ltd.
    All Rights Reserved.
*/

/*
    sin,cos,tan,atan TABLE
       atan(2^-i) table
*/

#include "_kmclib.h"
#include <cordic.h>

XLONG _atbl[]={                /* atan (2^-i) */
     0.785398163397448309 *MBIT,    /* i=0 */
     0.463647609000806116 *MBIT,
     0.244978663126864154 *MBIT,
     0.124354994546761435 *MBIT,
    0.0624188099959573484 *MBIT,
    0.0312398334302682762 *MBIT,
    0.0156237286204768308 *MBIT,
   0.00781234106010111129 *MBIT,
   0.00390623013196697182 *MBIT,
   0.00195312251647881868 *MBIT,
   0.00097656218955931943 *MBIT,
  0.000488281211194898275 *MBIT,
  0.000244140620149361764 *MBIT,
  0.000122070311893670204 *MBIT,
   6.1035156174208775e-05 *MBIT,
  3.05175781155260968e-05 *MBIT,
  1.52587890613157621e-05 *MBIT,
  7.62939453110197026e-06 *MBIT,
  3.81469726560649628e-06 *MBIT,
  1.90734863281018703e-06 *MBIT,
  9.53674316405960879e-07 *MBIT,
   4.7683715820308886e-07 *MBIT,
  2.38418579101557982e-07 *MBIT,
  1.19209289550780685e-07 *MBIT,
  5.96046447753905544e-08 *MBIT,
  2.98023223876953037e-08 *MBIT,
  1.49011611938476551e-08 *MBIT,
  7.45058059692382798e-09 *MBIT,
  3.72529029846191404e-09 *MBIT,
  1.86264514923095703e-09 *MBIT,
  9.31322574615478515e-10 *MBIT,
  4.65661287307739257e-10 *MBIT,
  2.32830643653869629e-10 *MBIT,
  1.16415321826934814e-10 *MBIT,
  5.82076609134674072e-11 *MBIT,
  2.91038304567337036e-11 *MBIT,
  1.45519152283668518e-11 *MBIT,
   7.2759576141834259e-12 *MBIT,
  3.63797880709171295e-12 *MBIT,
  1.81898940354585648e-12 *MBIT,
  9.09494701772928238e-13 *MBIT,
  4.54747350886464119e-13 *MBIT,
  2.27373675443232059e-13 *MBIT,
   1.1368683772161603e-13 *MBIT,
  5.68434188608080149e-14 *MBIT,
  2.84217094304040074e-14 *MBIT,
  1.42108547152020037e-14 *MBIT,
  7.10542735760100186e-15 *MBIT,
  3.55271367880050093e-15 *MBIT,
  1.77635683940025046e-15 *MBIT,
  8.88178419700125232e-16 *MBIT,
  4.44089209850062616e-16 *MBIT,
  2.22044604925031308e-16 *MBIT,
  1.11022302462515654e-16 *MBIT,
   5.5511151231257827e-17 *MBIT,
  2.77555756156289135e-17 *MBIT,
  1.38777878078144568e-17 *MBIT,
  6.93889390390722838e-18 *MBIT,
  3.46944695195361419e-18 *MBIT,
  1.73472347597680709e-18 *MBIT,
  8.67361737988403547e-19 *MBIT,
  4.33680868994201774e-19 *MBIT,
  2.16840434497100887e-19 *MBIT,
  1.08420217248550443e-19 *MBIT    /* i=63 */

};
