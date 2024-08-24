CFLAGS = -Wall -I/home/soft/likwid/include -DLIKWID_PERFMON
LDFLAGS = -lm -O3 -mavx -march=native -L/home/soft/likwid/lib -llikwid

CC = gcc

# arquivos-objeto
	objects = main.o ajustePol calculoIntervalar.o eliminacaoGauss.o minimosQuadrados.o utils.o
     
ajustePol: main.o calculoIntervalar.o eliminacaoGauss.o minimosQuadrados.o utils.o
	$(CC) -o ajustePol main.o calculoIntervalar.o eliminacaoGauss.o minimosQuadrados.o utils.o $(LDFLAGS)

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

calculoIntervalar.o: calculoIntervalar.c
	$(CC) -c $(CFLAGS) calculoIntervalar.c

eliminacaoGauss.o: eliminacaoGauss.c
	$(CC) -c $(CFLAGS) eliminacaoGauss.c

minimosQuadrados.o: minimosQuadrados.c
	$(CC) -c $(CFLAGS) minimosQuadrados.c

utils.o: utils.c
	$(CC) -c $(CFLAGS) utils.c

purge:
	rm -f $(objects) ajustePol

clean:
	rm -f $(objects) ajustePol