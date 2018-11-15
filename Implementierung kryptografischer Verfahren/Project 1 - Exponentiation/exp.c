/* -*- Mode: C; c-file-style: "bsd" -*- */

/*
 * Name:        Nils Hanke
 * Student #:   108016214085
 *
 *
 * Implementierung kryptographischer Verfahren (WS 2018/19)
 * Project I -- Exponentiation
 *
 * C file for exercise 5 from project_exponentiation_WS18.pdf
 */

/*
 * [Please delete this complete comment when you are done.]
 *
 *
 * Before starting any work on this file, please follow the
 * instructions on this course's pages on > moodle.rub.de < for
 * installing GMP (if not yet available on your computer).
 *
 * Afterwards, you should be able to compile this file through a
 * command such as
 *
 *     gcc exp.c -O3 -Wall -l gmp -o exp
 *
 *  or if this does not work for you try:
 *
 *     gcc exp.c -O3 -Wall -l gmp -I my_h_directory -L my_lib_directory -o exp
 *
 * where you replace "my_h_directory" by the path to the directory
 * where you have file gmp.h from the GMP installation, and where you
 * replace "my_lib_directory" by the path to the directory where you
 * have file libgmp.a.
 *
 * This will result in an executable file exp.  Please run it (./exp) to see if everything is working so far.
 * It should print various lines of output.
 *
 *
 * Then, please read exercise 5 to see what you should implement in
 * this file, based on the existing skeleton.  Please insert your name
 * and student number above, where indicated!  Also, please rename
 * this file into exp############.c, where ############ denotes your
 * student number (Matrikelnummer).
 *
 * You may add new functions, global variables, or function arguments
 * as needed.  However, DO NOT CHANGE the interface to the four
 * exponentiation and four ecc functions (i.e., do not make changes to their function
 * arguments)!
 *
 * There will be a penalty for poorly documented code or ill-conceived
 * coding style. On the other hand, detailed inline documentation
 * and a sophisticated code structure can yield bonus points.
 *
 * You also have to implement a small testbench to verify your
 * implementation before taking any timings. You are allowed to use
 * the gmp exponentiation functions for the testbench only!
 * Do not forget seeding your PRNG. The seeding has to be somehow random,
 * but no true randomness is required, a good approach would be to read from
 * /dev/urandom (/dev/random is blocking) if this is too challenging try using
 * the current date and/or time.
 *
 * When you are done and have verified that your program works
 * properly, do not forget to collect the results as requested in
 * exercise 5!
 */




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include <gmp.h> /* GNU Multi Precision library */

int ecc_op_double(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t inputX, mpz_t inputY);
int ecc_op_add(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t operand1_X, mpz_t operand1_Y, mpz_t operand2_X, mpz_t operand2_Y);

/* Prototypes for functions that you need to complete at the end of this file */
int get_random_exponent(mpz_t e, int bits);
int exponentiate_binary(mpz_t result, mpz_t g, mpz_t e, mpz_t modulus, long *count_S, long *count_M);
int exponentiate_k_ary(mpz_t result, mpz_t g, mpz_t e, mpz_t modulus, int k, long *count_S, long *count_M);
int exponentiate_sliding_window(mpz_t result, mpz_t g, mpz_t e, mpz_t modulus, int k, long *count_S, long *count_M);

size_t get_fb_LUT_size(size_t maximal_exponent_length);
size_t get_imp_fb_LUT_size(size_t maximal_exponent_length, unsigned window_size);
mpz_t *allocate_fixed_base_LUT(size_t lut_size);
void free_fixed_base_LUT(mpz_t *lut, size_t lut_size);
void precompute_fixed_base_LUT(mpz_t *lut, mpz_t g, mpz_t modulus, size_t lut_size);
void precompute_improved_fixed_base_LUT(mpz_t *lut, mpz_t g, mpz_t modulus, size_t lut_size, unsigned window_size);
int exponentiate_fixed_based(mpz_t result, mpz_t e, mpz_t modulus, mpz_t *lut, size_t maximal_exponent_length, long *count_S, long *count_M);
int exponentiate_improved_fixed_based(mpz_t result, mpz_t e, mpz_t modulus, mpz_t *lut, size_t maximal_exponent_length, unsigned window_size, long *count_S, long *count_M);


int ecc_double_add(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t q, mpz_t inputX, mpz_t inputY, mpz_t factor, long *count_D, long *count_A);
int ecc_naf_double_add(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t q, mpz_t inputX, mpz_t inputY, mpz_t factor, long *count_D, long *count_A);

/* define a global random state here */

gmp_randstate_t randstate;




