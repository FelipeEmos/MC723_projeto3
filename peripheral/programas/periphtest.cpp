#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MIPS_TOOLCHAIN
#include "../my_peripheral.h"

#include <iostream>
using namespace std;

typedef struct {
	double r, i;
} Complex;

Complex getSoma(Complex z1, Complex z2);
Complex getSub(Complex z1, Complex z2);
void teste();
//char const char *byte_to_binary(int x);

volatile uint32_t *z1_r_p1 = (uint32_t*) Z1_R_P1_ADDR;
volatile uint32_t *z1_r_p2 = (uint32_t*) Z1_R_P2_ADDR;
volatile uint32_t *z1_i_p1 = (uint32_t*) Z1_I_P1_ADDR;
volatile uint32_t *z1_i_p2 = (uint32_t*) Z1_I_P2_ADDR;
volatile uint32_t *z2_r_p1 = (uint32_t*) Z2_R_P1_ADDR;
volatile uint32_t *z2_r_p2 = (uint32_t*) Z2_R_P2_ADDR;
volatile uint32_t *z2_i_p1 = (uint32_t*) Z2_I_P1_ADDR;
volatile uint32_t *z2_i_p2 = (uint32_t*) Z1_I_P2_ADDR;
volatile uint32_t *add_r_p1 = (uint32_t*) ADD_R_P1_ADDR;
volatile uint32_t *add_r_p2 = (uint32_t*) ADD_R_P2_ADDR;
volatile uint32_t *add_i_p1 = (uint32_t*) ADD_I_P1_ADDR;
volatile uint32_t *add_i_p2 = (uint32_t*) ADD_I_P2_ADDR;
volatile uint32_t *sub_r_p1 = (uint32_t*) SUB_R_P1_ADDR;
volatile uint32_t *sub_r_p2 = (uint32_t*) SUB_R_P2_ADDR;
volatile uint32_t *sub_i_p1 = (uint32_t*) SUB_I_P1_ADDR;
volatile uint32_t *sub_i_p2 = (uint32_t*) SUB_I_P2_ADDR;
volatile uint32_t *mod_p1 = (uint32_t*) MOD_P1_ADDR; 
volatile uint32_t *mod_p2 = (uint32_t*) MOD_P2_ADDR;


#define PERIPH_ON

int main(){
	Complex z1, z2, soma, sub;
	
	z1.r = z1.i = 1.00000000000000000000000;
	z2.r = z2.i = 2.00000000000000000000000;

	soma = getSoma(z1, z2);
	sub = getSub(z1, z2);

	printf("Z1:  %lf+j*%lf\n",z1.r,z1.i);
	printf("Z2:  %lf+j*%lf\n",z2.r,z2.i);
	printf("SUM: %lf+j*%lf\n",soma.r,soma.i);
	printf("SUB: %lf+j*%lf\n",sub.r,sub.i);

	return 0;
}


Complex getSoma(Complex z1, Complex z2){
#ifdef PERIPH_ON
	Complex resposta;

	*z1_r_p1 = *DOUBLE_PART1(&z1.r);
	*z1_r_p2 = *DOUBLE_PART2(&z1.r);
	*z1_i_p1 = *DOUBLE_PART1(&z1.i);
	*z1_i_p2 = *DOUBLE_PART2(&z1.i);

	*z2_r_p1 = *DOUBLE_PART1(&z2.r);
	*z2_r_p2 = *DOUBLE_PART2(&z2.r);
	*z2_i_p1 = *DOUBLE_PART1(&z2.i);
	*z2_i_p2 = *DOUBLE_PART2(&z2.i);
	
	UNITE_DOUBLE(*add_r_p1, *add_r_p2, &(resposta.r));
	UNITE_DOUBLE(*add_i_p1, *add_i_p2, &(resposta.i));

	return resposta;
#else
	Complex resposta;
	resposta.r = z1.r + z2.r;
	resposta.i = z1.i + z2.i;
	return resposta;
#endif
}
Complex getSub(Complex z1, Complex z2){
#ifdef PERIPH_ON
	Complex resposta;

	*z1_r_p1 = *DOUBLE_PART1(&z1.r);
	*z1_r_p2 = *DOUBLE_PART2(&z1.r);
	*z1_i_p1 = *DOUBLE_PART1(&z1.i);
	*z1_i_p2 = *DOUBLE_PART2(&z1.i);

	*z2_r_p1 = *DOUBLE_PART1(&z2.r);
	*z2_r_p2 = *DOUBLE_PART2(&z2.r);
	*z2_i_p1 = *DOUBLE_PART1(&z2.i);
	*z2_i_p2 = *DOUBLE_PART2(&z2.i);
	
	UNITE_DOUBLE(*sub_r_p1, *sub_r_p2, &(resposta.r));
	UNITE_DOUBLE(*sub_i_p1, *sub_i_p2, &(resposta.i));

	return resposta;
#else
	Complex resposta;
	resposta.r = z1.r - z2.r;
	resposta.i = z1.i - z2.i;
	return resposta;
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
