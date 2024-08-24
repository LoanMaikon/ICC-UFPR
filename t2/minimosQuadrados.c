// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include "minimosQuadrados.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define UF 2


// Monta a matriz de coeficientes a partir do método dos mínimos quadrados
void montarMatrizCoeficientes(Intervalo** restrict pont_vet, Intervalo* restrict vetA, Intervalo* restrict vetB, Intervalo* restrict x, int N, long long int K)
{
    /*
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < K; k++) {
                A[i][j] = soma(A[i][j], potenciacao(x[k], i + j));
            }
        }
    }
    */

    for(int k = 0; k < K; k++) {
        Intervalo xk[N];
        xk[0] = criaIntervalo(1);
        xk[1] = x[k];
        for(int i = 2; i < N; i++) {
            xk[i] = multiplicacao(xk[i - 1], x[k]);
        }

        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                pont_vet[i][j] = soma(pont_vet[i][j], xk[i + j]);
            }
        }
    }
}

// Monta a matriz de resultados a partir do método dos mínimos quadrados
void montarVetorResultados(Intervalo* restrict vetB, Intervalo* restrict x, Intervalo* restrict y, int N, long long int K)
{
    /*
    for(int i = 0; i < N; i++) {
        for(int k = 0; k < K; k++) {
            vetB[i] = soma(vetB[i], multiplicacao(y[k], potenciacao(x[k], i)));
        }
    }
    */

    for(int k = 0; k < K; k++) {
        Intervalo xk[N];
        xk[0] = criaIntervalo(1);
        xk[1] = x[k];
        for(int i = 2; i < N; i++) {
            xk[i] = multiplicacao(xk[i - 1], x[k]);
        }

        for(int i = 0; i < N - N % UF; i+=UF) {
            vetB[i] = soma(vetB[i], multiplicacao(y[k], xk[i]));
            vetB[i + 1] = soma(vetB[i + 1], multiplicacao(y[k], xk[i + 1]));
        }

        for(int i = N - N % UF; i < N; i++) {
            vetB[i] = soma(vetB[i], multiplicacao(y[k], xk[i]));
        }
    }
}
