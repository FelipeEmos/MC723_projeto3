#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH   900
#define HEIGHT  900
#define BYTE    unsigned char

// ---------------------------------------------------------------------------//
// Mathematics

inline double uniform01() {
  return ((double)rand()/(double)RAND_MAX);
}

const double overlog2 = 1.44269504088896;
const double over2log2 = 0.721347520444482;

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
  double beta = 1.0 - alpha;
  c.r = c1->r*beta + c2->r*alpha;
  c.g = c1->g*beta + c2->g*alpha;
  c.b = c1->b*beta + c2->b*alpha;
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

Color _buffer[HEIGHT][WIDTH] = {0};

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
// COMPLEX

typedef struct {
    double r;
    double i;
} Complex;

double c_mod(Complex z) {
  return (z.r*z.r + z.i*z.i);
}

inline Complex c_scalar(Complex z, double s_r, double s_i) {
  z.r *= s_r;
  z.i *= s_i;
  return z;
}

Complex c_mult(Complex z1, Complex z2) {
  Complex z;
  z.r = (z1.r * z2.r) - (z1.i * z2.i);
  z.i = (z1.r * z2.i) + (z1.i * z2.r);
  return z;
}

Complex c_add(Complex z1, Complex z2) {
  Complex z;
  z.r = z1.r + z2.r;
  z.i = z1.i + z2.i;
  return z;
}

Complex c_sub(Complex z1, Complex z2) {
  Complex z;
  z.r = z1.r - z2.r;
  z.i = z1.i - z2.i;
  return z;
}

// ---------------------------------------------------------------------------//
// MANDELBROT

const int max_it = 8000;
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
    double smooth_it = it + 1.0 - log(log(c_mod(z))*over2log2)*overlog2;
    smooth_it *= scale;
    ind = (int)floor(smooth_it);
    double alpha = fmod(smooth_it, 1.0);
    col = interpolate_linear(&_pallete[ind%pal], &_pallete[(ind+1)%pal], alpha);
  }
  return col;
}


// MANDELBROT
// ---------------------------------------------------------------------------//

int main(int argc, char *argv[]) {
  // Check for parameters
  if (argc < 3) {
    printf("Usage %s imagefile samples_per_pixel\n", argv[0]);
    return 1;
  }
  int samples;
  sscanf(argv[2], "%d", &samples);
  srand((unsigned)time(NULL));

  // -------------------------------------------------------------------------//
  // Mandelbrot Setup

  // Mandelbrot Center
  //Complex center = {0.0, 0.0};
  //Complex window = {4.2, -4.2};
  //scale = 1.0;
  // Mandelbrot Feature 1
  //Complex center = {-0.743643135, 0.131825963};
  //Complex window = {0.000014628, -0.000014628};
  //scale = 0.03;
  // Mandelbrot Feature 2
  Complex center = {-0.743643887037151, 0.131825904205330};
  Complex window = {0.000000000051299, -0.000000000051299};
  scale = 0.02;

  // -------------------------------------------------------------------------//
  Complex window_base = c_sub(center, c_scalar(window, 0.5, 0.5));
  Complex window_limit = c_add(center, c_scalar(window, 0.5, 0.5));
  Complex pointer = c_scalar(c_sub(window_limit, window_base), 1.0/WIDTH, 1.0/HEIGHT);

  // -------------------------------------------------------------------------//
  // For every pixel of the image
  for (int j = 0; j < HEIGHT; ++j) {
    if ( j % 100 == 0) { printf("%d ", j+100); fflush(stdout);}
    for (int i = 0; i < WIDTH; ++i) {
      ColorAccumulator acc = {0};
      for (int s = 0; s < samples; ++s) {
          double sample_i = i + uniform01();
          double sample_j = j + uniform01();
          Complex c = c_add(window_base, c_scalar(pointer, sample_i, sample_j));
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
  //char cmd[80];
  //sprintf(cmd, "display %s", argv[1]);
  //return system(cmd);
  return 0;
}
