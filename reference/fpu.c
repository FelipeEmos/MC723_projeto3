#include "fpu.h"

#ifndef HARD
#include <math.h>
#include <stdlib.h>
#endif

// ---------------------------------------------------------------------------//
// Floating Point Unit

// ---------------------------------------------------------------------------//
// Complex Operations

Real c_mod(Complex z) {
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
  z.r = ((Real)rand()/(Real)RAND_MAX);
  z.i = ((Real)rand()/(Real)RAND_MAX);
  return z;
#endif
}

// ---------------------------------------------------------------------------//
// Real Operations

Real r_add(Real d1, Real d2) {
#ifdef HARD
#else
  return d1 + d2;
#endif
}

Real r_sub(Real d1, Real d2) {
#ifdef HARD
#else
  return d1 - d2;
#endif
}

Real r_mult(Real d1, Real d2) {
#ifdef HARD
#else
  return d1 * d2;
#endif
}

Real r_log(Real d) {
#ifdef HARD
#else
  return log(d);
#endif
}

Real r_frac(Real d) {
#ifdef HARD
#else
  return fmod(d, r_one);
#endif
}

int r_floor(Real d) {
#ifdef HARD
#else
  return (int)floor(d);
#endif
}
