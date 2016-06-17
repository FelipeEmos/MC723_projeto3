#include <stdio.h>

#ifndef __mips__
#include <stdlib.h>
#endif

#include "fpu.h"

#define WIDTH   400
#define HEIGHT  400
#define BYTE    unsigned char


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

Color interpolate_linear(Color *c1, Color *c2, double alpha) {
  Color c;
  double beta = d_sub(1.0,alpha);
  c.r = (BYTE)d_add(d_mult((double)c1->r,beta), d_mult((double)c2->r,alpha));
  c.g = (BYTE)d_add(d_mult((double)c1->g,beta), d_mult((double)c2->g,alpha));
  c.b = (BYTE)d_add(d_mult((double)c1->b,beta), d_mult((double)c2->b,alpha));
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

Color _buffer[HEIGHT][WIDTH];

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

int max_it = 2000;
double scale = 1.0;

Color mandelbrot(Complex c) {
  // -------------------------------------------------------------------------//
  // Iterate Mandelbrot Set
  Complex z = {0.0, 0.0};
  int it = 0;
  while (c_mod(z) < (1 << 16) && it++ < max_it) {
    z = c_add(c_mult(z,z), c);
  }

  // -------------------------------------------------------------------------//
  // Determine the color for the point
  Color col = Black;
  int ind;
  if (it > 1 && it < max_it) {
    double smooth_it = d_sub(d_add(it,1.0),d_mult(d_log(d_mult(d_log(c_mod(z)),over2log2)),overlog2));
    smooth_it = d_mult(smooth_it,scale);
    ind = d_floor(smooth_it);
    col = interpolate_linear(&_pallete[ind%pal], &_pallete[(ind+1)%pal], d_frac(smooth_it));
  }
  return col;
}

// ---------------------------------------------------------------------------//
// PRESETS

void loadpreset(Complex *center, Complex *window, int preset) {
  switch (preset) {
    case 1:
      // Mandelbrot Center
      center->r =  0.0;
      center->i =  0.0;
      window->r =  4.2;
      window->i = -4.2;
      scale = 1.0;
      max_it = 2000;
      break;
    case 2:
      // Mandelbrot Feature 1
      center->r = -0.743643135;
      center->i =  0.131825963;
      window->r =  0.000014628;
      window->i = -0.000014628;
      scale = 0.03;
      max_it = 2000;
      break;
    case 3:
      // Mandelbrot Feature 2
      center->r = -0.743643887037151;
      center->i =  0.131825904205330;
      window->r =  0.000000000051299;
      window->i = -0.000000000051299;
      scale = 0.02;
      max_it = 8000;
      break;
  }
}

// ---------------------------------------------------------------------------//
// MAIN

int p_main(int argc, char *argv[]) {
  // -------------------------------------------------------------------------//
  // Reading Parameters
  if (argc < 4) {
    printf("Usage %s imagefile samples_per_pixel preset\n", argv[0]);
    return 1;
  }
  int samples;
  sscanf(argv[2], "%d", &samples);
  int preset;
  sscanf(argv[3], "%d", &preset);

  // -------------------------------------------------------------------------//
  // Mandelbrot Setup
  Complex center;
  Complex window;
  loadpreset(&center, &window, preset);
  Complex half = {0.5, 0.5};
  Complex window_base = c_sub(center, c_scalar(window, half));
  Complex window_limit = c_add(center, c_scalar(window, half));
  Complex offset = {1.0/(double)WIDTH, 1.0/(double)HEIGHT};
  Complex pointer = c_scalar(c_sub(window_limit, window_base), offset);

  // -------------------------------------------------------------------------//
  // For every pixel of the image
  for (int j = 0; j < HEIGHT; ++j) {
    if ( j % 100 == 0) { printf("%d ", j+100); fflush(stdout);}
    for (int i = 0; i < WIDTH; ++i) {
      ColorAccumulator acc = {0};
      Complex base = {(double)i,(double)j};
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
  FILE *image;
  image = fopen(argv[1], "wb");
  if (image == NULL) {
    printf("Could not open file %s\n", argv[1]);
    return 1;
  }
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
