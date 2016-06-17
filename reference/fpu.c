#include "fpu.h"

#ifndef HARD
#include <math.h>
#include <stdlib.h>
#endif

// ---------------------------------------------------------------------------//
// Floating Point Unit

// ---------------------------------------------------------------------------//
// Complex Operations

double c_mod(Complex z) {
#ifdef HARD
#else
  return (z.r*z.r + z.i*z.i);
#endif
}

Complex c_add(Complex z1, Complex z2) {
#ifdef HARD
#else
  Complex z;
  z.r = z1.r + z2.r;
  z.i = z1.i + z2.i;
  return z;
#endif
}

Complex c_sub(Complex z1, Complex z2) {
#ifdef HARD
#else
  Complex z;
  z.r = z1.r - z2.r;
  z.i = z1.i - z2.i;
  return z;
#endif
}

Complex c_scalar(Complex z1, Complex z2) {
#ifdef HARD
#else
  Complex z;
  z.r = z1.r * z2.r;
  z.i = z1.i * z2.i;
  return z;
#endif
}

Complex c_mult(Complex z1, Complex z2) {
#ifdef HARD
#else
  Complex z;
  z.r = (z1.r * z2.r) - (z1.i * z2.i);
  z.i = (z1.r * z2.i) + (z1.i * z2.r);
  return z;
#endif
}

Complex c_uniform01() {
#ifdef HARD
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
#else
  return d1 + d2;
#endif
}

double d_sub(double d1, double d2) {
#ifdef HARD
#else
  return d1 - d2;
#endif
}

double d_mult(double d1, double d2) {
#ifdef HARD
#else
  return d1 * d2;
#endif
}

double d_log(double d) {
#ifdef HARD
#else
  return log(d);
#endif
}

double d_frac(double d) {
#ifdef HARD
#else
  return fmod(d, 1.0);
#endif
}

int d_floor(double d) {
#ifdef HARD
#else
  return (int)floor(d);
#endif
}