int main(int argc, char *argv[])
{
	enum {binary, ecc_binary, ecc_naf_binary, k_ary, fixed_base, improved_fixed_base, sliding_window} algorithm;
	struct {int bits; int min_k; int max_k;} test_cases[] = {{160, 3, 7}, {1024, 4, 8}};
	int number_of_operations = 100; /* change this if necessary to adjust the number of exponentiations*/
	int r;


	mpz_t modulus, g, e, result;

	mpz_init(modulus);
	mpz_init(g);
	mpz_init(e);
	mpz_init(result);
	/* you can use this fixed modulus, so you do not need to choose a 1024 bit prime number */
	r = mpz_set_str(modulus, "FFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD1"
			"29024E088A67CC74020BBEA63B139B22514A08798E3404DD"
			"EF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245"
			"E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
			"EE386BFB5A899FA5AE9F24117C4B1FE649286651ECE65381"
			"FFFFFFFFFFFFFFFF", 16);
	assert (r == 0);
	/* 	for simplicity we use a fixed base g but this does not mean, that you can
		assume to always work with this single fixed base like in assignment 6 */
	r = mpz_set_str(g, "FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210"
			"FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210"
			"FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210"
			"FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210"
			"FEDCBA9876543210FEDCBA9876543210FEDCBA9876543210"
			"FEDCBA9876543210", 16);
	assert (r == 0);


	/* TO BE IMPLEMENTED: initialize and seed the GMP random number generator here*/
    
	mpz_t seed;
	mpz_init(seed);

	// read data from /dev/urandom
	unsigned char buffer[1024];
	int fd = open("/dev/urandom", O_RDONLY);
	read(fd, buffer, 1024);
	close(fd);

	// import seed and initialize the random state
	mpz_import(seed, sizeof(buffer), 1, sizeof(buffer[0]), 0, 0, buffer);
	gmp_randinit_default(randstate);
	gmp_randseed(randstate, seed);
	mpz_clear(seed);

	//---------------------------------------------------
	// Testing algorithms
	//---------------------------------------------------
	mpz_t test_e, test_res;
	int test_k = 3;
	long cs, cm;

	mpz_init(test_e);
	mpz_init(test_res);

	// initialize test exponent
	r = mpz_set_str(test_e, "FFFFFC90FDAA22168C234C4C6628B80DC1CD1"
					"29024E088A67CC74020BBEA63B139B22514A08798E3404DD"
					"EF9519B3CD3A431A6DF25F14374FE1356D6D51C245"
					"E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7ED"
					"EE386BFB5A899FA5AE9F649286651ECE65381"
					"FFF125", 16);

	// ecc inits
	mpz_t a, b, p, q; // brainpoolP160r1
	long cA, cD;
	mpz_t basePoint_X, basePoint_Y;
	mpz_t testFactor;
	mpz_t test_resultPoint_X, test_resultPoint_Y;

	mpz_t resultPoint_X, resultPoint_Y;
	// init and set of curve parameters and point coordinates
	mpz_inits(a, b, p, q, basePoint_X, basePoint_Y, testFactor, test_resultPoint_X, test_resultPoint_Y, resultPoint_X, resultPoint_Y, NULL);

	mpz_set_str(p, "E95E4A5F737059DC60DFC7AD95B3D8139515620F", 16);
	mpz_set_str(a, "340E7BE2A280EB74E2BE61BADA745D97E8F7C300", 16);
	mpz_set_str(b, "1E589A8595423412134FAA2DBDEC95C8D8675E58", 16);

	mpz_set_str(q, "E95E4A5F737059DC60DF5991D45029409E60FC09", 16);

	mpz_set_str(basePoint_X, "BED5AF16EA3F6A4F62938C4631EB5AF7BDBCDBC3", 16);
	mpz_set_str(basePoint_Y, "1667CB477A1A8EC338F94741669C976316DA6321", 16);

	mpz_set_str(testFactor, "e95e4a5f737059dc4e7cb133c1d94f942460fc09", 16);

	mpz_set_str(test_resultPoint_X, "30b15f81552a92105f9da2527749edaf21f5571f", 16);
	mpz_set_str(test_resultPoint_Y, "d7d9d0ab3d671851282809a491e912d8851e379f", 16);

	assert (r == 0);

	// calculate g^e for comparison
	mpz_powm(test_res,g,test_e, modulus);

	printf("Testing algorithms:\n");


	// compare results of binary and mpz_pow
	r = exponentiate_binary(result, g, test_e, modulus,
			&cs, &cm);
	if (!mpz_cmp(result, test_res)){
		printf("Binary works properly\n");
	} else {
		printf("Binary failed\n");
	}
	mpz_set_ui(result,0);

	// compare results of k-ary and mpz_pow
	r = exponentiate_k_ary(result, g, test_e, modulus, test_k,
			&cs, &cm);
	if (!mpz_cmp(result, test_res)){
		printf("k-ary works properly\n");
	} else {
		printf("k-ary failed\n");
	}
	mpz_set_ui(result,0);

	// compare results of sliding window and mpz_pow
	r = exponentiate_sliding_window(result, g, test_e, modulus,
			test_k, &cs, &cm);
	// gmp_printf("%Zd \n", result);
	// gmp_printf("%Zd \n", test_res);
	if (!mpz_cmp(result, test_res)){
		printf("Sliding window works properly\n");
	} else {
		printf("Sliding window failed\n");
	}
	mpz_set_ui(result,0);

	//compare results of fixed base and mpz_pow
    unsigned exponent_size = mpz_sizeinbase(test_e, 2);
	size_t lut_size = get_fb_LUT_size(exponent_size);
    mpz_t *lut = allocate_fixed_base_LUT(lut_size);
    precompute_fixed_base_LUT(lut, g, modulus, lut_size);
    exponentiate_fixed_based(result, test_e, modulus, lut, exponent_size, &cs, &cm);
    if (!mpz_cmp(result, test_res)){
		printf("Fixed base works properly\n");
	} else {
		printf("Fixed base failed\n");
	}
	mpz_set_ui(result,0);
    free_fixed_base_LUT(lut, lut_size);

    //compare results of improved fixed base and mpz_pow
    unsigned window_size = 3;
	lut_size = get_imp_fb_LUT_size(exponent_size, window_size);
    mpz_t *imp_lut = allocate_fixed_base_LUT(lut_size);
    precompute_improved_fixed_base_LUT(imp_lut, g, modulus, lut_size, window_size);

    exponentiate_improved_fixed_based(result, test_e, modulus, imp_lut, exponent_size, window_size, &cs, &cm);
    if (!mpz_cmp(result, test_res)){
		printf("Improved fixed base works properly\n");
	} else {
		printf("Improved fixed base failed\n");
	}
	mpz_set_ui(result,0);
    free_fixed_base_LUT(imp_lut, lut_size);

	// free memory
	mpz_clear(test_e);
	mpz_clear(test_res);

	// ecc testing

	r = ecc_double_add(resultPoint_X, resultPoint_Y, a, b, p, q, basePoint_X, basePoint_Y, testFactor, &cD, &cA);
	if (mpz_cmp(test_resultPoint_X, resultPoint_X) == 0 && mpz_cmp(test_resultPoint_Y, resultPoint_Y) == 0){
		printf("double & add works properly\n");
	} else {
		printf("double & add failed\n");
	}

	mpz_set_ui(resultPoint_X, 0);
	mpz_set_ui(resultPoint_Y, 0);

	r = ecc_naf_double_add(resultPoint_X, resultPoint_Y, a, b, p, q, basePoint_X, basePoint_Y, testFactor, &cD, &cA);
	if (mpz_cmp(test_resultPoint_X, resultPoint_X) == 0 && mpz_cmp(test_resultPoint_Y, resultPoint_Y) == 0){
		printf("NAF double & add works properly\n\n");
	} else {
		printf("NAF double & add failed\n\n");
	}


	//---------------------------------------------------
	// Testing Performance
	//---------------------------------------------------

	for (algorithm = binary; algorithm <= sliding_window; algorithm++) {
		int i;


		for (i = 0; i < sizeof test_cases/sizeof test_cases[0]; i++) {
			int bits = test_cases[i].bits;
			int min_k = test_cases[i].min_k;
			int max_k = test_cases[i].max_k;
			int k;

			if (algorithm == binary || algorithm == ecc_binary || algorithm == ecc_naf_binary || algorithm == fixed_base) {
				min_k = 1;
				max_k = 1;

				if((algorithm == ecc_binary || algorithm == ecc_naf_binary) && bits > 160){
					continue;
				}
			}

			for (k = min_k; k <= max_k; k++) {
				long count_S;
				long count_M;
				clock_t start_time, end_time;
				int j;

				switch (algorithm) {
				case binary:
					printf("Binary algorithm, %i bits\n", bits);
					break;
				case ecc_binary:
					printf("Double and Add algorithm, %i bits\n", bits);
					break;
				case ecc_naf_binary:
					printf("NAF-Double and Add algorithm, %i bits\n", bits);
					break;
				case k_ary:
					printf("k-ary algorithm, %i bits, k = %i\n", bits, k);
					break;
				case sliding_window:
					printf("Sliding window algorithm, %i bits, k = %i\n", bits, k);
					break;
                case fixed_base:
                    lut_size = get_fb_LUT_size(bits);
                    lut = allocate_fixed_base_LUT(lut_size);
                    precompute_fixed_base_LUT(lut, g, modulus, lut_size);
                    printf("Fixed base algorithm, %i bits\n", bits);
                    break;
                case improved_fixed_base:
                    lut_size = get_imp_fb_LUT_size(bits, k);
                    lut = allocate_fixed_base_LUT(lut_size);
                    precompute_improved_fixed_base_LUT(lut, g, modulus, lut_size, k);
                    printf("Improved fixed base algorithm, %i bits, k = %i\n", bits, k);
                    break;


                default:
                    break;
				}

				count_S = 0;
				count_M = 0;
				start_time = clock();

				for (j = 0; j < number_of_operations; j++) {
					r = get_random_exponent(e, bits);
					assert(r == 0);

					switch (algorithm) {
					case binary:
						r = exponentiate_binary(result, g, e, modulus, &count_S, &count_M);
						break;

					case k_ary:
						r = exponentiate_k_ary(result, g, e, modulus, k, &count_S, &count_M);
						break;

					case sliding_window:
						r = exponentiate_sliding_window(result, g, e, modulus, k, &count_S, &count_M);
						break;

                    case fixed_base:
                        r = exponentiate_fixed_based(result, e, modulus, lut, bits, &count_S, &count_M);
                        break;

                    case improved_fixed_base:
                        r = exponentiate_improved_fixed_based(result, e, modulus, lut, bits, k, &count_S, &count_M);
                        break;

					case ecc_binary:
						r = ecc_double_add(resultPoint_X, resultPoint_Y, a, b, p, q, basePoint_X, basePoint_Y, e, &count_S, &count_M);
						break;

					case ecc_naf_binary:
						r = ecc_naf_double_add(resultPoint_X, resultPoint_Y, a, b, p, q, basePoint_X, basePoint_Y, e, &count_S, &count_M);
						break;
                    default:
                        break;
					}


					if (r == 1) {
						printf("TO BE IMPLEMENTED\n\n");
						break;
					}

					assert(r == 0);

					/* We ignore the exponentiation result in "result" */
				}

				end_time = clock();


				if(algorithm == fixed_base || algorithm == improved_fixed_base) {
                    free_fixed_base_LUT(lut, lut_size);
				}

				if (r == 0) {
					if(algorithm == ecc_binary || algorithm == ecc_naf_binary){
						printf("Operations per point multiplication: %.1f D, %.1f A\n",
					       ((double) count_S)/number_of_operations,
					       ((double) count_M)/number_of_operations);
					printf("Time per point multiplication: %.0f microseconds\n\n", ((double) (end_time - start_time))/CLOCKS_PER_SEC*1000000/number_of_operations);
					}else{
						printf("Operations per exponentiation: %.1f S, %.1f M\n",
					       ((double) count_S)/number_of_operations,
					       ((double) count_M)/number_of_operations);
					printf("Time per exponentiation: %.0f microseconds\n\n", ((double) (end_time - start_time))/CLOCKS_PER_SEC*1000000/number_of_operations);
					}
				}
			}
		}
	}

	
	mpz_clear(modulus);
	mpz_clear(g);
	mpz_clear(e);
	mpz_clear(result);
	mpz_clears(a, b, p, q, basePoint_X, basePoint_Y, testFactor, test_resultPoint_X, test_resultPoint_Y, resultPoint_X, resultPoint_Y, NULL);
	return 0;
}

