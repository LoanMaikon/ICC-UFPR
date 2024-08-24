// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "eliminacaoGauss.h"

#define UF 8

// Recebe intervalo A e B e aplica o resultado da retrosubstituição em X
void retroSubs(Intervalo** restrict pont_vet, Intervalo* restrict vetA, Intervalo* restrict vetB, Intervalo* restrict vetX, int N)
{
    for (int i = N - 1; i >= 0; i--) {
        vetX[i] = vetB[i];
        for (int j = i + 1; j < N; j++)
            vetX[i] = subtracao(vetX[i], multiplicacao(pont_vet[i][j], vetX[j]));
        vetX[i] = divisao(vetX[i], pont_vet[i][i]);
    }
}

void trocaLinhas(Intervalo** restrict pont_vet, Intervalo* restrict vetA, Intervalo* restrict vetB, int i, int iPivo, int N)
{
    Intervalo *aux1;
    aux1 = pont_vet[i];
    pont_vet[i] = pont_vet[iPivo];
    pont_vet[iPivo] = aux1;

    Intervalo aux2;
    aux2 = vetB[i];
    vetB[i] = vetB[iPivo];
    vetB[iPivo] = aux2;
}

int achaMax(Intervalo** restrict pont_vet, Intervalo* restrict vetA, int i, int N)
{
    int max = i;

    for(int k = i + 1; k < N; k++)
        if(fabs(pont_vet[k][i].intervaloMaior.d) > fabs(pont_vet[max][i].intervaloMaior.d))
            max = k;

    return max;
}


void eliminacaoGauss(Intervalo** restrict pont_vet, Intervalo* restrict vetA, Intervalo* restrict vetB, int N) // UF = 8
{
    for(int i = 0; i < N; i++)
    {
        for(int k = i + 1; k < N; k++)
        {
            Intervalo m = divisao(pont_vet[k][i], pont_vet[i][i]);
            pont_vet[k][i].intervaloMenor.d = 0.0;
            pont_vet[k][i].intervaloMaior.d = 0.0;

            for(int j = i + 1; j < N; j++)
                pont_vet[k][j] = subtracao(pont_vet[k][j], multiplicacao(m, pont_vet[i][j]));

            vetB[k] = subtracao(vetB[k], multiplicacao(m, vetB[i]));
        }
    }
}

// Imprime uma matriz (depuração)
void imprimeMatriz(Intervalo **pont_vet, Intervalo *vetA, Intervalo *vetB, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N ; ++j)
        {
            imprimeIntervalo(vetA[i * N + j]);
            printf(" ");
        }
        printf("| ");
        imprimeIntervalo(vetB[i]);
        printf("\n");
    }
    printf("\n");
}


// Imprime o resíduo de um sistema linear
void calculaResiduo(Intervalo* restrict vetX, Intervalo* restrict x, Intervalo* restrict y, int N, long long int K, Intervalo* restrict residuo) // UF = 8
{
    for (long long int k = 0; k < K; k++) {
        Intervalo temp = criaIntervalo(0.0);
        int i;

        temp = soma(temp, vetX[0]);
        Intervalo pot = x[k];
        for (i = 1; i < N - N % UF; i += UF) {
            Intervalo pot1 = multiplicacao(pot, x[k]);
            Intervalo pot2 = multiplicacao(pot1, x[k]);
            Intervalo pot3 = multiplicacao(pot2, x[k]);
            Intervalo pot4 = multiplicacao(pot3, x[k]);
            Intervalo pot5 = multiplicacao(pot4, x[k]);
            Intervalo pot6 = multiplicacao(pot5, x[k]);
            Intervalo pot7 = multiplicacao(pot6, x[k]);
            Intervalo pot8 = multiplicacao(pot7, x[k]);
            temp = soma(temp, multiplicacao(vetX[i], pot));
            temp = soma(temp, multiplicacao(vetX[i+1], pot1));
            temp = soma(temp, multiplicacao(vetX[i+2], pot2));
            temp = soma(temp, multiplicacao(vetX[i+3], pot3));
            temp = soma(temp, multiplicacao(vetX[i+4], pot4));
            temp = soma(temp, multiplicacao(vetX[i+5], pot5));
            temp = soma(temp, multiplicacao(vetX[i+6], pot6));
            temp = soma(temp, multiplicacao(vetX[i+7], pot7));
            pot = pot8;
        }

        for (; i < N; i++) {
            temp = soma(temp, multiplicacao(vetX[i], pot));
            pot = multiplicacao(pot, x[k]);
        }

        residuo[k] = subtracao(y[k], temp);
    }
}

// Imprime os coeficientes de um sistema linear
void imprimeCoeficientes(Intervalo *vetX, int N)
{
    for(int i = 0; i < N; i++) {
        imprimeIntervalo(vetX[i]);
        printf(" ");
    }
    printf("\n");
}

void imprimeResiduo(Intervalo *residuo, long long int K)
{
    for(long long int i = 0; i < K; i++) {
        imprimeIntervalo(residuo[i]);
        printf(" ");
    }
    printf("\n");
}