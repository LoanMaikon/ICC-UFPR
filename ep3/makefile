CFLAGS = -Wall -I/home/soft/likwid/include -DLIKWID_PERFMON
LDFLAGS = -lm -O3 -mavx -march=native -L/home/soft/likwid/lib -llikwid

CC = gcc

# arquivos-objeto
	objects = labMonteCarlo.o labMonteCarlo utils.o
     
labMonteCarlo: labMonteCarlo.o utils.o
	$(CC) -o labMonteCarlo labMonteCarlo.o utils.o $(LDFLAGS)

labMonteCarlo.o: labMonteCarlo.c
	$(CC) -c $(CFLAGS) labMonteCarlo.c

utils.o: utils.c
	$(CC) -c $(CFLAGS) utils.c

clean:
	rm -f $(objects)
