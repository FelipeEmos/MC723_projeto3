#include <stdio.h>
#include <stdlib.h>
#define MIPS_TOOLCHAIN
#include "../peripheral_addrs.h"

typedef struct {
	double r, i;
} Complex;

Complex getSoma(Complex z1, Complex z2);
Complex getSub(Complex z1, Complex z2);

volatile double *z1_r = (double*) Z1_R_ADDR;
volatile double *z1_i = (double*) Z1_I_ADDR;
volatile double *z2_r = (double*) Z2_R_ADDR;
volatile double *z2_i = (double*) Z2_I_ADDR;
volatile double *add_r = (double*) ADD_R_ADDR;
volatile double *add_i = (double*) ADD_I_ADDR;
volatile double *sub_r = (double*) SUB_R_ADDR;
volatile double *sub_i = (double*) SUB_I_ADDR;


int main(){
	
	Complex z1, z2;

	z1.i = z1.r = 1; // 1 + 1j
	z2.r = z2.i = 2; // 2 + 2j

	Complex soma = getSoma(z1, z2);
	//Complex sub = getSub(z1, z2);

	printf("Da certo plz, nunca te pedi nada: %lf + j*%lf\n", soma.r, soma.i);

	return 0;
}


Complex getSoma(Complex z1, Complex z2){
	Complex resposta;
	
	*z1_r = z1.r;
	*z1_i = z1.i;
	*z2_r = z2.r;
	*z2_i = z2.i;
	
	resposta.r = *add_r;
	resposta.i = *add_i;

	return resposta;
}
Complex getSub(Complex z1, Complex z2){
	Complex resposta;


	return resposta;
}

