//#define DEBUG

// TODO VER TAMANHO E DAR OS ENDERECOS

#define STARTING_SEED 0

// Variables addresses
#define Z1_R_ADDR 0x6400001    // complex 1
#define Z1_I_ADDR 0x6400002    // complex 2
#define Z2_R_ADDR 0x6400003    // double 1
#define Z2_I_ADDR 0x6400004    // double 2
/// Result addresses
#define ADD_R_ADDR 0x6400005 // Re(z1+z2)
#define ADD_I_ADDR 0x6400015 // Im(z1+z2)
#define SUB_R_ADDR 0x6400006 // z1-z2
#define SUB_I_ADDR 0x6400016 // z1-z2
#define MULT_R_ADDR 0x6400007    //z1*z2
#define MULT_I_ADDR 0x6400017    //z1*z2
#define MOD_ADDR 0x6400008 // |z1|
#define SCALAR_R_ADDR 0x6400009 // z.r *= d1; + z.i *= d2;
#define SCALAR_I_ADDR 0x6400019 // z.r *= d1; + z.i *= d2;
#define LOG_ADDR 0x640000A //log d1
#define FRAC_ADDR 0x640000B //d1%1.0
#define FLOOR_ADDR 0x640000C //floor(d1)
#define RANDOM_ADDR 0x640000D //random
//
