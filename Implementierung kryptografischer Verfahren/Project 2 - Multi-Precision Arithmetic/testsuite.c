/*! \file testsuite.c
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

#include "testsuite.h"
#include "mpa_algs.h"
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

#define CVAL "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"


/*Prototypes*/
void __report_error(int round, mpz_t a, mpz_t b, mpz_t c_ref, mpz_t c);
void __setup_rng();
void __gen_rnumber(mpz_t rn, unsigned long int length);
int __test_school_add (int rounds, unsigned long int length);
int __rtest_school_add (int rounds);
int __stest_school_add ();
int __test_mul_limb (int rounds, unsigned long int length);
int __stest_mul_limb ();
int __test_mul_base (int rounds, unsigned long int length);
int __stest_mul_base ();
int __test_school_mul (int rounds, unsigned long int length);
int __rtest_school_mul (int rounds);
int __test_rec_mul (void (*rec_mul) (mpz_t,mpz_t,mpz_t), char* alg, int rounds, unsigned long int length);
int __stest_mul (void (*mul) (mpz_t,mpz_t,mpz_t), char* alg);
int __test_red (int rounds, unsigned long int length);


/* Global variable for storing state of gmp's random number generator */
gmp_randstate_t __rand_state;


int test_school_add ()
{
  int tests = 7;
  int passed = 0;

  __setup_rng();
  
  printf("\n*** mpz_school_add tests ***\n");

  passed += __stest_school_add();
  passed += __test_school_add(1000, 100);
  passed += __test_school_add(1000, 512);
  passed += __test_school_add(1000, 1024);
  passed += __rtest_school_add(1000);

  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}

int test_mul_limb ()
{
  int tests = 7;
  int passed = 0;

  __setup_rng();

  printf("\n\n*** mpz_mul_limb tests ***\n");

  passed += __stest_mul_limb();  
  passed += __test_mul_limb(1000, 100);
  passed += __test_mul_limb(1000, 512);
  passed += __test_mul_limb(1000, 1024);

  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}

int test_mul_base ()
{
  int tests = 7;
  int passed = 0;

  __setup_rng();

  printf("\n\n*** mpz_mul_base tests ***\n");

  passed += __stest_mul_base();    
  passed += __test_mul_base(1000, 100);
  passed += __test_mul_base(1000, 512);
  passed += __test_mul_base(1000, 1024);

  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}

int test_school_mul ()
{
  int tests = 11;
  int passed = 0;

  __setup_rng();

  printf("\n\n*** mpz_school_mul tests ***\n");

  passed += __stest_mul(mpz_school_mul, "mpz_school_mul");  
  passed += __test_school_mul(1000, 100);
  passed += __test_school_mul(1000, 512);
  passed += __test_school_mul(1000, 1024);
  passed += __rtest_school_mul(1000);

  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}

int test_rec_mul ()
{
  int tests = 10;
  int passed = 0;

  __setup_rng();

  printf("\n\n*** mpz_rec_mul tests ***\n");

  passed += __stest_mul(mpz_rec_mul, "mpz_rec_mul");    
  passed += __test_rec_mul(mpz_rec_mul, "mpz_rec_mul", 1000, 100);
  passed += __test_rec_mul(mpz_rec_mul, "mpz_rec_mul", 1000, 512);
  passed += __test_rec_mul(mpz_rec_mul, "mpz_rec_mul", 1000, 1024);

  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}

int test_karatsuba_mul ()
{
  int tests = 10;
  int passed = 0;

  __setup_rng();

  printf("\n\n*** mpz_karatsuba_mul tests ***\n");

  passed += __stest_mul(mpz_karatsuba_mul, "mpz_karatsuba_mul");  
  passed += __test_rec_mul(mpz_karatsuba_mul, "mpz_karatsuba_mul", 1000, 100);
  passed += __test_rec_mul(mpz_karatsuba_mul, "mpz_karatsuba_mul", 1000, 512);
  passed += __test_rec_mul(mpz_karatsuba_mul, "mpz_karatsuba_mul", 1000, 1024);

  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}

