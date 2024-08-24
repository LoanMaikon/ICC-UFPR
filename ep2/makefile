CFLAGS = -Wall  -I/home/soft/likwid/include -DLIKWID_PERFMON
LDFLAGS = -lm -O3 -mavx -march=native -L/home/soft/likwid/lib -llikwid

CC = gcc

# arquivos-objeto
	objects = main.o interpola
     
interpola: main.o
	$(CC) -o interpola main.o $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects)

purge:
	rm -f $(objects)