#include "fpu.h"

#include <stdio.h>

#ifndef HARD
#include <math.h>
#include <stdlib.h>
#endif

#ifdef HARD
#include "../peripheral/fpuAddress.h"
#endif


// ---------------------------------------------------------------------------//
// Floating Point Unit

// ---------------------------------------------------------------------------//
// Peripheral Pointers

#ifdef HARD
static int tid;
typedef uint32_t* u32;
volatile u32 z1_r_p1[4]  ={(u32)(Z1_R_P1  ),(u32)(Z1_R_P1  +1*LIMIT),(u32)(Z1_R_P1  +2*LIMIT),(u32)(Z1_R_P1  +3*LIMIT)};
volatile u32 z1_r_p2[4]  ={(u32)(Z1_R_P2  ),(u32)(Z1_R_P2  +1*LIMIT),(u32)(Z1_R_P2  +2*LIMIT),(u32)(Z1_R_P2  +3*LIMIT)};
volatile u32 z1_i_p1[4]  ={(u32)(Z1_I_P1  ),(u32)(Z1_I_P1  +1*LIMIT),(u32)(Z1_I_P1  +2*LIMIT),(u32)(Z1_I_P1  +3*LIMIT)};
volatile u32 z1_i_p2[4]  ={(u32)(Z1_I_P2  ),(u32)(Z1_I_P2  +1*LIMIT),(u32)(Z1_I_P2  +2*LIMIT),(u32)(Z1_I_P2  +3*LIMIT)};
volatile u32 z2_r_p1[4]  ={(u32)(Z2_R_P1  ),(u32)(Z2_R_P1  +1*LIMIT),(u32)(Z2_R_P1  +2*LIMIT),(u32)(Z2_R_P1  +3*LIMIT)};
volatile u32 z2_r_p2[4]  ={(u32)(Z2_R_P2  ),(u32)(Z2_R_P2  +1*LIMIT),(u32)(Z2_R_P2  +2*LIMIT),(u32)(Z2_R_P2  +3*LIMIT)};
volatile u32 z2_i_p1[4]  ={(u32)(Z2_I_P1  ),(u32)(Z2_I_P1  +1*LIMIT),(u32)(Z2_I_P1  +2*LIMIT),(u32)(Z2_I_P1  +3*LIMIT)};
volatile u32 z2_i_p2[4]  ={(u32)(Z1_I_P2  ),(u32)(Z1_I_P2  +1*LIMIT),(u32)(Z1_I_P2  +2*LIMIT),(u32)(Z1_I_P2  +3*LIMIT)};
volatile u32 add_r_p1[4] ={(u32)(ADD_R_P1 ),(u32)(ADD_R_P1 +1*LIMIT),(u32)(ADD_R_P1 +2*LIMIT),(u32)(ADD_R_P1 +3*LIMIT)};
volatile u32 add_r_p2[4] ={(u32)(ADD_R_P2 ),(u32)(ADD_R_P2 +1*LIMIT),(u32)(ADD_R_P2 +2*LIMIT),(u32)(ADD_R_P2 +3*LIMIT)};
volatile u32 add_i_p1[4] ={(u32)(ADD_I_P1 ),(u32)(ADD_I_P1 +1*LIMIT),(u32)(ADD_I_P1 +2*LIMIT),(u32)(ADD_I_P1 +3*LIMIT)};
volatile u32 add_i_p2[4] ={(u32)(ADD_I_P2 ),(u32)(ADD_I_P2 +1*LIMIT),(u32)(ADD_I_P2 +2*LIMIT),(u32)(ADD_I_P2 +3*LIMIT)};
volatile u32 sub_r_p1[4] ={(u32)(SUB_R_P1 ),(u32)(SUB_R_P1 +1*LIMIT),(u32)(SUB_R_P1 +2*LIMIT),(u32)(SUB_R_P1 +3*LIMIT)};
volatile u32 sub_r_p2[4] ={(u32)(SUB_R_P2 ),(u32)(SUB_R_P2 +1*LIMIT),(u32)(SUB_R_P2 +2*LIMIT),(u32)(SUB_R_P2 +3*LIMIT)};
volatile u32 sub_i_p1[4] ={(u32)(SUB_I_P1 ),(u32)(SUB_I_P1 +1*LIMIT),(u32)(SUB_I_P1 +2*LIMIT),(u32)(SUB_I_P1 +3*LIMIT)};
volatile u32 sub_i_p2[4] ={(u32)(SUB_I_P2 ),(u32)(SUB_I_P2 +1*LIMIT),(u32)(SUB_I_P2 +2*LIMIT),(u32)(SUB_I_P2 +3*LIMIT)};
volatile u32 mod_p1[4]   ={(u32)(MOD_P1   ),(u32)(MOD_P1   +1*LIMIT),(u32)(MOD_P1   +2*LIMIT),(u32)(MOD_P1   +3*LIMIT)};
volatile u32 mod_p2[4]   ={(u32)(MOD_P2   ),(u32)(MOD_P2   +1*LIMIT),(u32)(MOD_P2   +2*LIMIT),(u32)(MOD_P2   +3*LIMIT)};
volatile u32 scal_r_p1[4]={(u32)(SCAL_R_P1),(u32)(SCAL_R_P1+1*LIMIT),(u32)(SCAL_R_P1+2*LIMIT),(u32)(SCAL_R_P1+3*LIMIT)};
volatile u32 scal_r_p2[4]={(u32)(SCAL_R_P2),(u32)(SCAL_R_P2+1*LIMIT),(u32)(SCAL_R_P2+2*LIMIT),(u32)(SCAL_R_P2+3*LIMIT)};
volatile u32 scal_i_p1[4]={(u32)(SCAL_I_P1),(u32)(SCAL_I_P1+1*LIMIT),(u32)(SCAL_I_P1+2*LIMIT),(u32)(SCAL_I_P1+3*LIMIT)};
volatile u32 scal_i_p2[4]={(u32)(SCAL_I_P2),(u32)(SCAL_I_P2+1*LIMIT),(u32)(SCAL_I_P2+2*LIMIT),(u32)(SCAL_I_P2+3*LIMIT)};
volatile u32 log_p1[4]   ={(u32)(LOG_P1   ),(u32)(LOG_P1   +1*LIMIT),(u32)(LOG_P1   +2*LIMIT),(u32)(LOG_P1   +3*LIMIT)};
volatile u32 log_p2[4]   ={(u32)(LOG_P2   ),(u32)(LOG_P2   +1*LIMIT),(u32)(LOG_P2   +2*LIMIT),(u32)(LOG_P2   +3*LIMIT)};
volatile u32 frac_p1[4]  ={(u32)(FRAC_P1  ),(u32)(FRAC_P1  +1*LIMIT),(u32)(FRAC_P1  +2*LIMIT),(u32)(FRAC_P1  +3*LIMIT)};
volatile u32 frac_p2[4]  ={(u32)(FRAC_P2  ),(u32)(FRAC_P2  +1*LIMIT),(u32)(FRAC_P2  +2*LIMIT),(u32)(FRAC_P2  +3*LIMIT)};
volatile u32 floor_p1[4] ={(u32)(FLOOR_P1 ),(u32)(FLOOR_P1 +1*LIMIT),(u32)(FLOOR_P1 +2*LIMIT),(u32)(FLOOR_P1 +3*LIMIT)};
volatile u32 floor_p2[4] ={(u32)(FLOOR_P2 ),(u32)(FLOOR_P2 +1*LIMIT),(u32)(FLOOR_P2 +2*LIMIT),(u32)(FLOOR_P2 +3*LIMIT)};
volatile u32 random_p1[4]={(u32)(RANDOM_P1),(u32)(RANDOM_P1+1*LIMIT),(u32)(RANDOM_P1+2*LIMIT),(u32)(RANDOM_P1+3*LIMIT)};
volatile u32 random_p2[4]={(u32)(RANDOM_P2),(u32)(RANDOM_P2+1*LIMIT),(u32)(RANDOM_P2+2*LIMIT),(u32)(RANDOM_P2+3*LIMIT)};
volatile u32 mult_r_p1[4]={(u32)(MULT_R_P1),(u32)(MULT_R_P1+1*LIMIT),(u32)(MULT_R_P1+2*LIMIT),(u32)(MULT_R_P1+3*LIMIT)};
volatile u32 mult_r_p2[4]={(u32)(MULT_R_P2),(u32)(MULT_R_P2+1*LIMIT),(u32)(MULT_R_P2+2*LIMIT),(u32)(MULT_R_P2+3*LIMIT)};
volatile u32 mult_i_p1[4]={(u32)(MULT_I_P1),(u32)(MULT_I_P1+1*LIMIT),(u32)(MULT_I_P1+2*LIMIT),(u32)(MULT_I_P1+3*LIMIT)};
volatile u32 mult_i_p2[4]={(u32)(MULT_I_P2),(u32)(MULT_I_P2+1*LIMIT),(u32)(MULT_I_P2+2*LIMIT),(u32)(MULT_I_P2+3*LIMIT)};
#endif

