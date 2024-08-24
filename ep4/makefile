CFLAGS = -Wall -std=c99 -I/home/soft/likwid/include -DLIKWID_PERFMON
LDFLAGS = -lm -O3 -mavx -march=native -L/home/soft/likwid/lib -llikwid

CC = gcc

# arquivos-objeto
	objects = main.o main
     
main: main.o
	$(CC) -o main main.o $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

purge:
	rm -f $(objects)