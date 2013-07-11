/*determine the position of the least significant one bit in an int64_t (signed)*/
int least_sig_one_signed(int64_t input);

/*determine the position of the least significant one bit in a uint64_t (unsigned)*/
int least_sig_one_unsigned(uint64_t input);

/*calculate 2**exponent (really really fast with bit shifting)*/
inline uint64_t pow2(unsigned exponent);
