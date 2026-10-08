/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 徐明 25303050254
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~(~x&y)&~(x&~y));
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask = x>>31;
  int A = ~x+1;
  return mask & A;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int byte = (x >> srcShift) & 0x000000ff;
  int mask = ~(0x000000ff << dstShift);
  return (x & mask)|(byte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}
// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int mask = 0x0f | (0x0f << 8);
  mask = mask | (mask << 16);

  int lowbit = (x & mask) << 4;
  int highbit = (x >> 4) & mask;
  return lowbit | highbit;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  int lowestZeroBit = ~x & (x + 1);
  int x_fill= x | lowestZeroBit;
  int secondLowestZeroBit = ~x_fill & (1 + x_fill);
  return secondLowestZeroBit;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {

    int s = n & 31;
    int rshift = x >> s;
    int lshift = x << (31 + (~s + 1)) << 1;
    int clearMask = ~((~0) << (31 + (~s +1)) << 1);
    rshift = rshift & clearMask;
    return rshift | lshift;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int s = 1 << n;
  int half = s >> 1;
  int mask = s + ~0;  
  int rem = x & mask;
  int isMid = !(rem ^ half);

  int q = x >> n;
  int midQ = q + (q & 1);
  int normalQ = (x + half) >> n;

  int mask_flag = ~isMid + 1;
  int Q = (mask_flag & midQ) | (~mask_flag & normalQ);
  return Q << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int base = (x & y) + ((x ^ y) >> 1);   // 精确中点的 floor，任意 x,y 不溢出
  int odd = (x ^ y) & 1;                 // 中点是否为 k+0.5
  int sx = x >> 31;
  int sy = y >> 31;
  int sameSign = ~(sx ^ sy);
  int xGtSame = ~((x + ~y + 1) >> 31);   // 同号时 x-y 必不溢出，符号位即比较结果
  int mask1 = ~sx & sy;                  // 异号时 x>=0>y 即 x>y
  int ltMask = mask1 | (sameSign & xGtSame);
return base + (odd & ltMask); 
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
    int sx = x >> 31;
    int sa = a >> 31;
    int sb = b >> 31;
    int nsx = ~sx;
    int nsa = ~sa;
    int nsb = ~sb;
    int sameA = ~(sx ^ sa);
    int sameB = ~(sx ^ sb);
    int leXA_s = (x + ~a) >> 31;
    int leAX_s = (a + ~x) >> 31;
    int leXB_s = (x + ~b) >> 31;
    int leBX_s = (b + ~x) >> 31;
    int leXA = (sx & nsa) | (sameA & leXA_s);
    int leAX = (sa & nsx) | (sameA & leAX_s);
    int leXB = (sx & nsb) | (sameB & leXB_s);
    int leBX = (sb & nsx) | (sameB & leBX_s);
    int in1 = leAX & leXB;
    int in2 = leBX & leXA;
    return !! (in1 | in2);  // 修正返回逻辑
}





// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */


int mul5Sat(int x) {
  int B = (0x19 << 24) | (0x99 << 16) | (0x99 << 8) | 0x99;
  int sum = (x << 2) + x;
  int pos_ovf = ~((x + ~B) >> 31);
  int neg_ovf = (x >> 31) & ((x + B) >> 31);
  int overflow = pos_ovf | neg_ovf;
  int sat_val = (~(1 << 31)) ^ (x >> 31);

  return (overflow & sat_val) | (~overflow & sum);
}
// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>22
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
     int s1 = x + y;
    int s2 = s1 + z;
    
    int sx  = x >> 31;
    int sy  = y >> 31;
    int sz  = z >> 31;
    int s1s = s1 >> 31;
    int s2s = s2 >> 31;
    
    int p1 = ~sx & ~sy & s1s;
    int n1 =  sx &  sy & ~s1s;
    
    int p2 = ~s1s & ~sz & s2s;
    int n2 =  s1s &  sz & ~s2s;
    
    int is_pos = (p1 & (~sz | ~n2)) | (~p1 & ~n1 & p2);
    int is_neg = (n1 & (sz | ~p2)) | (~p1 & ~n1 & n2);
    
    // ★ 修正后的返回逻辑，消除 ~bool 警告
    int result_pos = !!is_pos;
    int result_neg = (!!is_neg) << 31 >> 31;
    return result_pos | result_neg;
}
// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
 //single-precision floating point values(单精度浮点数)的表示方法：1位符号位S，8位指数位E，23位尾数位M