// ---------------------------------------------------------------------------//
// Setup FPU Address Ranges

void setupFPU(int proc_num) {
#ifdef HARD
  tid = proc_num;
#endif
}

// ---------------------------------------------------------------------------//
// Complex Operations

Real c_mod(Complex z) {
#ifdef HARD
	Real d;
	LOAD_Z1(z, tid);
	UNITE_DOUBLE(*mod_p1[tid], *mod_p2[tid], &(d));
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
	UNITE_DOUBLE(*add_r_p1[tid], *add_r_p2[tid], &(z.r));
	UNITE_DOUBLE(*add_i_p1[tid], *add_i_p2[tid], &(z.i));
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
	UNITE_DOUBLE(*sub_r_p1[tid], *sub_r_p2[tid], &(z.r));
	UNITE_DOUBLE(*sub_i_p1[tid], *sub_i_p2[tid], &(z.i));
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
	UNITE_DOUBLE(*scal_r_p1[tid], *scal_r_p2[tid], &(z.r));
	UNITE_DOUBLE(*scal_i_p1[tid], *scal_i_p2[tid], &(z.i));
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
	UNITE_DOUBLE(*mult_r_p1[tid], *mult_r_p2[tid], &(z.r));
	UNITE_DOUBLE(*mult_i_p1[tid], *mult_i_p2[tid], &(z.i));
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
	UNITE_DOUBLE(*random_p1[tid], *random_p2[tid], &(z.r));
	UNITE_DOUBLE(*random_p1[tid], *random_p2[tid], &(z.i));
	return z;
#else
  Complex z;
  z.r = ((Real)rand()/(Real)RAND_MAX);
  z.i = ((Real)rand()/(Real)RAND_MAX);
  return z;
#endif
}

