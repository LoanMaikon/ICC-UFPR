// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "calculoIntervalar.h"
#include "eliminacaoGauss.h"
#include "minimosQuadrados.h"
#include "utils.h"
#include "likwid.h"

int main()
{
    int N;
    long long int K;
    Intervalo *x, *y;
    double tGeraSL, tSolucionaSL, tCalculaResiduo;

    scanf("%d %lld", &N, &K);
    // Polinômio de grau N
    // K pontos
    N++; // Número de coeficientes

    // Alocando memória para os vetores de pontos
    x = calloc(K, sizeof(Intervalo));
    y = calloc(K, sizeof(Intervalo));

    // Lendo os pontos
    for (long long int i = 0; i < K; ++i) {
        double tempX, tempY;
        scanf("%lf %lf", &tempX, &tempY);
        x[i] = criaIntervalo(tempX);
        y[i] = criaIntervalo(tempY);
    }

    Intervalo *vetA = calloc(N * N, sizeof(Intervalo));
    Intervalo **pont_vet = calloc(N, sizeof(Intervalo*));
    for (int i = 0; i < N; ++i) {
        pont_vet[i] = vetA + i * N;
    }
    Intervalo *vetB = calloc(N, sizeof(Intervalo));
    Intervalo *vetX = calloc(N, sizeof(Intervalo));


    LIKWID_MARKER_INIT;
    // Likwid
    tGeraSL = timestamp();
    LIKWID_MARKER_START("GERACAO_SISTEMA");

    // Montando a matriz de coeficientes
    montarMatrizCoeficientes(pont_vet, vetA, vetB, x, N, K);

    // Montando o vetor de resultados
    montarVetorResultados(vetB, x, y, N, K);

    // Likwid
    LIKWID_MARKER_STOP("GERACAO_SISTEMA");
    tGeraSL = timestamp() - tGeraSL;
    
    tSolucionaSL = timestamp();
    LIKWID_MARKER_START("SOLUCAO_SISTEMA");

    // Aplicando eliminação de gauss
    eliminacaoGauss(pont_vet, vetA, vetB, N);

    // Aplicando retrosubstituição
    retroSubs(pont_vet, vetA, vetB, vetX, N);

    // Likwid
    LIKWID_MARKER_STOP("SOLUCAO_SISTEMA");
    tSolucionaSL = timestamp() - tSolucionaSL;

    // Alocando resíduo
    Intervalo *residuo = calloc(K, sizeof(Intervalo));

    // Likwid
    tCalculaResiduo = timestamp();
    LIKWID_MARKER_START("CALCULO_RESIDUO");

    // Calculando resíduo
    calculaResiduo(vetX, x, y, N, K, residuo);

    // Likwid
    LIKWID_MARKER_STOP("CALCULO_RESIDUO");
    tCalculaResiduo = timestamp() - tCalculaResiduo;
    LIKWID_MARKER_CLOSE;

    // Imprimindo coeficientes e resíduos
    imprimeCoeficientes(vetX, N);
    imprimeResiduo(residuo, K);

    printf("%lf\n", tGeraSL);
    printf("%lf\n", tSolucionaSL);
    printf("%lf\n", tCalculaResiduo);

    free(x);
    free(y);
    free(vetA);
    free(residuo);
    free(vetB);
    free(vetX);

    return 0;
}