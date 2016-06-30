#include "fpu.h"
#include "lock.h"

#ifndef __mips__
#include <stdlib.h>
#endif

#include <stdio.h>

#define WIDTH   20
#define HEIGHT  20
#define BYTE    unsigned char


// ---------------------------------------------------------------------------//
// DEBUG PRINT

int Fail(const char format[], char arg[]) {
#ifndef __mips__
    fprintf(stderr, format, arg);
#endif
    return 1;
}

// ---------------------------------------------------------------------------//
// COLOR STRUCTURE

typedef struct {
  BYTE r;
  BYTE g;
  BYTE b;
} Color;

const Color Black = {0};
const Color White = {255, 255, 255};
const Color Red = {255, 0, 0};

Color interpolate_linear(Color *c1, Color *c2, Real alpha) {
  Color c;
  Real beta = r_sub(r_one,alpha);
  c.r = (BYTE)r_add(r_mult((Real)c1->r,beta), r_mult((Real)c2->r,alpha));
  c.g = (BYTE)r_add(r_mult((Real)c1->g,beta), r_mult((Real)c2->g,alpha));
  c.b = (BYTE)r_add(r_mult((Real)c1->b,beta), r_mult((Real)c2->b,alpha));
  return c;
}

typedef struct {
  unsigned int r;
  unsigned int g;
  unsigned int b;
} ColorAccumulator;

void accumulate(ColorAccumulator *acc, Color c) {
  acc->r += (int)c.r;
  acc->g += (int)c.g;
  acc->b += (int)c.b;
}

Color average(ColorAccumulator *acc, int n) {
  Color c;
  c.r = (BYTE)(acc->r/n);
  c.g = (BYTE)(acc->g/n);
  c.b = (BYTE)(acc->b/n);
  return c;
}

// ---------------------------------------------------------------------------//
// BUFFER

static Color _buffer[HEIGHT][WIDTH];

void setPixel(int x, int y, Color c) {
  _buffer[y][x] = c;
}

// ---------------------------------------------------------------------------//
// COLOR PALLETE

const int pal = 16;

Color _pallete[16] = {
  { 66,  30,  15}, //brown 3
  { 25,   7,  26}, //dark violett
  {  9,   1,  47}, //darkest blue
  {  4,   4,  73}, //blue 5
  {  0,   7, 100}, //blue 4
  { 12,  44, 138}, //blue 3
  { 24,  82, 177}, //blue 2
  { 57, 125, 209}, //blue 1
  {134, 181, 229}, //blue 0
  {211, 236, 248}, //lightest blue
  {241, 233, 191}, //lightest yellow
  {248, 201,  95}, //light yellow
  {255, 170,   0}, //dirty yellow
  {204, 128,   0}, //brown 0
  {153,  87,   0}, //brown 1
  {106,  52,   3}  //brown 2
};

// ---------------------------------------------------------------------------//
// MANDELBROT

int max_it;
Real scale;

Color mandelbrot(Complex c) {
  // -------------------------------------------------------------------------//
  // Iterate Mandelbrot Set
  Complex z = c_zero;
  int it = 0;
  while (c_mod(z) < (1 << 16) && it++ < max_it) {
    z = c_add(c_mult(z,z), c);
  }

  // -------------------------------------------------------------------------//
  // Determine the color for the point
  Color col = Black;
  int ind;
  if (it > 1 && it < max_it) {
    Real smooth_it = r_sub(r_add(it,1.0),r_mult(r_log(r_mult(r_log(c_mod(z)),r_over2log2)),r_overlog2));
    smooth_it = r_mult(smooth_it,scale);
    ind = r_floor(smooth_it);
    col = interpolate_linear(&_pallete[ind%pal], &_pallete[(ind+1)%pal], r_frac(smooth_it));
  }
  return col;
}

// ---------------------------------------------------------------------------//
// PRESETS

void loadpreset(Complex *center, Complex *window, int *samples, int preset) {
  switch (preset) {
    case 1:
      // Mandelbrot Center
      center->r =  0.0;
      center->i =  0.0;
      window->r =  4.2;
      window->i = -4.2;
      scale     =  1.0;
      max_it    =  2000;
      *samples  =  1;
      break;
    case 2:
      // Mandelbrot Feature 1
      center->r = -0.743643135;
      center->i =  0.131825963;
      window->r =  0.000014628;
      window->i = -0.000014628;
      scale     =  0.03;
      max_it    =  2000;
      *samples  =  1;
      break;
    case 3:
      // Mandelbrot Feature 2
      center->r = -0.743643887037151;
      center->i =  0.131825904205330;
      window->r =  0.000000000051299;
      window->i = -0.000000000051299;
      scale     =  0.02;
      max_it    =  8000;
      *samples  =  1;
      break;
  }
}

// ---------------------------------------------------------------------------//
// MAIN

int p_main(int argc, char *argv[]) {
  // -------------------------------------------------------------------------//
  // Reading Parameters
  if (argc != 3 || argc != 5)
    return Fail("Usage %s image_file preset [proc number_of_procs]\n", argv[0]);

  char filename[32];
  int preset = 1;
  int proc_num = 1;
  int proc_total = 1;

  sscanf(argv[1], "%s", filename);
  sscanf(argv[2], "%d", &preset);
  if (argc == 5) {
    sscanf(argv[3], "%d", &proc_num);
    sscanf(argv[4], "%d", &proc_total);
  }

  // -------------------------------------------------------------------------//
  // Mandelbrot Setup
  int samples;
  Complex center;
  Complex window;
  loadpreset(&center, &window, &samples, preset);
  Complex window_base = c_sub(center, c_scalar(window, c_half));
  Complex window_limit = c_add(center, c_scalar(window, c_half));
  Complex offset = {r_one/(Real)WIDTH, r_one/(Real)HEIGHT};
  Complex pointer = c_scalar(c_sub(window_limit, window_base), offset);

  int start_job = 0;
  int end_job = HEIGHT;
#ifdef __mips__
  //int proc_num = getProc();
  start_job = (proc_num*HEIGHT)/proc_total;
  end_job = ((proc_num+1)*HEIGHT)/proc_total;
#endif

  // -------------------------------------------------------------------------//
  // For every pixel of the image
  for (int j = start_job; j < end_job; ++j) {
    //if (j % 100 == 0) { printf("%d ", j+100); fflush(stdout);}
    for (int i = 0; i < WIDTH; ++i) {
      ColorAccumulator acc = {0};
      Complex base = {(Real)i,(Real)j};
      for (int s = 0; s < samples; ++s) {
          Complex sample = c_add(base, c_uniform01());
          Complex c = c_add(window_base, c_scalar(pointer, sample));
          accumulate(&acc, mandelbrot(c));
      }
      setPixel(i, j, average(&acc, samples));
    }
  }

  // -------------------------------------------------------------------------//
  // Write Image to File
#ifdef __mips__
  if (Join(proc_num, proc_total)) return 0;
#endif
  FILE *image;
  image = fopen(argv[1], "wb");
  if (image == NULL) return Fail("Could not open file %s\n", argv[1]);
  fprintf(image, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  fwrite(_buffer, sizeof(BYTE), sizeof(_buffer), image);
  fclose(image);

  // -------------------------------------------------------------------------//
  // Open Image for Display
#ifdef __mips__
  return 0;
#else
  char cmd[80];
  sprintf(cmd, "display %s", argv[1]);
  return system(cmd);
#endif
}


// ---------------------------------------------------------------------------//
// MAIN WRAPPER
int main(int argc, char *argv[]) {
  return p_main(argc, argv);
}
