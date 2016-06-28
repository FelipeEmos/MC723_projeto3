#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MIPS_TOOLCHAIN
#include "../my_peripheral.h"
#include <math.h>

#include <iostream>
using namespace std;

typedef struct {
	double r, i;
} Complex;

Complex getSoma(Complex z1, Complex z2);
Complex getSub(Complex z1, Complex z2);
double getMod(Complex z1);
Complex getScalar(Complex z1, Complex z2);
double getLog(double d);
double getFrac(double d);
int getFloor(double d);
Complex getRandom();
Complex getMult(Complex z1, Complex z2);

void teste();
//char const char *byte_to_binary(int x);

// thread id
const uint32_t tid = 0;

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

#define PERIPH_ON

int main(){
	Complex z1, z2, soma, sub, z3,scalar, random, mult;
	double mod,log2,frac;
	int floor;

	z1.r = z1.i = 1.00000000000000000000000;
	z2.r = z2.i = 2.00000000000000000000000;

	z3.r = 2.90000000000000000000000;
	z3.i = -5.30000000000000000000000;

	double d = 10.28177711;

	soma = getSoma(z1, z2);
	sub = getSub(z1, z2);
	mod = getMod(z3);
	scalar = getScalar(z2,z3);
	log2 = getLog(d);
	frac = getFrac(d);
	floor = getFloor(d);
	random = getRandom();
	mult = getMult(z2,z3);

	printf("Z1:  %.10lf+j*%.10lf\n",z1.r,z1.i);
	printf("Z2:  %.10lf+j*%.10lf\n",z2.r,z2.i);
	printf("Z3:  %.10lf+j*%.10lf\n",z3.r,z3.i);
	printf("d:  %.10lf\n",d);
	printf("\n");
	printf("SUM: %.10lf+j*%.10lf\n",soma.r,soma.i);
	printf("SUB: %.10lf+j*%.10lf\n",sub.r,sub.i);
	printf("MOD: %.10lf\n",mod);
	printf("SCALAR: %.10lf+j*%.10lf\n",scalar.r,scalar.i);
	printf("Log(%.10lf): %.10lf\n",d,log2);
	printf("Frac(%.10lf): %.10lf\n",d,frac);
	printf("Floor(%.10lf): %d\n",d,floor);
	printf("RANDOM:  %.10lf+j*%.10lf\n",random.r,random.i);
	printf("MULT:  %.10lf+j*%.10lf\n",mult.r,mult.i);

	return 0;
}

Complex getSoma(Complex z1, Complex z2){
#ifdef PERIPH_ON
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

Complex getSub(Complex z1, Complex z2){
#ifdef PERIPH_ON
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

double getMod(Complex z1){
#ifdef PERIPH_ON
	double z;

	LOAD_Z1(z1, tid);

	UNITE_DOUBLE(*mod_p1, *mod_p2, &(z));

	return z;
#else
	double z;
	z = (z1.r*z1.r + z1.i*z1.i);
	return z;
#endif
}

Complex getScalar(Complex z1, Complex z2){
#ifdef PERIPH_ON
	Complex z;

	LOAD_Z1(z1, tid);
	LOAD_Z2(z2, tid);

	UNITE_DOUBLE(*scalar_r_p1, *scalar_r_p2, &(z.r));
	UNITE_DOUBLE(*scalar_i_p1, *scalar_i_p2, &(z.i));

	return z;
#else
	Complex z;
	z.r = z1.r*z2.r;
	z.i = z1.i*z2.i;

	return z;
#endif
}

double getLog(double d){
#ifdef PERIPH_ON
	*z1_r_p1 = *DOUBLE_PART1(&d);
	*z1_r_p2 = *DOUBLE_PART2(&d);

	UNITE_DOUBLE(*log_p1, *log_p2, &(d));

	return d;
#else
	return log(d);
#endif
}

double getFrac(double d){
#ifdef PERIPH_ON
	*z1_r_p1 = *DOUBLE_PART1(&d);
	*z1_r_p2 = *DOUBLE_PART2(&d);

	UNITE_DOUBLE(*frac_p1, *frac_p2, &(d));

	return d;
#else
	return fmod(d, 1.0);
#endif
}

int getFloor(double d){
#ifdef PERIPH_ON
	*z1_r_p1 = *DOUBLE_PART1(&d);
	*z1_r_p2 = *DOUBLE_PART2(&d);

	UNITE_DOUBLE(*floor_p1, *floor_p2, &(d));

	return (int)d;
#else
	return (int)floor(d);
#endif
}

Complex getRandom(){
#ifdef PERIPH_ON
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

Complex getMult(Complex z1, Complex z2) {
#ifdef PERIPH_ON
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

void teste(){
	double d1, d2;
        uint32_t int1, int2;

	d1 = 4.0;

	int1 = *DOUBLE_PART1(&d1);
	int2 = *DOUBLE_PART2(&d1);

	UNITE_DOUBLE(int1, int2, &d2);

	printf("[%p]double1:%lf\n[%p]int1: %x\n[%p]int2: %x\n[-------]double2:%lf\n",
			&d1, d1, DOUBLE_PART1(&d1),int1, DOUBLE_PART2(&d1),int2,d2);
}
