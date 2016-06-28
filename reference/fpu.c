#include "fpu.h"

#ifndef HARD
#include <math.h>
#include <stdlib.h>
#endif

// ---------------------------------------------------------------------------//
// Floating Point Unit

#ifdef HARD
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "../mips-tlm/my_peripheral.h"

#define tid 0

volatile uint32_t *z1_r_p1 = (uint32_t*) (Z1_R_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z1_r_p2 = (uint32_t*) (Z1_R_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z1_i_p1 = (uint32_t*) (Z1_I_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z1_i_p2 = (uint32_t*) (Z1_I_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z2_r_p1 = (uint32_t*) (Z2_R_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z2_r_p2 = (uint32_t*) (Z2_R_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z2_i_p1 = (uint32_t*) (Z2_I_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *z2_i_p2 = (uint32_t*) (Z1_I_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *add_r_p1 = (uint32_t*) (ADD_R_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *add_r_p2 = (uint32_t*) (ADD_R_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *add_i_p1 = (uint32_t*) (ADD_I_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *add_i_p2 = (uint32_t*) (ADD_I_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *sub_r_p1 = (uint32_t*) (SUB_R_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *sub_r_p2 = (uint32_t*) (SUB_R_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *sub_i_p1 = (uint32_t*) (SUB_I_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *sub_i_p2 = (uint32_t*) (SUB_I_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *mod_p1 = (uint32_t*) (MOD_P1_ADDR + tid*LIMIT_ADDR); 
volatile uint32_t *mod_p2 = (uint32_t*) (MOD_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *scalar_r_p1 = (uint32_t*) (SCALAR_R_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *scalar_r_p2 = (uint32_t*) (SCALAR_R_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *scalar_i_p1 = (uint32_t*) (SCALAR_I_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *scalar_i_p2 = (uint32_t*) (SCALAR_I_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *log_p1 = (uint32_t*) (LOG_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *log_p2 = (uint32_t*) (LOG_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *frac_p1 = (uint32_t*) (FRAC_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *frac_p2 = (uint32_t*) (FRAC_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *floor_p1 = (uint32_t*) (FLOOR_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *floor_p2 = (uint32_t*) (FLOOR_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *random_p1 = (uint32_t*) (RANDOM_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *random_p2 = (uint32_t*) (RANDOM_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *mult_r_p1 = (uint32_t*) (MULT_R_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *mult_r_p2 = (uint32_t*) (MULT_R_P2_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *mult_i_p1 = (uint32_t*) (MULT_I_P1_ADDR + tid*LIMIT_ADDR);
volatile uint32_t *mult_i_p2 = (uint32_t*) (MULT_I_P2_ADDR + tid*LIMIT_ADDR);
#endif

// ---------------------------------------------------------------------------//
// Complex Operations

double c_mod(Complex z) {
#ifdef HARD
	double d;
	
	LOAD_Z1(z, tid);
	
	UNITE_DOUBLE(*mod_p1, *mod_p2, &(d));
	
	return d;  
#else
  return (z.r*z.r + z.i*z.i);
#endif
}

Complex c_add(Complex z1, Complex z2) {
#ifdef HARD
   Complex z;

	LOAD_Z1(z1, tid);
	LOAD_Z2(z2, tid);
	
	UNITE_DOUBLE(*add_r_p1, *add_r_p2, &(z.r));
	UNITE_DOUBLE(*add_i_p1, *add_i_p2, &(z.i));

	return z;
#else
  Complex z;
  z.r = z1.r + z2.r;
  z.i = z1.i + z2.i;
  return z;
#endif
}

Complex c_sub(Complex z1, Complex z2) {
#ifdef HARD
	Complex z;

	LOAD_Z1(z1, tid);
	LOAD_Z2(z2, tid);
	
	UNITE_DOUBLE(*sub_r_p1, *sub_r_p2, &(z.r));
	UNITE_DOUBLE(*sub_i_p1, *sub_i_p2, &(z.i));

	return z;  
#else
  Complex z;
  z.r = z1.r - z2.r;
  z.i = z1.i - z2.i;
  return z;
#endif
}

Complex c_scalar(Complex z1, Complex z2) {
#ifdef HARD
	Complex z;

	LOAD_Z1(z1, tid);
	LOAD_Z2(z2, tid);
	
	UNITE_DOUBLE(*scalar_r_p1, *scalar_r_p2, &(z.r));
	UNITE_DOUBLE(*scalar_i_p1, *scalar_i_p2, &(z.i));

	return z;
#else
  Complex z;
  z.r = z1.r * z2.r;
  z.i = z1.i * z2.i;
  return z;
#endif
}

Complex c_mult(Complex z1, Complex z2) {
#ifdef HARD
	Complex z;

	LOAD_Z1(z1, tid);
	LOAD_Z2(z2, tid);
	
	UNITE_DOUBLE(*mult_r_p1, *mult_r_p2, &(z.r));
	UNITE_DOUBLE(*mult_i_p1, *mult_i_p2, &(z.i));

	return z;
#else
  Complex z;
  z.r = (z1.r * z2.r) - (z1.i * z2.i);
  z.i = (z1.r * z2.i) + (z1.i * z2.r);
  return z;
#endif
}

Complex c_uniform01() {
#ifdef HARD
	Complex z;
	
	UNITE_DOUBLE(*random_p1, *random_p2, &(z.r));
	UNITE_DOUBLE(*random_p1, *random_p2, &(z.i));

	return z;
#else
  Complex z;
  z.r = ((double)rand()/(double)RAND_MAX);
  z.i = ((double)rand()/(double)RAND_MAX);
  return z;
#endif
}

// ---------------------------------------------------------------------------//
// Double Operations

double d_add(double d1, double d2) {
#ifdef HARD
    //return d1+d2;

    double d;
    *z1_r_p1 = *DOUBLE_PART1(&d1);
	*z1_r_p2 = *DOUBLE_PART2(&d1);
    *z2_r_p1 = *DOUBLE_PART1(&d2);
	*z2_r_p2 = *DOUBLE_PART2(&d2);
    
    UNITE_DOUBLE(*add_r_p1, *add_r_p2, &(d));
	
	return d;
    
#else
  return d1 + d2;
#endif
}

double d_sub(double d1, double d2) {
#ifdef HARD
    //return d1 - d2;

    double d;
    *z1_r_p1 = *DOUBLE_PART1(&d1);
	*z1_r_p2 = *DOUBLE_PART2(&d1);
    *z2_r_p1 = *DOUBLE_PART1(&d2);
	*z2_r_p2 = *DOUBLE_PART2(&d2);
    
    UNITE_DOUBLE(*sub_r_p1, *sub_r_p2, &(d));
	
	return d;
#else
  return d1 - d2;
#endif
}

double d_mult(double d1, double d2) {
#ifdef HARD
    double d;
    *z1_r_p1 = *DOUBLE_PART1(&d1);
	*z1_r_p2 = *DOUBLE_PART2(&d1);
    *z2_r_p1 = *DOUBLE_PART1(&d2);
	*z2_r_p2 = *DOUBLE_PART2(&d2);
    
    UNITE_DOUBLE(*scalar_r_p1, *scalar_r_p2, &(d));
	
	return d;
#else
  return d1 * d2;
#endif
}

double d_log(double d) {
#ifdef HARD
    //return log(d);

	*z1_r_p1 = *DOUBLE_PART1(&d);
	*z1_r_p2 = *DOUBLE_PART2(&d);
	
	UNITE_DOUBLE(*log_p1, *log_p2, &(d));
	
	return d;
#else
  return log(d);
#endif
}

double d_frac(double d) {
#ifdef HARD
    //return fmod(d,1.0);
    
	*z1_r_p1 = *DOUBLE_PART1(&d);
	*z1_r_p2 = *DOUBLE_PART2(&d);
	
	UNITE_DOUBLE(*frac_p1, *frac_p2, &(d));
	
	return d;
#else
  return fmod(d, 1.0);
#endif
}

int d_floor(double d) {
#ifdef HARD
    //return (int) floor(d);
    
	*z1_r_p1 = *DOUBLE_PART1(&d);
	*z1_r_p2 = *DOUBLE_PART2(&d);
	
	UNITE_DOUBLE(*floor_p1, *floor_p2, &(d));
	
	return (int)d;
#else
  return (int)floor(d);
#endif
}