/* Performs an ecc point doubling on the elliptic curve defined by a, b, p. The input point is doubled and written into the result point.

	--> DO NOT TOUCH THIS METHOD! <--

 */
int ecc_op_double(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t inputX, mpz_t inputY)
{
	// init
	mpz_t s, t1, t2;
	mpz_inits(s, t1, t2, NULL);
	// calculate s by calculating nominator and denominator separately
	mpz_mul(t1, inputX, inputX);
	mpz_mul_ui(t1, t1, 3);
	mpz_add(t1, t1, a);

	mpz_mul_ui(t2, inputY, 2);

	mpz_invert(t2, t2, p);

	mpz_mul(s, t1, t2);
	mpz_mod(s, s, p);
	// calculate result point
	mpz_t x3, y3;
	mpz_inits(x3, y3, NULL);

	mpz_mul(x3, s, s);
	mpz_sub(x3, x3, inputX);
	mpz_sub(x3, x3, inputX);
	mpz_mod(x3, x3, p);

	mpz_sub(y3, inputX, x3);
	mpz_mul(y3, y3, s);
	mpz_sub(y3, y3, inputY);
	mpz_mod(y3, y3, p);
	// set the result
	mpz_set(resultX, x3);
	mpz_set(resultY, y3);
	// free used variables
	mpz_clears(s, t1, t2, NULL);
	mpz_clears(x3, y3, NULL);
	return 1;
}