// ---------------------------------------------------------------------------//
// Real Operations

Real r_add(Real d1, Real d2) {
#ifdef HARD
  Real d;
  *z1_r_p1[tid] = *DOUBLE_PART1(&d1);
	*z1_r_p2[tid] = *DOUBLE_PART2(&d1);
  *z2_r_p1[tid] = *DOUBLE_PART1(&d2);
	*z2_r_p2[tid] = *DOUBLE_PART2(&d2);
  UNITE_DOUBLE(*add_r_p1[tid], *add_r_p2[tid], &(d));
	return d;
#else
  return d1 + d2;
#endif
}

Real r_sub(Real d1, Real d2) {
#ifdef HARD
  Real d;
  *z1_r_p1[tid] = *DOUBLE_PART1(&d1);
	*z1_r_p2[tid] = *DOUBLE_PART2(&d1);
  *z2_r_p1[tid] = *DOUBLE_PART1(&d2);
	*z2_r_p2[tid] = *DOUBLE_PART2(&d2);
  UNITE_DOUBLE(*sub_r_p1[tid], *sub_r_p2[tid], &(d));
	return d;
#else
  return d1 - d2;
#endif
}

Real r_mult(Real d1, Real d2) {
#ifdef HARD
  Real d;
  *z1_r_p1[tid] = *DOUBLE_PART1(&d1);
	*z1_r_p2[tid] = *DOUBLE_PART2(&d1);
  *z2_r_p1[tid] = *DOUBLE_PART1(&d2);
	*z2_r_p2[tid] = *DOUBLE_PART2(&d2);
  UNITE_DOUBLE(*scal_r_p1[tid], *scal_r_p2[tid], &(d));
	return d;
#else
  return d1 * d2;
#endif
}

Real r_log(Real d) {
#ifdef HARD
	if (tid == 0) printf("JUE\n");
	*z1_r_p1[tid] = *DOUBLE_PART1(&d);
	*z1_r_p2[tid] = *DOUBLE_PART2(&d);
	UNITE_DOUBLE(*log_p1[tid], *log_p2[tid], &(d));
	return d;
#else
  return log(d);
#endif
}

Real r_frac(Real d) {
#ifdef HARD
	*z1_r_p1[tid] = *DOUBLE_PART1(&d);
	*z1_r_p2[tid] = *DOUBLE_PART2(&d);
	UNITE_DOUBLE(*frac_p1[tid], *frac_p2[tid], &(d));
	return d;
#else
  return fmod(d, r_one);
#endif
}

int r_floor(Real d) {
#ifdef HARD
	*z1_r_p1[tid] = *DOUBLE_PART1(&d);
	*z1_r_p2[tid] = *DOUBLE_PART2(&d);
	UNITE_DOUBLE(*floor_p1[tid], *floor_p2[tid], &(d));
	return (int)d;
#else
  return (int)floor(d);
#endif
}
