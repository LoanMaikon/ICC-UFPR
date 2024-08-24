// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#ifndef CALCULO_INTERVALAR_H
#define CALCULO_INTERVALAR_H

#include <stdint.h>

// Union dada em aula para representação mais elaborada de um double
typedef union {
    int64_t i;
    double d;
    struct {
        uint64_t mantissa : 52;
        uint64_t exponent : 11;
        uint64_t sign : 1;
    } parts;
} Double_t;

// Struct para representar um intervalo (intervalo menor e intervalo maior) de um double
typedef struct {
    Double_t intervaloMenor;
    Double_t intervaloMaior;
} Intervalo;

// soma recebe como argumentos dois intervalos a serem somados
// retorna soma intervalar de x + y
Intervalo soma(Intervalo x, Intervalo y);

// subtracao recebe como argumentos dois intervalos a serem subtraidos
// retorna subtracao intervalar de x + y
Intervalo subtracao(Intervalo x, Intervalo y);

// multiplicacao recebe como argumentos dois intervalos a serem multiplicados
// retorna multiplicacao intervalar de x * y
Intervalo multiplicacao(Intervalo x, Intervalo y);

// divisao recebe como argumentos dois intervalos a serem divididos
// retorna divisao intervalar de x / y
Intervalo divisao(Intervalo x, Intervalo y);

// potenciacao recebe um intervalo e aplica a pontenciacao em p
// retorna x elevado a p
Intervalo potenciacao(Intervalo x, int p);

/**
 * Cria um intervalo X = [m(x), M(x)], onde m(x) é o 
 * maior número de máquina menor ou igual a x e M(x) 
 * é o menor número de máquina maior ou igual a x.
*/
Intervalo criaIntervalo(double x);

void imprimeIntervalo(Intervalo x);

#endif