#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

#include "bitstat.h"

/*constants (not sure if I need these)*/
const uint64_t MAX_UNSIGNED = 0xFFFFFFFFFFFFFFFF;
const int64_t MAX_SIGNED = 0x7FFFFFFFFFFFFFFF;
const int64_t MIN_SIGNED = 0x8000000000000000;

static void test();


/*determine the least significant one bit of an int64_t
return -1 if there are no one bits (i.e. input is zero)
calls least_sig_one_unsigned under the hood*/
int least_sig_one_signed(int64_t input){
	/*call the least_sig_one function after casting to uint64_t*/
	return least_sig_one_unsigned((uint64_t)input);
}

/*determine the least significant one bit of an uint64_t.
return -1 if there are no one bits
it would be stellar if this could be made non-iterative*/
int least_sig_one_unsigned(uint64_t input){
	uint64_t mask = 1;
	unsigned mask_bits_shifted = 0;

	while (mask_bits_shifted < 64){
		/*mask input with the mask*/
		uint64_t tester = 0;
		tester = mask & input;
		/*if the tester != 0, then a one has been found*/
		if (tester != 0)
			return mask_bits_shifted;
		mask  = mask << 1;
		mask_bits_shifted++;
	}
	
	/*if 64 bits have been shifted, return -1*/
	return -1;
}


/*return 2**exponent by shifting 1 over by exponent bits*/
inline uint64_t pow2(unsigned exponent){
	assert(exponent < 64);
	/*must cast 1 as a 64 bit value to allow return values > 2**32*/
	return (uint64_t)1 << exponent;
}

/******************************************************************************
															Testing functions: 
add tests to the test function and uncomment out main() to allow them to be run
******************************************************************************/

/*
int main(){
	test();
	return 0;
}*/
static void test(){
	/* 8 = 0000...0001000, should return 3*/
	printf("least_sig_one_unsigned(8) returns %u\n",
					least_sig_one_unsigned((uint64_t)8));
	assert(least_sig_one_unsigned((uint64_t)8) == 3);

		/* 9 = 0000...0001001, should return 0*/
	printf("least_sig_one_unsigned(9) returns %u\n",
					least_sig_one_unsigned((uint64_t)9));
	assert(least_sig_one_unsigned((uint64_t)9) == 0);

		/* 0xF0000000 should return 60*/
	/*1111 0000-00000000-00000000-00000000*/
	printf("least_sig_one_unsigned(0xF000000000000000) returns %u\n",
					least_sig_one_unsigned((uint64_t)0xF000000000000000));
	assert(least_sig_one_unsigned((uint64_t)0xF000000000000000) == 60);

	/*-1 unsigned is all one bits. it should return 0*/
	printf("least_sig_one_unsigned(-1) returns %u\n",
					least_sig_one_unsigned((uint64_t)-1));
	assert(least_sig_one_unsigned((uint64_t)-1) == 0);
	/*0 should return -1*/
	printf("least_sig_one_unsigned(0) returns %d\n",
					least_sig_one_unsigned((uint64_t)0));
	assert(least_sig_one_unsigned((uint64_t)0) == -1);

	printf("all tests passed!\n");
}