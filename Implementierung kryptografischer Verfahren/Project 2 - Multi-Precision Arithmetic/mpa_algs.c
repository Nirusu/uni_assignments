/*! \file mpa_algs.c
 *  \brief Implementation of basic MPA functions.
 *  \author Nils Hanke, 108016214085
 *  \date WS18/19
 *  \version 0.3
 *
 *  Lecture: "Implementierung kryptographischer Verfahren", WS18/19.
 *  MPA-Project.
 *  Solution to implementation assignments.
 *
 *  THIS IS THE PART WHERE YOU HAVE TO PUT YOUR CODE!
 */

#include "mpa_algs.h"
#include "gmp_ext.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/**
 * Function mpz_school_add.
 * Computes the sum c of two multi-precision
 * integers a and b.
 *
 * @param c the multi-precision sum a + b.
 * @param a the first multi-precision operand.
 * @param b the second multi-precision operand.
 */
void mpz_school_add(mpz_t c, mpz_t a, mpz_t b)
{
    mp_limb_t carry;
    mp_limb_t a_limb;
    mp_limb_t b_limb;
    mp_limb_t temp;

    // loop variables
    int i = 0;
    int size = 0;
    int size_a = mpz_size(a);
    int size_b = mpz_size(b);

    // assign result which is going to end up as our c. Required so we don't trash c in special cases.
    mpz_t result;
    mpz_init(result);
    mpz_set(result, c);

    // Use the larger number as our boundary for the for-loop
    if (size_a >= size_b)
        size = size_a;
    else
        size = size_b;

    mpz_set_str(result, "0", 10);
    // Start with 0 as carry
    carry = 0;

    // For every digit of the (larger) multi-precision number, get the single digit and add them. If we get a carry, save it and add in for the next digit at the beginning.
    for (i = 0; i <= size + 1; i++)
    {
        a_limb = mpz_getlimbn(a, i);
        b_limb = mpz_getlimbn(b, i);
        carry = mp_add_limb(&temp, a_limb, carry);
        carry += mp_add_limb(&temp, temp, b_limb);
        mpz_setlimbn(result, temp, i);
    }

    // If the last addition gave us a carry, add it to the most significant digit
    mpz_setlimbn(result, carry, i+1);

    // Clear the temporary result variable
    mpz_set(c, result);
    mpz_clear(result);
}


/**
 * Function mpz_mul_limb.
 * Computes the product c of a multi-precision integer a
 * and a single-precision integer b.
 *
 * @param c the multi-precision product a * b.
 * @param a the multi-precision operand.
 * @param b the single-precision operand.
 */
void mpz_mul_limb(mpz_t c, mpz_t a, mp_limb_t b)
{
    // We need two carrys now. One for the result of the multiplication, a second one which is going to be added after the result with the carry value of the previous digit
    mp_limb_t carry_1;
    mp_limb_t carry_2;
    mp_limb_t a_limb;
    mp_limb_t temp;


    // loop variables
    int i = 0;

    // assign result which is going to end up as our c. Required so we don't trash c in special cases.
    mpz_t result;
    mpz_init(result);
    mpz_set(result, c);

    mpz_set_str(result, "0", 10);
    // Start with 0 as carry
    carry_1 = 0;
    carry_2 = 0;

    // For every digit of the (larger) multi-precision number, get the single digit and multiply it. If we get a carry, save it (carry_1) and add it for the next digit *after* multiplication (carry_2).
    for (i = 0; i <= mpz_size(a) + 1; i++)
    {
        a_limb = mpz_getlimbn(a, i);
        carry_1 = mp_mul_limb(&temp, a_limb, b);
        carry_1 += mp_add_limb(&temp, temp, carry_2);
        carry_2 = carry_1;
        mpz_setlimbn(result, temp, i);
    }

    // If the last addition gave us a carry, add it to the most significant digit
    mpz_setlimbn(result, carry_2, i+1);

    // Clear the temporary result variable
    mpz_set(c, result);
    mpz_clear(result);


}


