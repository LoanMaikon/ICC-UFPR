CFLAGS = -Wall -std=c99
LDFLAGS = -lm

CC = gcc

# arquivos-objeto
	objects = main.o main
     
main: main.o
	$(CC) -o main main.o $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm -f $(objects)