/* Performs an ecc point addition on the elliptic curve defined by a, b, p. The two operands are added and the result is written into the result point.

	--> DO NOT TOUCH THIS METHOD! <--

 */
int ecc_op_add(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t operand1_X, mpz_t operand1_Y, mpz_t operand2_X, mpz_t operand2_Y)
{
	if (mpz_cmp(operand1_X, operand2_X) == 0 && mpz_cmp(operand1_Y, operand2_Y) == 0){
		printf("The two passed operands are identical. Please use the function ecc_op_double to perform the point doubling.\n");
		return 1;
	}
	//init
	mpz_t s, t1, t2;
	mpz_inits(s, t1, t2, NULL);
	// calculate s by calculating nominator and denominator separately
	mpz_sub(t1, operand2_Y, operand1_Y);
	mpz_sub(t2, operand2_X, operand1_X);

	mpz_invert(t2, t2, p);

	mpz_mul(s, t1, t2);
	mpz_mod(s, s, p);
	// calculate result point
	mpz_t x3, y3;
	mpz_inits(x3, y3, NULL);

	mpz_mul(x3, s, s);
	mpz_sub(x3, x3, operand1_X);
	mpz_sub(x3, x3, operand2_X);
	mpz_mod(x3, x3, p);

	mpz_sub(y3, operand1_X, x3);
	mpz_mul(y3, y3, s);
	mpz_sub(y3, y3, operand1_Y);
	mpz_mod(y3, y3, p);
	// set the result
	mpz_set(resultX, x3);
	mpz_set(resultY, y3);
	// free used variables
	mpz_clears(s, t1, t2, NULL);
	mpz_clears(x3, y3, NULL);
	return 1;
}

