#ifndef __FPU_H__
#define __FPU_H__

// ---------------------------------------------------------------------------//
// Floating Point Unit

static const double overlog2 = 1.44269504088896;
static const double over2log2 = 0.721347520444482;

typedef struct {
    double r;
    double i;
} Complex;

double c_mod(Complex z);

Complex c_add(Complex z1, Complex z2);

Complex c_sub(Complex z1, Complex z2);

Complex c_scalar(Complex z1, Complex z2);

Complex c_mult(Complex z1, Complex z2);

Complex c_uniform01();

double d_add(double d1, double d2);

double d_sub(double d1, double d2);

double d_mult(double d1, double d2);

double d_log(double d);

double d_frac(double d);

int d_floor(double d);

#endif