int test_montgomery_red ()
{
  int tests = 3;
  int passed = 0;
	
  __setup_rng();
	
  printf("\n\n*** mpz_montgomery_red tests ***\n");
	
  passed += __test_red(1000, 100);
  passed += __test_red(1000, 512);
  passed += __test_red(1000, 1024);
	
  printf("\n*** %d/%d tests passed ***\n", passed, tests);

  gmp_randclear(__rand_state);

  return (passed == tests);
}




/* Internal functions */

void __report_error(int round, mpz_t a, mpz_t b, mpz_t c_ref, mpz_t c)
{
  printf("\nAn error has occured in round %d:\n", round);
  gmp_printf ("Operand a = %Zx\n", a);
  gmp_printf ("Operand b (i) = %Zx\n", b);
  gmp_printf("Your result c = %Zx\n", c);
  gmp_printf("Correct result c_ref = %Zx\n", c_ref);
}

void __setup_rng()
{
  gmp_randinit_default(__rand_state);  
  gmp_randseed_ui(__rand_state, time(NULL));
} 

void __gen_rnumber(mpz_t rn, unsigned long int length)
{

  mpz_rrandomb(rn,__rand_state,length);

}

int __test_school_add (int rounds, unsigned long int length)
{
  mpz_t a;
  mpz_t b;
  mpz_t c, c_ref;
  int i;

  printf("\nTesting using %lu-bit operands, %d rounds ...", length, rounds);
  fflush(stdout);
	
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init(c_ref);

  for (i = 0; i < rounds; i++)
  {
    /* Avoid special case where result variable c != 0 */
    mpz_set_ui(c,0);
    mpz_set_ui(c_ref,0);      

    __gen_rnumber(a, length);
    __gen_rnumber(b, length);
      
    mpz_add(c_ref,a,b);
    mpz_school_add(c,a,b);
    
    if (mpz_cmp(c_ref,c) != 0)
	{
	  __report_error(i, a, b, c_ref, c);
            mpz_clear(a);
            mpz_clear(b);
            mpz_clear(c_ref);
  	    mpz_clear(c); 
	  return 0;
 	}
  }


  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c); 

  printf("passed.\n");
  return 1;
}

int __rtest_school_add (int rounds)
{
  mpz_t a;
  mpz_t b;
  mpz_t c, c_ref;
  unsigned long int op_len_a, op_len_b;
  int i;

  printf("\nTesting using random-length operands, %d rounds ...", rounds);
  fflush(stdout);
	
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init(c_ref);


  for (i = 0; i < rounds; i++)
  {
     /* Avoid special case where result variable != 0 */
     mpz_set_ui(c,0);
     mpz_set_ui(c_ref,0);      

     __gen_rnumber(a, 12);
     __gen_rnumber(b, 12);

     op_len_a = mpz_get_ui(a);
     op_len_b = mpz_get_ui(b);

     __gen_rnumber(a, op_len_a);
     __gen_rnumber(b, op_len_b);

     mpz_add(c_ref,a,b);
     mpz_school_add(c,a,b);

     if (mpz_cmp(c_ref,c) != 0)
	 {
	   __report_error(i, a, b, c_ref, c);
           mpz_clear(a);
	   mpz_clear(b);
	   mpz_clear(c_ref);
	   mpz_clear(c);
	   return 0;
 	 }
  } 


  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c);
  
  printf("passed.\n");
  return 1;
}