/* Generate a random positive integer up to e bits */
int get_random_exponent(mpz_t e, int bits)
{
	mpz_urandomb(e, randstate, bits);
	return 0;
}


/*
 * Perform the modular exponentiation
 *
 *    "result := g^e mod modulus",
 *
 * using the binary method; operation tally in *count_s and *count_M
 */

int exponentiate_binary(mpz_t result, mpz_t g, mpz_t e, mpz_t modulus, long *count_S, long *count_M)
{
	// A = g
	mpz_set(result, g);

	// get number of length in Binary representation
	unsigned number_of_bits_factor = mpz_sizeinbase(e, 2) - 1;

	// square on every digit
	for(int i = number_of_bits_factor - 1; i>=0; i--)
	{
		mpz_mul(result, result, result);
		mpz_mod(result, result, modulus);
		(*count_S)++;

		// Multiply on 1's
		if (mpz_tstbit(e, i) == 1)
		{
			mpz_mul(result, result, g);
			mpz_mod(result, result, modulus);
			(*count_M)++;
		}
	}
	return 0; 
}


/*
 * Perform the modular exponentiation
 *
 *    "result := g^e mod modulus",
 *
 * using the k-ary method parameterized by k;
 * operation tally in *count_s and *count_M
 */
int exponentiate_k_ary(mpz_t result, mpz_t g, mpz_t e, mpz_t modulus, int k, long *count_S, long *count_M)
{
	// Precomputation
	// Since there's no math libary in the compile options, there's no math library, making pow not usable and GMP annoying to use for allocations. So let's do this here instead...
	int lut_size = (1 << k);
	int tuple = 0;
	unsigned number_of_bits_factor = mpz_sizeinbase(e, 2) - 1;

	// create the LUT
	mpz_t *lut = malloc(sizeof(mpz_t) * (lut_size - 1));

	// set the first value in the LUT to 0, because we never multiply with 1 anyway. Just with g in the worst case.
	mpz_init(lut[0]);
	mpz_set(lut[0], g);

	for (int i = 1; i < (lut_size - 1); i++)
	{
		mpz_init(lut[i]);
		mpz_mul(lut[i], lut[i-1], g);
		mpz_mod(lut[i], lut[i], modulus);
		(*count_M)++;
	}

	// Computation

	// start with '1' as result so we have a neutral value for the first multiplication
	mpz_set_str(result, "1", 10);

	for (int i = number_of_bits_factor; i >= 0; i--)
	{
		// Just as Squary-And-Multiply, we multiply with each digit.
		mpz_mul(result, result, result);
        mpz_mod(result, result, modulus);
        (*count_S)++;

		// Collect tuples of k size. Use trick with pow(2) because dealing with tuples is gonna be hairy in C
		if (mpz_tstbit(e, i) == 1)
		{
			tuple += (1 << (i % k));
		}

		// If our tuple doesn't consist out of zeros (which would destroy our result) and we collected a k-tuple, multiply it.
		if (tuple > 0 && i % k == 0)
		{
			mpz_mul(result, result, lut[tuple - 1]);
			mpz_mod(result, result, modulus);
			(*count_M)++;

			// reset for the next tuple iterations
			tuple = 0;
		}
	}
	// Cleanup after we're done
	for (int i=0; i<(lut_size - 1); i++)
	{
		mpz_clear(lut[i]);
	}
	free(lut);
	return 0; 
}