unsigned floatScaleThreeHalves(unsigned uf) {
  // 1. 提取符号、指数、尾数
    unsigned sign = uf & 0x80000000U;
    unsigned exp  = (uf >> 23) & 0xFFU;
    unsigned frac = uf & 0x7FFFFFU;

    if (exp == 0xFFU) return uf;
    if (exp == 0 && frac == 0) return uf;

    unsigned mantissa;
    int e;

    if (exp != 0) {
        mantissa = frac | (1U << 23);
        e = exp ;
        e = e + ~126;
    } else {
        mantissa = frac;
        e = ~125;
    }

    /* 乘以 3 */
    unsigned product = mantissa * 3U;

    /* 归一化到 [2^23, 2^24)，带 RNE 舍入 */
    if (product >= (1U << 25)) {
        /* 需要右移 2 位 */
        unsigned dropped = product & 3U;
        product >>= 2;
        e += 2;
        /* RNE: dropped > 2 进位, dropped == 2 向偶数 */
        if (dropped > 2U || (dropped == 2U && (product & 1U))) {
            product++;
        }
    } else if (product >= (1U << 24)) {
        /* 需要右移 1 位 */
        unsigned dropped = product & 1U;
        product >>= 1;
        e ++;
        if (dropped && (product & 1U)) {
            product++;
        }
    }

    /* 除以 2 */
    e--;

    /* 处理下溢 */
    if (e < -126) {
        int shift = -126 - e;
        if (shift >= 24) return sign;

        unsigned kept = product >> shift;
        unsigned dropped = product & ((1U << shift) - 1U);
        unsigned half = 1U << (shift - 1);

        if (dropped > half || (dropped == half && (kept & 1U))) {
            kept++;
        }

        if (kept >= (1U << 23)) {
            return sign | (1U << 23) | (kept & 0x7FFFFFU);
        }
        return sign | kept;
    }

    if (e > 127) {
        return sign | 0x7F800000U;
    }

    unsigned new_exp = (unsigned)(e + 127);
    unsigned new_frac = product & 0x7FFFFFU;

    return sign | (new_exp << 23) | new_frac;
}
// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xff;
  unsigned frac = uf & 0x7fffff;
  unsigned shift, mask, remainder, half, result;

  if (exp == 0xff)
    return uf;
  if (exp < 126)
    return sign;
  if (exp == 126) {
    if (frac != 0)
      return sign | 0x3f800000;
    return sign;
  }
  if (exp >= 150)
    return uf;

  shift = 150 - exp;
  mask = (1u << shift) - 1;
  remainder = uf & mask;
  half = 1u << (shift - 1);
  result = uf & ~mask;

  if (remainder > half ||
      (remainder == half && (result & (1u << shift))))
    result += 1u << shift;

  return result;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned ux = x;
  unsigned sign = ux >> 31;
  unsigned mag = sign ? (~ux + 1u) : ux;
  unsigned temp = mag;
  unsigned sig, exp;
  int msb = 0;

  if (mag == 0)
    return 0;

  while (temp >> 1) {
    temp >>= 1;
    msb++;
  }

  exp = msb + 127;
  if (msb <= 23) {
    sig = mag << (23 - msb);
  } else {
    int shift = msb - 23;
    unsigned remainder = mag & ((1u << shift) - 1u);
    unsigned halfway = 1u << (shift - 1);

    sig = mag >> shift;
    if (remainder > halfway ||
        (remainder == halfway && (sig & 1u))) {
      sig++;
      if (sig == (1u << 24)) {
        sig >>= 1;
        exp++;
      }
    }
  }

  return (sign << 31) | (exp << 23) | (sig & 0x7fffffu);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 0x55 | (0x55 << 8);
  int m2 = 0x33 | (0x33 << 8);
  int m4 = 0x0f | (0x0f << 8);

  m1 = m1 | (m1 << 16);
  m2 = m2 | (m2 << 16);
  m4 = m4 | (m4 << 16);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  x = x + (x >> 8);
  x = x + (x >> 16);

  return x & 0x3f;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
  {
  int m8 = 0xff | (0xff << 16);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);
  int m16 = 0xff | (0xff << 8);

  x = (x << 16) | ((x >> 16) & m16);
  x = ((x >> 8) & m8) | ((x & m8) << 8);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 1) & m1) | ((x & m1) << 1);

  return x;
  }