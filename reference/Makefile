CFLAGS=-O2 -std=c99
CC=gcc
MIPSCC=mips-newlib-elf-gcc
MIPSCFLAGS=-O2 -std=c99 -specs=archc

.PHONY: all hard

all: mandel mandel.mips hard

hard: mandel_hard_1.mips mandel_hard_2.mips mandel_hard_3.mips mandel_hard_4.mips

##### FPU RULES ####

fpu.o: fpu.c
	$(CC) -c fpu.c -o fpu.o $(CFLAGS)

fpu_mips.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips.o $(MIPSCFLAGS)

fpu_mips_hard_1.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips_hard_1.o $(MIPSCFLAGS) -DHARD -DTID=1

fpu_mips_hard_2.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips_hard_2.o $(MIPSCFLAGS) -DHARD -DTID=2

fpu_mips_hard_3.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips_hard_3.o $(MIPSCFLAGS) -DHARD -DTID=3

fpu_mips_hard_4.o: fpu.c
	$(MIPSCC) -c fpu.c -o fpu_mips_hard_4.o $(MIPSCFLAGS) -DHARD -DTID=4

#### LOCK PERIPHERAL RULES ####

lock.o: lock.c
	$(MIPSCC) -c lock.c -o lock.o $(MIPSCFLAGS)

#### MANDELBROT RULES ####

mandelbrot.o: mandelbrot.c
	$(CC) -c mandelbrot.c -o mandelbrot.o $(CFLAGS)

mandelbrot_mips.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips.o $(MIPSCFLAGS)

mandelbrot_mips_1.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips_1.o $(MIPSCFLAGS) -DTID=1

mandelbrot_mips_2.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips_2.o $(MIPSCFLAGS) -DTID=2

mandelbrot_mips_3.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips_3.o $(MIPSCFLAGS) -DTID=3

mandelbrot_mips_4.o: mandelbrot.c
	$(MIPSCC) -c mandelbrot.c -o mandelbrot_mips_4.o $(MIPSCFLAGS) -DTID=4

#### APPLICATION RULES #####

mandel: mandelbrot.o fpu.o
	$(CC) mandelbrot.o fpu.o -o mandel $(CFLAGS) -lm

mandel.mips: mandelbrot_mips.o fpu_mips.o lock.o
	$(MIPSCC) mandelbrot_mips.o fpu_mips.o lock.o -o mandel.mips $(MIPSCFLAGS) -lm

mandel_hard_1.mips: mandelbrot_mips_1.o fpu_mips_hard_1.o lock.o
	$(MIPSCC) mandelbrot_mips_1.o fpu_mips_hard_1.o lock.o -o mandel_hard_1.mips $(MIPSCFLAGS)

mandel_hard_2.mips: mandelbrot_mips_2.o fpu_mips_hard_2.o lock.o
	$(MIPSCC) mandelbrot_mips_2.o fpu_mips_hard_2.o lock.o -o mandel_hard_2.mips $(MIPSCFLAGS)

mandel_hard_3.mips: mandelbrot_mips_3.o fpu_mips_hard_3.o lock.o
	$(MIPSCC) mandelbrot_mips_3.o fpu_mips_hard_3.o lock.o -o mandel_hard_3.mips $(MIPSCFLAGS)

mandel_hard_4.mips: mandelbrot_mips_4.o fpu_mips_hard_4.o lock.o
	$(MIPSCC) mandelbrot_mips_4.o fpu_mips_hard_4.o lock.o -o mandel_hard_4.mips $(MIPSCFLAGS)

#### CLEANING RULE ####

clean:
	rm -f mandel *.mips *.o