/*
 * Perform the modular exponentiation
 *
 *    "result := g^e mod modulus",
 *
 * using the sliding window method parameterized by k;
 * operation tally in *count_s and *count_M
 */
int exponentiate_sliding_window(mpz_t result, mpz_t g, mpz_t e, mpz_t modulus, int k, long *count_S, long *count_M)
{
	int lut_size = (1 << (k-1));
	unsigned number_of_bits_factor = mpz_sizeinbase(e, 2) - 1;
	int tuple = 0;
	int window_length = 0;
	mpz_t *lut = malloc(sizeof(mpz_t) * (lut_size));
	mpz_t g2;
	 
	// Precomputation
	
	// Since this time the LUT is based on g^2, we calculate g2 beforehand case and can free it after generating the LUT.
	mpz_init(g2);
	mpz_mul(g2, g, g);
	mpz_mod(g2, g2, modulus);
	(*count_S)++;

	// First entry in the LUT is g. Same as the normal k-ary, we don't need 1, so LUT[0] is g instead.
	mpz_init(lut[0]);
	mpz_set(lut[0], g);
	
	// Generate rest of the LUT by multiplications with g^2
	for (int i = 1; i < lut_size; i++)
	{
		mpz_init(lut[i]);
		mpz_mul(lut[i], lut[i-1], g2);
		mpz_mod(lut[i], lut[i], modulus);
		(*count_M)++;
	} 

	// Sinde we only deal with odd values in the LOT, we can release g2 as it has served its purpose.
	mpz_clear(g2);

	// Computation
	// start with '1' as result so we have a neutral value for the first multiplication
	mpz_set_str(result, "1", 10);

	for (int i = number_of_bits_factor; i>=0;)
	{
		// gmp_printf("Bit %i = %Zd \n", i, result);
		// On 0's, just do simple squaring as in every other previous algorithm
		if (mpz_tstbit(e, i) == 0)
		{
			mpz_mul(result, result, result);
			mpz_mod(result, result, modulus);
			(*count_S)++;

			// manually decrement since we have to decrement on another way if we're dealing with the windows
			i--;
		}

		// If we have a 1...
		else
		{
			// Tuple contains the tuple combined as a number
			tuple = 1;
			// Now that we have a *sliding* window, we need to calculate how large a window is each time, as it could be smaller than k.
			window_length = 0;
			for (int j = 1; j < k; j++)
			{
				if (mpz_tstbit(e, i - j) == 1)
				{
                  	// Same trick as k-ary: Treat the tuples with their respective power so we get an integer equivilant of the (max.) k bits in binary representation.
					// Add 1 to fix the offset from the binary -> int conversion.
					// And for some reason, *= doesn't work here (why?), so using the long variation...
					tuple = tuple * (1 << (j-window_length)) + 1;
					// Adjust the window length to the actual amount of values we have in our 'sliding' window. Cannot be greater than k. 
					window_length = j;
				}
			}

			// Do as many squares as required for our window
			for (int j = 0; j <= window_length; j++)
			{
				mpz_mul(result, result, result);
				mpz_mod(result, result, modulus);
				(*count_S)++;
			}

			// Now multiply with the corresponding entry from the LUT, and we should be done!
			// Division by 2 to convert the int tuple to the LUT index.
			tuple /= 2;
			mpz_mul(result, result, lut[tuple]);
			mpz_mod(result, result, modulus);
			(*count_M)++;

			// After dealing with our sliding window, we can skip ahead so we aren't processing certain bits twice.
			i -= window_length + 1;
		}
	}

	// Cleanup after we're done
	for (int i=0; i < lut_size; i++)
	{
		mpz_clear(lut[i]);
	}
	free(lut);
	return 0; 
}

/*
 * Determine the size of the LUT for the regular fixed based exponentiation algorithm.
 */
size_t get_fb_LUT_size(size_t maximal_exponent_length) {
	
    return maximal_exponent_length;
}
/*
 * Determine the size of the LUT for the improved fixed based exponentiation algorithm.
 * Hint: The given exponent length is not neccessarily divisible by window_size. Suppose maximal_exponent_length is 4
 * and window_size is 3, then the required LUT size is 2.
 */
size_t get_imp_fb_LUT_size(size_t maximal_exponent_length, unsigned window_size) {
	// Since the given exponent length is not *neccessarily divisible*, we round the number up to next full integer.
	// Would've used ceil() here, but since math.h isn't allowed, we're using this fancy trick which basically does the same as ceil()
    return (maximal_exponent_length / window_size) + ((maximal_exponent_length % window_size) != 0);
}
/*
 * Allocate (and initialize!) the LUT for fixed based exponentiation. The size of the LUT is passed as an argument,
 * therefore this function is used for both regular and improved fixed based exponentiation.
 */
