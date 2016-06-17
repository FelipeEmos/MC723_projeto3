CFLAGS=-O2 -std=c99
CC=gcc
MIPSCC=mips-newlib-elf-gcc
MIPSCFLAGS=-O2 -std=c99 -specs=archc

all: mandel mandel.mips mandel_hard.mips

fpu.o: fpu.c
	$(CC) -c fpu.c -o fpu.o $(CFLAGS)

mandelbrot.o: mandelbrot.c
	$(CC) -c mandelbrot.c -o mandelbrot.o $(CFLAGS)

mandel: mandelbrot.o fpu.o
	$(CC) mandelbrot.o fpu.o -o mandel $(CFLAGS) -lm

fpu_mips.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips.o $(MIPSCFLAGS)

mandelbrot_mips.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips.o $(MIPSCFLAGS)

mandel.mips: mandelbrot_mips.o fpu_mips.o
	$(MIPSCC) mandelbrot_mips.o fpu_mips.o -o mandel.mips $(MIPSCFLAGS) -lm

fpu_mips_hard.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips_hard.o $(MIPSCFLAGS) -DHARD

mandel_hard.mips: mandelbrot_mips.o fpu_mips_hard.o
	$(MIPSCC) mandelbrot_mips.o fpu_mips_hard.o -o mandel_hard.mips $(MIPSCFLAGS)

clean:
	rm -f mandel *.mips *.o
