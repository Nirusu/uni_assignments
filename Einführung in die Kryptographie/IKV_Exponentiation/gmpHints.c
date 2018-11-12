#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

/*
    This file simply shows some basics of GMP.
    Also, do have a look at the official GMP documentation, it's really quite readable.
*/


void aFunction(mpz_t io_variable);


int main() {

    //Declare a multi-precision variable for an arbitrarily long integer.
    mpz_t aVariable;
    //You have to initialize the variable. This will allocate memory for storage. GMP will automatically allocate enough memory for you.
    //This is not C++, we don't have constructors or destructors. Clear any initialized variable!
    mpz_init(aVariable);

    //You can set your variable to actual numerical values.
    mpz_set_str(aVariable, "FF", 16);
    gmp_printf("aVariable before: 0x%Zx\n", aVariable);
    //You can simply pass variables to functions. GMP variables are passed by-reference and are not copied!
    //Changes to the passed variable will be seen outside the function.
    aFunction(aVariable);
    gmp_printf("aVariable after: 0x%Zx\n", aVariable);

    //You can simply determine the length of a variable in bits.
    unsigned number_of_bits = mpz_sizeinbase(aVariable, 2);
    gmp_printf("Number of bits in aVariable: %d\n", number_of_bits);

    //You can extract single bits from your variable. The least significant digit has the index 0.
    unsigned extracted_bit = mpz_tstbit(aVariable, 8);
    gmp_printf("The extracted bit is: %d\n", extracted_bit);


    //You can simply allocate a number of mpz_t variables (Hint: Look-up tables)
    mpz_t *dynamicVariable = malloc(sizeof(mpz_t) * 1);
    //You still have to initialize and clear them...
    mpz_init(*dynamicVariable);
    mpz_set_str(*dynamicVariable, "BEEF", 16);
    gmp_printf("dynamicVariable content: 0x%Zx\n", *dynamicVariable);
    mpz_clear(*dynamicVariable);
    //...before you free your allocated variable.
    free(dynamicVariable);



    //Clear your variables after you're done with them.
    mpz_clear(aVariable);
    return 0;
}


void aFunction(mpz_t io_variable) {
    mpz_t tmpVariable;

    mpz_init(tmpVariable);
    mpz_set_ui(tmpVariable, 1);
    //Arithmetic functions usually have three operands: (result, operand1, operand2)
    mpz_add(io_variable, io_variable, tmpVariable);
    //Skipping this clear would introduce a memory leak -> not good...
    mpz_clear(tmpVariable);
}
