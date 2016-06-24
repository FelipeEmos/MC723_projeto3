//#define DEBUG

// TODO VER TAMANHO E DAR OS ENDERECOS

#define STARTING_SEED 0

// Endian inversion
// http://stackoverflow.com/questions/2182002/convert-big-endian-to-little-endian-in-c-without-using-provided-func
#define INVERT_ENDIAN(num) \
	(((num>>24)&0xff) \
	|((num<<8)&0xff0000) \
	|((num>>8)&0xff00) \
	|((num<<24)&0xff000000))

// 64bit breaking into 32bit
// x -> double value to be broken
#define DOUBLE_PART1(addr_double) \
	((uint32_t*)(addr_double))

// x -> double value to be broken
#define DOUBLE_PART2(addr_double) \
	((uint32_t*)(addr_double)+1)

// int1 -> uint32_t value, part1 of double
// int2 -> uint32_t value, part2 of double
// addr_double -> address to be written in the double
// DO NOT use the same variable in addr_double and int1, int2
#define UNITE_DOUBLE(int1, int2, addr_double) \
	*((uint32_t*)(addr_double)) = int1; \
	*((uint32_t*)(addr_double) + 1) = int2
	

// -- Peripheral addresses --
// Writing addrs
#define Z1_R_P1_ADDR 0x6400004 // complex 1 real part 1
#define Z1_R_P2_ADDR 0x6400008 // complex 1 real part 2
#define Z1_I_P1_ADDR 0x640000C // complex 1 imag part 1
#define Z1_I_P2_ADDR 0x6400010 // compelx 1 imag part 2
#define Z2_R_P1_ADDR 0x6400014 // complex 2 real part 1 
#define Z2_R_P2_ADDR 0x6400018 // complex 2 real part 2
#define Z2_I_P1_ADDR 0x640001C // complex 2 imag part 1
#define Z2_I_P2_ADDR 0x6400020 // complex 2 imag part 2
// Reading addrs
#define ADD_R_P1_ADDR 0x6400024
#define ADD_R_P2_ADDR 0x6400028
#define ADD_I_P1_ADDR 0x640002C
#define ADD_I_P2_ADDR 0x6400030
#define SUB_R_P1_ADDR 0x6400034
#define SUB_R_P2_ADDR 0x6400038
#define SUB_I_P1_ADDR 0x6400040
#define SUB_I_P2_ADDR 0x6400044
#define MOD_P1_ADDR 0x6400048
#define MOD_P2_ADDR 0x640004C
#define SCALAR_R_P1_ADDR 0x6400050 // z.r *= d1; + z.i *= d2;
#define SCALAR_R_P2_ADDR 0x6400054
#define SCALAR_I_P1_ADDR 0x6400058 // z.r *= d1; + z.i *= d2;
#define SCALAR_I_P2_ADDR 0x640005C
#define LOG_P1_ADDR 0x6400060 //log d1
#define LOG_P2_ADDR 0x6400064
#define FRAC_P1_ADDR 0x6400068 //d1%1.0
#define FRAC_P2_ADDR 0x640006C
#define FLOOR_P1_ADDR 0x6400070 //floor(d1)
#define FLOOR_P2_ADDR 0x6400074
#define RANDOM_P1_ADDR 0x6400078 //random
#define RANDOM_P2_ADDR 0x640007C
//
