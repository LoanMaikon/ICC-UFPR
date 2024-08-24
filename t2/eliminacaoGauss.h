// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include "calculoIntervalar.h"

// Imprime uma matriz (depuração)
void imprimeMatriz(Intervalo **pont_vet, Intervalo *vetA, Intervalo *vetB, int N);

void eliminacaoGauss(Intervalo **pont_vet, Intervalo *vetA, Intervalo *vetB, int N);

void retroSubs(Intervalo **pont_vet, Intervalo *vetA, Intervalo *vetB, Intervalo *vetX, int N);

void calculaResiduo(Intervalo *vetX, Intervalo *x, Intervalo *y, int N, long long int K, Intervalo *residuo);

void imprimeCoeficientes(Intervalo *vetX, int N);

void imprimeResiduo(Intervalo *residuo, long long int K);