/* Special tests to detect frequent implementation errors */
int __stest_school_add ()
{
  mpz_t a;
  mpz_t b;
  mpz_t c, c_ref;
  int passed;

  passed = 0;

  /* Special case 1: b := 0 */
  printf("\nTesting special case b := 0 ...");
  fflush(stdout);
	
  mpz_init_set_str(a, "7f00007ffffffffffff801f", 16);
  mpz_init_set_ui(b, 0);
  mpz_init(c);
  mpz_init(c_ref);

  mpz_add(c_ref,a,b);
  mpz_school_add(c,a,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
      __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }
  

  /* Special case 2: c != 0, mpz_size(c) > max( mpz_size(a), mpz_size(b) ) */
  printf("\nTesting special case c != 0, mpz_size(c) > max(mpz_size(a), mpz_size(b)) ...");
  fflush(stdout);
	
  mpz_set_str(a, "ccffffffff00ffe001fffe0", 16);
  mpz_set_str(b, "7f00007ffffffffffff801f", 16);
  mpz_set_str(c, CVAL, 16);
  mpz_set(c_ref,c);

  mpz_add(c_ref,a,b);
  mpz_school_add(c,a,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  /* Special case 3: a := a + b, mpz_size(a) < mpz_size(b); */
  printf("\nTesting special case a := a + b, mpz_size(a) < mpz_size(b) ...");
  fflush(stdout);
	
  mpz_set_str(a, "ffffffffff00ffe001fffe0", 16);
  mpz_set_str(b, "ffffff9fff83ff007fff003f0000001ffffffffffffff80007e003fffc1fffffc0001fffe000010000000000000f", 16);
  mpz_set(c,a);
  mpz_set(c_ref,a);

  mpz_add(c_ref,c_ref,b);
  mpz_school_add(c,c,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c);

  return passed;
}

int __test_mul_limb (int rounds, unsigned long int length)
{
  mpz_t a;
  mpz_t b,b_ui;
  mpz_t c, c_ref;
  int i;

  mpz_init(a);
  mpz_init(b);
  mpz_init(b_ui);
  mpz_init(c);
  mpz_init(c_ref);

  printf("\nTesting using %lu-bit operand, %d rounds ...", length, rounds);
  fflush(stdout);
	
  for (i = 0; i < rounds; i++)
  {
     /* Avoid special case where result variable != 0 */
     mpz_set_ui(c,0);
     mpz_set_ui(c_ref,0);      

     __gen_rnumber(a, length);
     __gen_rnumber(b, length);
      
     mpz_mul_ui(c_ref,a,mpz_get_ui(b));
     mpz_mul_limb(c,a,mpz_get_ui(b));
      
     if (mpz_cmp(c_ref,c) != 0)
	 {
	   mpz_set_ui(b_ui, mpz_get_ui(b));
	   __report_error(i, a, b_ui, c_ref, c);
		mpz_clear(a);
		mpz_clear(b);
		mpz_clear(b_ui);
		mpz_clear(c_ref);
		mpz_clear(c);
	   return 0;
 	 }
  }

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(b_ui);
  mpz_clear(c_ref);
  mpz_clear(c);

  printf("passed.\n");
  return 1;
}

/* Special tests to detect frequent implementation errors */
int __stest_mul_limb ()
{
  mpz_t a, bmp;
  mp_limb_t b;
  mpz_t c, c_ref;
  int passed;

  passed = 0;
  mpz_init(bmp);

  /* Special case 1: c != 0, mpz_size(c) > mpz_size(a), b = 0,1,2 */
  mpz_init_set_str(a, "ccffffffff00ffe001fffe0", 16);
  mpz_init_set_str(c, CVAL, 16);
  mpz_init_set(c_ref,c);

  for (b = 0; b <=2; b++)
  {
     printf("\nTesting special case c != 0, mpz_size(c) > mpz_size(a), b := %lu ...", (unsigned long)b);
     fflush(stdout);
		
     mpz_mul_ui(c_ref,a,b);
     mpz_mul_limb(c,a,b);

     if (mpz_cmp(c_ref,c) != 0)
	 {
	   mpz_set_ui(bmp, b);
	   __report_error(0, a, bmp, c_ref, c);
	 }
     else
	 {
	   printf("passed.\n");
	   passed++;
	 }
  }

  /* Special case 3: a := a * b; */
  printf("\nTesting special case a := a * b ...");
  fflush(stdout);
	
  mpz_set_str(a, "ffffffffff00ffe001fffe0", 16);
  b = 2734;
  mpz_set(c,a);
  mpz_set(c_ref,a);

  mpz_mul_ui(c_ref,c_ref,b);
  mpz_mul_limb(c,c,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    mpz_set_ui(bmp, b);
    __report_error(0, a, bmp, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }
  
  mpz_clear(a);
  mpz_clear(bmp);
  mpz_clear(c_ref);
  mpz_clear(c);

  return passed;
}

int __test_mul_base (int rounds, unsigned long int length)
{
  mpz_t a;
  mpz_t b, b_ui;
  mpz_t c, c_ref;
  unsigned long int bui;
  int i;

  printf("\nTesting using %lu-bit operand, %d rounds ...", length, rounds);
  fflush(stdout);
	
  mpz_init(a);
  mpz_init(b);
  mpz_init(b_ui);
  mpz_init(c);
  mpz_init(c_ref);


  for (i = 0; i < rounds; i++)
  {
    /* Avoid special case where result variable != 0 */
    mpz_set_ui(c,0);
    mpz_set_ui(c_ref,0);      

    __gen_rnumber(a, length);
    __gen_rnumber(b, 16);

    bui = mpz_get_ui(b);
    mpz_mul_base(c,a,bui);
    mpz_mul_2exp(c_ref,a,bui*mp_bits_per_limb);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  mpz_set_ui(b_ui, mpz_get_ui(b));
	  __report_error(i , a, b_ui, c_ref, c);
   	  mpz_clear(a);
  	  mpz_clear(b);
  	  mpz_clear(b_ui);
  	  mpz_clear(c_ref);
  	  mpz_clear(c);
	  return 0;
 	}
  }


  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(b_ui);
  mpz_clear(c_ref);
  mpz_clear(c);

  printf("passed.\n");
  return 1;
}

/* Special tests to detect frequent implementation errors */
int __stest_mul_base ()
{
  mpz_t a, bmp;
  mp_limb_t b;
  mpz_t c, c_ref;
  int passed;

  passed = 0;
  mpz_init(bmp);
  mpz_init(a);
  mpz_init(c);
  mpz_init(c_ref);

  /* Special case 1: c != 0, mpz_size(c) > mpz_size(a), i = 0,1,2 */
  for (b = 0; b <=2; b++)
  {
    printf("\nTesting special case c != 0, mpz_size(c) > mpz_size(a), i := %lu ...", (unsigned long)b);
    fflush(stdout);
		
    mpz_set_str(a, "ccffffffff00ffe001fffe0", 16);
    mpz_set_str(c, CVAL, 16);
    mpz_set(c_ref,c);

    mpz_mul_2exp(c_ref,a,b * mp_bits_per_limb);
    mpz_mul_base(c,a,b);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  mpz_set_ui(bmp, b);
	  __report_error(0, a, bmp, c_ref, c);
	}
    else
	{
	  printf("passed.\n");
	  passed++;
	}
  }

  /* Special case 3: a := a * B^i; */
  printf("\nTesting special case a := a * B^i ...");
  mpz_set_str(a, "ffffffffff00ffe001fffe0", 16);
  b = 17;
  mpz_set(c,a);
  mpz_set(c_ref,a);

  mpz_mul_2exp(c_ref,c_ref,b * mp_bits_per_limb);
  mpz_mul_base(c,c,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    mpz_set_ui(bmp, b);
    __report_error(0, a, bmp, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  mpz_clear(a);
  mpz_clear(bmp);
  mpz_clear(c_ref);
  mpz_clear(c);

  return passed;
}

int __test_school_mul (int rounds, unsigned long int length)
{
  mpz_t a;
  mpz_t b;
  mpz_t c, c_ref;
  int i;

  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init(c_ref);

  printf("\nTesting using %lu-bit operands, %d rounds ...", length, rounds);
  fflush(stdout);
	
  for (i = 0; i < rounds; i++)
  {
    /* Avoid special case where result variable != 0 */
    mpz_set_ui(c,0);
    mpz_set_ui(c_ref,0);      

    __gen_rnumber(a, length);
    __gen_rnumber(b, length);
      
    mpz_mul(c_ref,a,b);
    mpz_school_mul(c,a,b);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  __report_error(i, a, b, c_ref, c);
	  mpz_clear(a);
	  mpz_clear(b);
	  mpz_clear(c_ref);
	  mpz_clear(c);
	  return 0;
 	}
  }

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c);

  printf("passed.\n");
  return 1;
}