mpz_t *allocate_fixed_base_LUT(size_t lut_size) {
    // Create an array for the LUT. Reserve the memory...
	mpz_t *lut = malloc(sizeof(mpz_t) * lut_size);

	//... and initialize the array. 
	for (int i = 0; i < lut_size; i++)
	{
		mpz_init(lut[i]);
	}

	return lut;
}
/*
 * Free the LUT for fixed based exponentiation. The size of the LUT is passed as an argument,
 * therefore this function is used for both regular and improved fixed based exponentiation.
 */
void free_fixed_base_LUT(mpz_t *lut, size_t lut_size) {
	// Clear out the array, removing potential additional memory allocations done by GMP
    for (int i = 0; i < lut_size; i++)
	{
		mpz_clear(lut[i]);
	}
	// Free the LUT, releasing memory.
	free(lut);
}
/*
 * Precompute the LUT for regular fixed based exponentiation for base g and modulus n. Base g is not
 * passed as an argument to the actual exponentation.
 */
void precompute_fixed_base_LUT(mpz_t *lut, mpz_t g, mpz_t n, size_t lut_size) {
     // First entry in the LUT is g
	 mpz_set(lut[0], g);

	 // Calculate rest of the LUT by squaring the previous entry
	 for (int i = 1; i < lut_size; i++)
	 {
		 mpz_mul(lut[i], lut[i - 1], lut[i - 1]);
		 mpz_mod(lut[i], lut[i], n);
	 }
}
/*
 * Precompute the LUT for improved fixed based exponentiation for base g and modulus n. Base g is not
 * passed as an argument to the actual exponentation.
 */
void precompute_improved_fixed_base_LUT(mpz_t *lut, mpz_t g, mpz_t modulus, size_t lut_size, unsigned window_size) {
     // Initilize the base by squaring it with the window_size as often as needed
	 int base = (1 << window_size);

	 // First entry in the LUT is g
	 mpz_set(lut[0], g);

	 for (int i = 1; i < lut_size; i++)
	 {
		 // Init entry with the previous value
		 mpz_set(lut[i], lut[i - 1]);
		 for (int j = 1; j < base; j++)
		 {
			// Square the previous entry as often as required for correct base conversion
			mpz_mul(lut[i], lut[i], lut[i - 1]);
			mpz_mod(lut[i], lut[i], modulus);
		 }
	 }

}
/*
 * Perform the modular exponentiation
 *
 *    "result := g^e mod modulus",
 *
 * using the regular fixed base method using the look-up table lut;
 * operation tally in *count_s and *count_M
 */
int exponentiate_fixed_based(mpz_t result, mpz_t e, mpz_t modulus, mpz_t *lut, size_t maximal_exponent_length, long *count_S, long *count_M) {

    // Algorithm 3.8
	// Step 1
	// Set the starting result to the last entry of the LUT. -1 because the array index start at 0.
	mpz_set(result, lut[maximal_exponent_length - 1]);

	// Step 2
	// -2, because the algorithm requires l-1 and we need to substract one time more for the array indexes
	for (int i = maximal_exponent_length - 2; i >= 0; i--)
	{
		if(mpz_tstbit(e,i) == 1)
		{
			mpz_mul(result, result, lut[i]);
			mpz_mod(result, result, modulus);
			(*count_M)++;
		}
	}

	return 0; 
}
/*
 * Perform the modular exponentiation
 *
 *    "result := g^e mod modulus",
 *
 * using the improved fixed base method parameterized by window_size using the look-up table lut;
 * operation tally in *count_s and *count_M
 */
int exponentiate_improved_fixed_based(mpz_t result, mpz_t e, mpz_t modulus, mpz_t *lut, size_t maximal_exponent_length, unsigned window_size, long *count_S, long *count_M) {

    // Algorithm 3.9

	// Initilize the base by squaring it with the window_size as often as needed
	int base = 1 << window_size;
	int tuple = 0;
	
	// A = result and B = B
	mpz_t B;
	mpz_init(B);

	// Step 1
	// Initialize A and B with 1
	mpz_set_ui(result, 1);
	mpz_set_ui(B, 1);

	// Step 2
	for (int j = (base - 1); j > 0; j--)
	{
		// Use same trick as in sliding-window k-ary: work with tuples by squaring a single integer as often as needed
		tuple = 0;

		for (int i = (maximal_exponent_length - 1); i >= 0; i--)
		{
			// For every digit, left shift for correct base representation
			tuple = tuple << 1;
			// If we have a one, add it to the tuple. This is likely going to get shifted to the correct base in the next iteration.
			if(mpz_tstbit(e, i) == 1)
			{
				tuple++;
			}

			// Step 2.1
			if (i % window_size == 0)
			{
				// For every window, we check if the window matches with j. If so, we calculate (B * g^(b^l) mod n).
				if (tuple == j)
				{
					mpz_mul(B, B, lut[i / window_size]);
					mpz_mod(B, B, modulus);
					(*count_M)++;
				}
				tuple = 0;
			}
		}
		// Step 2.2
		mpz_mul(result, result, B);
		mpz_mod(result, result, modulus);
		(*count_M)++;
	}
	mpz_clear(B);
	return 0; 
}

