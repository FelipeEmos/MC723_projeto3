#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MIPS_TOOLCHAIN
#include "../my_peripheral.h"

typedef struct {
	double r, i;
} Complex;

Complex getSoma(Complex z1, Complex z2);
Complex getSub(Complex z1, Complex z2);
void teste();

volatile double *z1_r_p1 = (double*) Z1_R_P1_ADDR;
volatile double *z1_r_p2 = (double*) Z1_R_P2_ADDR;
volatile double *z1_i_p1 = (double*) Z1_I_P1_ADDR;
volatile double *z1_i_p2 = (double*) Z1_I_P2_ADDR;
volatile double *z2_r_p1 = (double*) Z2_R_P1_ADDR;
volatile double *z2_r_p2 = (double*) Z2_R_P2_ADDR;
volatile double *z2_i_p1 = (double*) Z2_I_P1_ADDR;
volatile double *z2_i_p2 = (double*) Z1_I_P2_ADDR;
volatile double *add_r_p1 = (double*) ADD_R_P1_ADDR;
volatile double *add_r_p2 = (double*) ADD_R_P2_ADDR;
volatile double *add_i_p1 = (double*) ADD_I_P1_ADDR;
volatile double *add_i_p2 = (double*) ADD_I_P2_ADDR;
volatile double *sub_r_p1 = (double*) SUB_R_P1_ADDR;
volatile double *sub_r_p2 = (double*) SUB_R_P2_ADDR;
volatile double *sub_i_p1 = (double*) SUB_I_P1_ADDR;
volatile double *sub_i_p2 = (double*) SUB_I_P2_ADDR;
volatile double *mod_p1 = (double*) MOD_P1_ADDR; 
volatile double *mod_p2 = (double*) MOD_P2_ADDR;

#define PERIPH_ON

int main(){
	//teste();
	//return 0;
	Complex z1, z2, soma;
	
	z1.r = z1.i = 1.0;
	z2.r = z2.i = 2.0;
	printf("TESTE\n");

	soma = getSoma(z1,z2);
	printf("TESTE\n");

	printf("z1 = %lf+j%lf;\n",z1.r,z1.i);	
	printf("z2 = %lf+j%lf;\n",z2.r,z2.i);
	printf("TESTE\n");

	printf("Soma = %lf+j%lf;",soma.r,soma.i);
	printf("TESTE\n");
	
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
	
	UNITE_DOUBLE(*add_r_p1, *add_r_p2, &resposta.r);
	UNITE_DOUBLE(*add_i_p1, *add_i_p2, &resposta.i);

	return resposta;
#else
	Complex resposta;
	resposta.r = z1.r + z2.r;
	resposta.i = z1.i + z2.i;
	return resposta;
#endif
}
Complex getSub(Complex z1, Complex z2){
	Complex resposta;


	return resposta;
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
