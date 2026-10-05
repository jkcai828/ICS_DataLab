/* 
 * CS:APP Data Lab 
 * 
 * 蔡纪坤 24300810016
 * 
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
  /* Move a single 1 to the most significant bit. */
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
  /* Express XOR using only NOT and AND via De Morgan's law. */
	return ~(~x & ~y) & ~(x & y);
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
  /* Use the sign mask to keep -x only when x is negative. */
  int mask = x >> 31;
  return mask & (~x + 1);
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
  /* Extract the source byte, clear the destination byte, then insert it. */
  int ss = src << 3;
  int ds = dst << 3;
  int byte = (x >> ss) & 0xFF;
  int mask = 0xFF << ds;
  return (x & ~mask) | (byte << ds);
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
  /* Mask off sign-extension bits after the arithmetic right shift. */
  int high = 1 << 31;
  int mask = ~((high >> n) << 1);
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
  /* Separate low/high nibbles in every byte and swap their positions. */
  int mask = 0x0F | (0x0F << 8);
  mask = mask | (mask << 16);
  return ((x & mask) << 4) | ((x >> 4) & mask);
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
  /* Turn zero bits into ones, remove the lowest one, then isolate the next. */
  int y = ~x;
  int t = y & (y + ~0);
  return t & (~t + 1);
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
  /* Fold all bits with XOR and invert the final parity bit. */
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
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
  /* Combine a logical right shift with the wrapped bits shifted from the left. */
  int s;
  int high;
  int mask;
  int right;
  int left;
  n = n & 31;
  s = (~n + 1) & 31;
  high = 1 << 31;
  mask = ~((high >> n) << 1);
  right = (x >> n) & mask;
  left = x << s;
  return right | left;
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
  /* Compare the remainder with half and apply round-to-nearest-even. */
  int mask = (1 << n) + ~0;
  int rem = x & mask;
  int half = 1 << (n + ~0);
  int base = x & ~mask;
  int qpar = (x >> n) & 1;
  int gt = ((half + (~rem + 1)) >> 31) & 1;
  int eq = !(rem ^ half);
  int up = gt | (eq & qpar);
  return base + (up << n);
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
  /* Compute an overflow-safe midpoint and break half ties toward x. */
  int xy = x ^ y;
  int base = (x & y) + (xy >> 1);
  int odd = xy & 1;
  int sx = x >> 31;
  int sy = y >> 31;
  int sd = (sx ^ sy) & 1;
  int d = y + (~x + 1);
  int dneg = (d >> 31) & 1;
  int cross = sd & !sx;
  int samegt = (!sd) & dneg;
  int gt = cross | samegt;
  return base + (odd & gt);
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
  /* Compare x with both endpoints safely and accept either endpoint order. */
  int sx = x >> 31;
  int sa = a >> 31;
  int sb = b >> 31;
  int sd1 = sx ^ sa;
  int d1 = x + (~a + 1);
  int lm1 = (sd1 & sx) | (~sd1 & (d1 >> 31));
  int l1 = lm1 & 1;
  int sd2 = sb ^ sx;
  int d2 = b + (~x + 1);
  int lm2 = (sd2 & sb) | (~sd2 & (d2 >> 31));
  int l2 = lm2 & 1;
  int eq1 = !(x ^ a);
  int eq2 = !(x ^ b);
  int same = !(l1 ^ l2);
  return same | eq1 | eq2;
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
  /* Detect whether x exceeds the safe x*5 range, then select product or saturation. */
  int limit = (0x19 << 24) | (0x99 << 16);
  int prod;
  int sx;
  int dpos;
  int posover;
  int dneg;
  int negover;
  int over;
  int tmin;
  int tmax;
  int sat;
  limit = limit | (0x99 << 8);
  limit = limit | 0x99;
  prod = (x << 2) + x;
  sx = x >> 31;
  dpos = limit + (~x + 1);
  posover = (~sx) & (dpos >> 31);
  dneg = x + limit;
  negover = sx & (dneg >> 31);
  over = posover | negover;
  tmin = 1 << 31;
  tmax = ~tmin;
  sat = tmax ^ sx;
  return (over & sat) | (~over & prod);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* Track positive and negative overflow across the two additions. */
  int s = x + y;
  int sx = x >> 31;
  int sy = y >> 31;
  int ss = s >> 31;
  int p1 = (~sx) & (~sy) & ss;
  int n1 = sx & sy & (~ss);
  int t = s + z;
  int sz = z >> 31;
  int st = t >> 31;
  int p2 = (~ss) & (~sz) & st;
  int n2 = ss & sz & (~st);
  int p = p1 | p2;
  int n = n1 | n2;
  int netp = p & ~n;
  int netn = n & ~p;
  int pb = netp & 1;
  int nb = netn & 1;
  return pb + (~nb + 1);
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
unsigned floatScaleThreeHalves(unsigned uf) {
  /* Scale the IEEE-754 significand by 3/2 with round-to-nearest-even. */
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned prod;
  unsigned q;
  unsigned rem;
  unsigned m;

  if (exp == 0xFFu)
      return uf;

  if (exp == 0) {
      prod = frac * 3u;
      q = prod >> 1;
      rem = prod & 1u;
      if (rem && (q & 1u))
          q = q + 1u;
      return sign | q;
  }

  m = (1u << 23) | frac;
  prod = m * 3u;

  if (prod < (1u << 25)) {
      q = prod >> 1;
      rem = prod & 1u;
      if (rem && (q & 1u))
          q = q + 1u;
      if (q >= (1u << 24)) {
          q = q >> 1;
          exp = exp + 1u;
      }
  } else {
      q = prod >> 2;
      rem = prod & 3u;
      if (rem > 2u || (rem == 2u && (q & 1u)))
          q = q + 1u;
      exp = exp + 1u;
  }

  if (exp >= 0xFFu)
      return sign | 0x7F800000u;

  return sign | (exp << 23) | (q & 0x7FFFFFu);
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
  /* Remove fractional bits and round halfway cases to the even integer. */
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned k;
  unsigned mask;
  unsigned rem;
  unsigned base;
  unsigned half;

  if (exp == 0xFFu)
      return uf;

  if (exp < 126u)
      return sign;

  if (exp == 126u) {
      if (frac == 0)
          return sign;
      return sign | 0x3F800000u;
  }

  if (exp >= 150u)
      return uf;

  k = 150u - exp;
  mask = (1u << k) - 1u;
  rem = uf & mask;
  base = uf & ~mask;
  half = 1u << (k - 1u);

  if (rem > half || (rem == half && ((base >> k) & 1u)))
      base = base + (1u << k);
  return base;
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
  /* Build sign, exponent, and fraction fields with correct IEEE-754 rounding. */
  unsigned sign = 0;
  unsigned mag;
  unsigned exp;
  unsigned frac;
  unsigned q;
  unsigned rem;
  unsigned half;
  int p;
  int sh;

  if (x == 0)
      return 0;

  if (x < 0) {
      sign = 0x80000000u;
      mag = ~x;
      mag = mag + 1u;
  } else {
      mag = x;
  }

  p = 31;
  while (((mag >> p) & 1u) == 0)
      p = p - 1;

  exp = p + 127;

  if (p <= 23) {
      frac = (mag << (23 - p)) & 0x7FFFFFu;
  } else {
      sh = p - 23;
      q = mag >> sh;
      rem = mag & ((1u << sh) - 1u);
      half = 1u << (sh - 1);

      if (rem > half || (rem == half && (q & 1u)))
          q = q + 1u;

      if (q >= (1u << 24)) {
          q = q >> 1;
          exp = exp + 1u;
      }
      frac = q & 0x7FFFFFu;
    }

  return sign | (exp << 23) | frac;
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
  /* Count set bits in parallel using progressively wider bit groups. */
  int m1 = 0x55 | (0x55 << 8);
  int m2 = 0x33 | (0x33 << 8);
  int m4 = 0x0F | (0x0F << 8);

  m1 = m1 | (m1 << 16);
  m2 = m2 | (m2 << 16);
  m4 = m4 | (m4 << 16);

  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x + (x >> 4)) & m4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
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
  /* Reverse bits by swapping adjacent 1-, 2-, 4-, 8-, and 16-bit groups. */
  int m16 = 0xFF | (0xFF << 8);
  int m8 = m16 ^ (m16 << 8);
  int m4 = m8 ^ (m8 << 4);
  int m2 = m4 ^ (m4 << 2);
  int m1 = m2 ^ (m2 << 1);

  x = ((x >> 1) & m1) | ((x & m1) << 1);
  x = ((x >> 2) & m2) | ((x & m2) << 2);
  x = ((x >> 4) & m4) | ((x & m4) << 4);
  x = ((x >> 8) & m8) | ((x & m8) << 8);
  x = (x << 16) | ((x >> 16) & m16);
  return x;
}
