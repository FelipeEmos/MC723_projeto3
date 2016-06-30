#ifndef __FPU_H__
#define __FPU_H__

// ---------------------------------------------------------------------------//
// Floating Point Unit

// ---------------------------------------------------------------------------//
// Real Data

typedef double Real;

static const Real r_zero      = 0.0;
static const Real r_one       = 1.0;
static const Real r_half      = 0.5;
static const Real r_overlog2  = 1.44269504088896;
static const Real r_over2log2 = 0.721347520444482;

// ---------------------------------------------------------------------------//
// Complex Data

typedef struct {
    Real r;
    Real i;
} Complex;

static const Complex c_zero   = {0.0, 0.0};
static const Complex c_one    = {1.0, 1.0};
static const Complex c_half   = {0.5, 0.5};

// ---------------------------------------------------------------------------//
// Complex Operations

Real c_mod(Complex z);

Complex c_add(Complex z1, Complex z2);

Complex c_sub(Complex z1, Complex z2);

Complex c_scalar(Complex z1, Complex z2);

Complex c_mult(Complex z1, Complex z2);

Complex c_uniform01();

// ---------------------------------------------------------------------------//
// Real Operations

Real r_add(Real d1, Real d2);

Real r_sub(Real d1, Real d2);

Real r_mult(Real d1, Real d2);

Real r_log(Real d);

Real r_frac(Real d);

int r_floor(Real d);

#endif
