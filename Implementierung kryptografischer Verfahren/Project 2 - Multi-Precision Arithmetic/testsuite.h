/*! \file testsuite.h
 *  \author
 *  \date WS18/19
 *  \version 0.3
 *
 *  Lecture: "Implementierung kryptographischer Verfahren", WS18/19.
 *  MPA-Project
 *  Testsuite for implementation assignments.
 *
 *  !!! You don't need to change anything here !!!
 */


#ifndef TESTSUITE_H
#define TESTSUITE_H

/**
 * Function test_school_add.
 * Performs various tests on mpz_school_add and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_school_add();

/**
 * Function test_mul_limb.
 * Performs various tests on mpz_mul_limb and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_mul_limb();

/**
 * Function test_mul_base.
 * Performs various tests on mpz_mul_base and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_mul_base();

/**
 * Function test_school_mul.
 * Performs various tests on mpz_school_mul and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_school_mul();

/**
 * Function test_rec_mul.
 * Performs various tests on mpz_rec_mul and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_rec_mul();

/**
 * Function test_karatsuba_mul.
 * Performs various tests on mpz_karatsuba_mul and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_karatsuba_mul();

/**
 * Function test_montgomery_red.
 * Performs various tests on mpz_montgomery_red and 
 * returns 1 if the function passed all tests and
 * 0 if at least one test failed.
 *
 * @return 1 if all tests passed and 0 else.
 */
int test_montgomery_red ();


#endif /* TESTSUITE_H */