int __rtest_school_mul (int rounds)
{
  mpz_t a;
  mpz_t b;
  mpz_t c, c_ref;
  unsigned long int op_len_a, op_len_b;
  int i;

  printf("\nTesting using random-length operands, %d rounds ...", rounds);
  fflush(stdout);
	
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init(c_ref);


  for (i = 0; i < rounds; i++)
  {
    /* Avoid special case where result variable != 0 */
    mpz_set_ui(c,0);
    mpz_set_ui(c_ref,0);      

    __gen_rnumber(a, 12);
    __gen_rnumber(b, 12);

    op_len_a = mpz_get_ui(a);
    op_len_b = mpz_get_ui(b);

    __gen_rnumber(a, op_len_a);
    __gen_rnumber(b, op_len_b);
      
    mpz_mul(c_ref,a,b);
    mpz_school_mul(c,a,b);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  __report_error(i, a, b, c_ref, c);
	  mpz_clear(a);
	  mpz_clear(b);
	  mpz_clear(c_ref);
	  mpz_clear(c); 
	  return 0;
	}
  }


  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c);

  printf("passed.\n");
  return 1;
}

int __test_rec_mul (void (*rec_mul) (mpz_t,mpz_t,mpz_t), char* alg, int rounds, unsigned long int length)
{
  mpz_t a;
  mpz_t b;
  mpz_t c, c_ref;
  unsigned long int i;

  printf("\nTesting using %lu-bit operands, %d rounds ...", length, rounds);
  fflush(stdout);
	
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init(c_ref);


  for (i = 0; i < rounds; i++)
  {
    /* Avoid special case where result variable != 0 */
    mpz_set_ui(c,0);
    mpz_set_ui(c_ref,0);      

    __gen_rnumber(a, length);
    __gen_rnumber(b, length);

    while (mpz_size(a) != mpz_size(b))
	{
	  __gen_rnumber(a, length);
	  __gen_rnumber(b, length);

	  if (mpz_size(a) > mpz_size(b)) 
	    mpz_add(b,a,b);
	  else
	    mpz_add(a,a,b);
	}

    mpz_mul(c_ref,a,b);
    rec_mul(c,a,b);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  __report_error(i, a, b, c_ref, c);

 	  mpz_clear(a);
 	  mpz_clear(b);
	  mpz_clear(c_ref);
 	  mpz_clear(c);
	  return 0;
 	}
  }


  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c);

  printf("passed.\n");
  return 1;
}

