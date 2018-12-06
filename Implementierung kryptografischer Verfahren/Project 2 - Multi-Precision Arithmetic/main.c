/*! \file main.c
 *  \brief Main function simply invokes all test functions from testsuite.
 *  \author 
 *  \date WS18/19
 *  \version 0.3
 *
 *  Lecture: "Implementierung kryptographischer Verfahren", WS18/19.
 *  MPA-Project.
 *
 * !!! You don't need to change anything here !!!
 */

#include "testsuite.h" 
 
int main ()
{
  test_school_add();
  test_mul_limb();
 // test_mul_base();
  //  test_school_mul();
  // test_rec_mul();
  // test_karatsuba_mul();
  // test_montgomery_red();
  return 0;
}