/**
 * Function mpz_mul_base.
 * Computes the product c of a multi-precision integer a
 * and the i-th power of the base B.
 *
 * @param c the multi-precision product a * B^i.
 * @param a the multi-precision operand.
 * @param i the base exponent.
 */
void mpz_mul_base(mpz_t c, mpz_t a, mp_size_t i)
{
    mp_limb_t a_limb;

    // Use temporary variable in case a := a...
    mpz_t a_temp;
    mpz_init(a_temp);
    mpz_set(a_temp, a);

    mpz_set_str(c, "0", 10);

    // For every digit, get the current digit and set i digits in the further direction -> left shift by i
    for (int j = mpz_size(a_temp) + 1; j >= 0; j--)
    {
        a_limb = mpz_getlimbn(a_temp, j);
        mpz_setlimbn(c, a_limb, i + j);
    }

    // Clear temporary variable
    mpz_clear(a_temp);
}


/**
 * Function mpz_school_mul.
 * Computes the product c of two multi-precision
 * integers a and b using the schoolbook method.
 *
 * @param c the multi-precision product a * b.
 * @param a the first multi-precision operand.
 * @param b the second multi-precision operand.
 */
void mpz_school_mul(mpz_t c, mpz_t a, mpz_t b)
{
    
    mp_limb_t a_limb;
    
    // Temporary variables for the cases where a, b or c are applied multiple times to the function call
    mpz_t a_temp;
    mpz_t b_temp;
    mpz_init(a_temp);
    mpz_init(b_temp);
    mpz_set(a_temp, a);
    mpz_set(b_temp, b);

    // Temporary variable for our multi-precision result from our single-precision multiplication
    mpz_t temp;
    mpz_init(temp);

    // c = 0
    mpz_set_str(c, "0", 10);

    // For every digit in a, multiply b with a to a temporary variable, shift it to its respective position and add the correct single-precision multiplication to the multi-presicion result
    for (int i = 0; i <= mpz_size(a_temp) + 1; i++)
    {
        a_limb = mpz_getlimbn(a_temp, i);
        mpz_mul_limb(temp, b_temp, a_limb);
        mpz_mul_base(temp, temp, i);
        mpz_school_add(c, c, temp);
    }

    // Clear out temporary variables
    mpz_clear(a_temp);
    mpz_clear(b_temp);
    mpz_clear(temp);
}


/**
 * Function mpz_rec_mul.
 * Computes the product c of two multi-precision
 * integers a and b using a recursive multiplication method.
 *
 * @param c the multi-precision product a * b.
 * @param a the first multi-precision operand.
 * @param b the second multi-precision operand.
 */
void mpz_rec_mul(mpz_t c, mpz_t a, mpz_t b)
{



}


/**
 * Function mpz_karatsuba_mul.
 * Computes the product c of two multi-precision
 * integers a and b using Karatsuba's multiplication method.
 *
 * @param c the multi-precision product a * b.
 * @param a the first multi-precision operand.
 * @param b the second multi-precision operand.
 */
void mpz_karatsuba_mul(mpz_t c, mpz_t a, mpz_t b)
{



}


/**
 * Function mpz_montgomery_trans.
 * Performs montgomery transformation. Maps the operands
 * to another representation system.
 *
 * @param x_tilde the transformed multi-precision result.
 * @param x the multi-precision operand.
 */

void mpz_montgomery_trans(mpz_t x_tilde, mpz_t x, mpz_t m)
{

}


/**
 * Function mpz_montgomery_get_m_prime.
 * Computes the negative inverse of the modulus. The result
 * m' is needed for montgomery reduction
 *
 * @param m_prime the negative inverse of m.
 * @param m the modulus.
 */
void mpz_montgomery_get_m_prime(mpz_t m_prime, mpz_t m)
{

}


/**
 * Function mpz_montgomery_red.
 * Computes montgomery reduction of a multi-precision product
 * T in montgomery respresentation system
 *
 * @param c the reduced multi-precision product
 * @param T the input multi-precision product.
 * @param m the modulus.
 * @param m_prime the negative inverse of m.
 */
void mpz_montgomery_red(mpz_t c, mpz_t T, mpz_t m, mpz_t m_prime)
{

}
