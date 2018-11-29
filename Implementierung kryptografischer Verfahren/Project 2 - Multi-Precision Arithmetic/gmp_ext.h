/*! \file gmp_ext.h
 *  \author 
 *  \date WS18/19
 *  \version 0.3
 *
 *  Lecture: "Implementierung kryptographischer Verfahren", WS18/19.
 *  MPA-Project
 *  GMP Extension for implementation assigments.
 *
 *  - Offers primitive operations like addition and multiplication 
 *    on single-precision integers (i.e., digits) 
 *    with double-precision results.
 *
 *  - Offers a function for assigning a single-precision value to 
 *    an arbitrary digit of a multi-precision integer.
 *
 *  !!! You don't need to change anything here !!!
 */

#ifndef GMP_EXT_H
#define GMP_EXT_H

#include<gmp.h>


/**
 * Function mpz_setlimbn.
 * Sets a_n of a = (a_k ... a_0) to l.
 * If n is greater than k, 
 * a is increased to size n+1 and
 * the previously unused digits 
 * (a_n-1 to a_k+1) are zeroed out.
 * Leading zeroes are avoided.
 *
 * @param a the multi-precision integer.
 * @param l the single-precision integer (digit).
 * @param n the index.
 */
void mpz_setlimbn (mpz_t a, mp_limb_t l, mp_size_t n)
{
  mp_size_t i;

  if ((l == 0) && (mpz_size(a) == 0))
    return;

  /* Avoid leading zero.*/
  if ((l == 0) && (n >= mpz_size(a)))
    return;

  /* Verify that enough memory is allocated.*/
  if (n >= a->_mp_alloc)
    {
      /* Avoid to continuously allocate small pieces of memory.*/
      _mpz_realloc(a,2 * n + 1);
    }
  
  /* Zero out previously unused digits */
  if (n > mpz_size(a))
    {
      for(i = n; i > mpz_size(a); i--)
	a->_mp_d[i] = 0;

      /* Treat as special case to avoid that i (unsigned long) falls below zero if mpz_size(a) == 0 */
      a->_mp_d[mpz_size(a)] = 0;
    }
  
  a->_mp_d[n] = l;

  /* Adjust size of a.*/ 
  
  /* Eliminate leading zeroes. */
  if ((l == 0) && (mpz_size(a) > 0) && (n == mpz_size(a) - 1))
    {
      /* Check n to assure that the value of i falls not below zero. */
      if (n == 0)
	{
	  a->_mp_size = 0;
	  return;
	}  
      
      i = n;

      while ((i-- > 0) && (a->_mp_d[i] == 0));

      if ((i == 0) && (a->_mp_d[i] == 0))
	a->_mp_size = 0;
      else
	a->_mp_size = (mpz_sgn(a) != -1) ? i+1 : -(i+1);
      return;
    }
  else 
    if (mpz_size(a) < n+1)
    {
      a->_mp_size = (mpz_sgn(a) != -1) ? n+1 : -(n+1);
    }
}

/**
 * Function mp_add_limb.
 * Adds two digits and returns a two-digit result.
 *
 * @param s pointer to the digit where the least significant 
 *          digit of the result should be stored.
 * @param a 1st operand.
 * @param b 2nd operand.
 * @return the carry (i.e., 2nd digit of the result).
 */
inline mp_limb_t mp_add_limb(mp_limb_t* s, mp_limb_t a, mp_limb_t b) { return mpn_add_n(s, &a, &b, 1); }

/**
 * Function mp_mul_limb.
 * Multiplies two digits and returns a two-digit result.
 *
 * @param p pointer to the digit where the least significant 
 *          digit of the result should be stored.
 * @param a 1st operand.
 * @param b 2nd operand.
 * @return the carry (i.e., 2nd digit of the result).
 */
inline mp_limb_t mp_mul_limb(mp_limb_t* p, mp_limb_t a, mp_limb_t b) { return mpn_mul_1(p, &a, 1, b); }

#endif /* GMP_EXT_H */