/*
 * Perform the elliptic curve multiplication
 *
 *    "result := factor * input mod p",
 *
 * using the double and add algorithm.
 * operation tally in *count_D and *count_A
 *
 * Please reduce the factor with the prime group order q of the elliptic curve to avoid the point of infinity!
 */
int ecc_double_add(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t q, mpz_t inputX, mpz_t inputY, mpz_t factor, long *count_D, long *count_A)
{
	int number_of_bits_factor = mpz_sizeinbase(factor, 2) - 1;

	// Reduce factor with the prime group as required
	mpz_mod(factor, factor, q);

	// Implementing Double-and-Add as described in "Understanding Cryptography"

	// Init: result = input
	mpz_set(resultX, inputX);
	mpz_set(resultY, inputY);

	for (int i = (number_of_bits_factor - 1); i >= 0; i--)
	{
		// Double point for every digit in the factor
		ecc_op_double(resultX, resultY, a, b, p, resultX, resultY);
		(*count_D)++;

		// If we have a 1 in the factor, do an additional add
		if(mpz_tstbit(factor, i) == 1)
		{
			ecc_op_add(resultX, resultY, a, b, p, resultX, resultY, inputX, inputY);
			(*count_A)++;
		}
	}

	return 0;
}

/*
 * Perform the elliptic curve multiplication
 *
 *    "result := factor * input mod p",
 *
 * using the NAF double and add algorithm.
 * operation tally in *count_D and *count_A
 *
 * Please reduce the factor with the prime group order q of the elliptic curve to avoid the point of infinity!
 */
int ecc_naf_double_add(mpz_t resultX, mpz_t resultY, mpz_t a, mpz_t b, mpz_t p, mpz_t q, mpz_t inputX, mpz_t inputY, mpz_t factor, long *count_D, long *count_A)
{
	// This time we're getting the real length of the factor, - without -1 -, since we need to process the whole number without inits first.
	int number_of_bits_factor = mpz_sizeinbase(factor, 2) - 1;
	int number_of_bits_factor_full = mpz_sizeinbase(factor, 2);

	// Array with the NAF representation. + 1 because the NAF representation is usually one digit longer. 
	char naf_representation[number_of_bits_factor_full + 1];

	// Algorithm 3.5 - Computing the NAF of a positive integer
	mpz_t X;
	mpz_t inputY_inverse;
	// Step 1
	int i = 0;
	mpz_init(X);
	mpz_set(X, factor);

	// Step 2
	while (mpz_cmp_ui(X, 1) >= 0)
	{
		if (mpz_odd_p(X))
		{
			naf_representation[i] = (2 - mpz_fdiv_ui(X, 4));
			if (naf_representation[i] > 0)
			{
				mpz_sub_ui(X,X,1);
			}
			// - (-1) = + 1
			else if (naf_representation[i] < 0)
			{
				mpz_add_ui(X,X,1);
			}
		}
		// Step 2.2
		else
		{
			naf_representation[i] = 0;
		}
		// Step 2.3
		mpz_divexact_ui(X, X, 2);
		i++;
	} 
	// NAD Double and Add
	// Pretty much the same as above, just with calculating the inverse and adding the inverse on a -1

	// Reduce factor with the prime group as required
	mpz_mod(factor, factor, q);

	// Calculate inverse from inputY. Only Y required because the inverse is as followed: (x, y) -> (x, -y)
	mpz_init(inputY_inverse);
	mpz_sub(inputY_inverse, p, inputY);

	// Init: result = input
	mpz_set(resultX, inputX);
	mpz_set(resultY, inputY);

	for (int i = (number_of_bits_factor); i >= 0; i--)
	{
		// Double point for every digit in the factor
		ecc_op_double(resultX, resultY, a, b, p, resultX, resultY);
		(*count_D)++;

		// If we have a 1 in the factor, do an additional add
		if(naf_representation[i] == 1)
		{
			ecc_op_add(resultX, resultY, a, b, p, resultX, resultY, inputX, inputY);
			(*count_A)++;
		}
		// Else if we do have a -1, do an additional add with the inverse (= substract the point)
		else if (naf_representation[i] == -1)
		{
			ecc_op_add(resultX, resultY, a, b, p, resultX, resultY, inputX, inputY_inverse);
			(*count_A)++;
		}
	}
	mpz_clear(X);
	mpz_clear(inputY_inverse);
	return 0;
}
