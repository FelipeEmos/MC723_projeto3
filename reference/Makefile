CFLAGS=-O2 -std=c99
CC=gcc
MIPSCC=mips-newlib-elf-gcc
MIPSCFLAGS= -O2 -std=c99 -specs=archc

all: mandel mandel.mips mandel_hard.mips

##### FPU RULES ####

fpu.o: fpu.c
	$(CC) -c fpu.c -o fpu.o $(CFLAGS)

fpu_mips.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips.o $(MIPSCFLAGS)

fpu_mips_hard.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips_hard.o $(MIPSCFLAGS) -DHARD

#### LOCK PERIPHERAL RULES ####

lock.o: lock.c
	$(MIPSCC) -c lock.c -o lock.o $(MIPSCFLAGS)

#### MANDELBROT RULES ####

mandelbrot.o: mandelbrot.c
	$(CC) -c mandelbrot.c -o mandelbrot.o $(CFLAGS)

mandelbrot_mips.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips.o $(MIPSCFLAGS)

#### APPLICATION RULES #####

mandel: mandelbrot.o fpu.o
	$(CC) mandelbrot.o fpu.o -o mandel $(CFLAGS) -lm

mandel.mips: mandelbrot_mips.o fpu_mips.o lock.o
	$(MIPSCC) mandelbrot_mips.o fpu_mips.o lock.o -o mandel.mips $(MIPSCFLAGS) -lm

mandel_hard.mips: mandelbrot_mips.o fpu_mips_hard.o lock.o
	$(MIPSCC) mandelbrot_mips.o fpu_mips_hard.o lock.o -o mandel_hard.mips $(MIPSCFLAGS)

#### CLEANING RULE ####

clean:
	rm -f mandel *.mips *.o