/* Special tests to detect frequent implementation errors */
int __stest_mul (void (*mul) (mpz_t,mpz_t,mpz_t), char* alg)
{
  mpz_t a;
  unsigned long int bui;
  mpz_t b;
  mpz_t c, c_ref;
  int passed;

  passed = 0;
  mpz_init(a);
  mpz_init(b);
  mpz_init(c);
  mpz_init(c_ref);

  for (bui = 0; bui <= 2; bui++)
  {
    printf("\nTesting special case c != 0, mpz_size(c) > mpz_size(a), b := %lu ...", bui);

    /* Special case 1: c != 0, mpz_size(c) > mpz_size(a), b = 0,1,2 */
    mpz_set_str(a, "ccffffffff00ffe001fffe0", 16);
    mpz_set_str(c, CVAL, 16);

    mpz_set(c_ref,c);
    mpz_set_ui(b,bui);

    mpz_mul(c_ref,a,b);
    mul(c,a,b);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  __report_error(0, a, b, c_ref, c);
	}
    else
	{
	  printf("passed.\n");
	  passed++;
	}
  }

  /* Special case 2: a := a * b; */
  printf("\nTesting special case a := a * b ...");
  mpz_set_str(a, "ffffffffff00ffe001fffe0", 16);
  mpz_set_str(b, "ffffff3647ff23ff00f00fe001feaff45e0a3efff0031", 16);
  mpz_set(c,a);
  mpz_set(c_ref,a);

  mpz_mul(c_ref,c_ref,b);
  mul(c,c,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  /* Special case 3a: c := a * b, where mpz_size(a) == mpz_size(b) = 2^k; */
  printf("\nTesting special case mpz_size(a) == mpz_size(b) == 2^2 (1) ...");
  mpz_set_str(a, "ffffffffccff5678ee7898fe67efcefe", 16);
  mpz_set_str(b, "ffffff3647ff23ff00f00fe001feaff4", 16);
  mpz_set_ui(c,0);
  mpz_set_ui(c_ref,0);

  mpz_mul(c_ref,a,b);
  mul(c,a,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  /* Special case 3b: c := a * b, where mpz_size(a) == mpz_size(b) = 2^k;*/
  printf("\nTesting special case mpz_size(a) == mpz_size(b) == 2^2 (2) ...");
  mpz_set_str(a, "ffffffffccff56780000000067efcefe", 16);
  mpz_set_str(b, "ffffff3647ff23ff00f00fe001feaff4", 16);
  mpz_set_ui(c,0);
  mpz_set_ui(c_ref,0);

  mpz_mul(c_ref,a,b);
  mul(c,a,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  /* Special case 3c: c := a * b, where mpz_size(a) == mpz_size(b) = 2^k; */
  printf("\nTesting special case mpz_size(a) == mpz_size(b) == 2^1 ...");
  mpz_set_str(a, "ffffffff00000000", 16);
  mpz_set_str(b, "cceaffcc00000000", 16);
  mpz_set_ui(c,0);
  mpz_set_ui(c_ref,0);

  mpz_mul(c_ref,a,b);
  mul(c,a,b);

  if (mpz_cmp(c_ref,c) != 0)
  {
    __report_error(0, a, b, c_ref, c);
  }
  else
  {
    printf("passed.\n");
    passed++;
  }

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(c_ref);
  mpz_clear(c);

  return passed;
}

int __test_red (int rounds, unsigned long int length)
{
  mpz_t a, a_tilde;
  mpz_t b, b_tilde;
  mpz_t p, q;
  mpz_t m, m_prime;
  mpz_t c, c_tilde, c_ref;
  int i;
  
  printf("\nTesting using %lu-bit operand, %d rounds ...", length, rounds);
  fflush(stdout);

  mpz_init(a);
  mpz_init(b);
  mpz_init(a_tilde);
  mpz_init(b_tilde);
  mpz_init(p);
  mpz_init(q);
  mpz_init(m);
  mpz_init(m_prime);
  mpz_init(c);
  mpz_init(c_tilde);
  mpz_init(c_ref);

  for (i = 0; i < rounds; i++)
  {
    mpz_set_ui(c,0);
    mpz_set_ui(c_ref,0);

    __gen_rnumber(a, length);
    __gen_rnumber(b, length);
	
    mpz_urandomb(p,__rand_state, length/2);
	while(mpz_probab_prime_p(p, 1)<1)
	{
		mpz_urandomb(p,__rand_state, length/2);
	}
	
    mpz_urandomb(q,__rand_state, length/2);
	while(mpz_probab_prime_p(q, 1)<1)
	{
		mpz_urandomb(q,__rand_state, length/2);
	}
	
	mpz_mul(m, p, q);

	mpz_mod(a, a, m);
	mpz_mod(b, b, m);

	mpz_mul(c_ref, a, b);
	mpz_mod(c_ref, c_ref, m);
	
	mpz_montgomery_get_m_prime(m_prime, m);
	mpz_montgomery_trans(a_tilde, a, m);
	mpz_montgomery_trans(b_tilde, b, m);
	mpz_mul(c_tilde, a_tilde, b_tilde);
	mpz_montgomery_red(c, c_tilde, m, m_prime);
	mpz_montgomery_red(c, c, m, m_prime);

    if (mpz_cmp(c_ref,c) != 0)
	{
	  __report_error(i , a, b, c_ref, c);
	  mpz_clear(a);
	  mpz_clear(b);
	  mpz_clear(a_tilde);
	  mpz_clear(b_tilde);
	  mpz_clear(p);
	  mpz_clear(q);
	  mpz_clear(m);
	  mpz_clear(m_prime);
	  mpz_clear(c);
	  mpz_clear(c_tilde);
	  mpz_clear(c_ref);
	  return 0;
 	}
  }

  mpz_clear(a);
  mpz_clear(b);
  mpz_clear(a_tilde);
  mpz_clear(b_tilde);
  mpz_clear(p);
  mpz_clear(q);
  mpz_clear(m);
  mpz_clear(m_prime);
  mpz_clear(c);
  mpz_clear(c_tilde);
  mpz_clear(c_ref);

  printf("passed.\n");
  return 1;
}