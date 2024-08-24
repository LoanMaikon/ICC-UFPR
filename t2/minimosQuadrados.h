// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include "calculoIntervalar.h"

// Monta a matriz de coeficientes a partir do método dos mínimos quadrados
void montarMatrizCoeficientes(Intervalo** restrict pont_vet, Intervalo* restrict vetA, Intervalo* restrict vetB, Intervalo* restrict x, int N, long long int K);

// Monta o vetor de resultados a partir do método dos mínimos quadrados
void montarVetorResultados(Intervalo* restrict vetB, Intervalo* restrict x, Intervalo* restrict y, int N, long long int K)
