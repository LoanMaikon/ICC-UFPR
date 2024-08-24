#include <getopt.h> /* getopt */
#include <stdio.h>
#include <stdlib.h> /* exit, malloc, calloc, etc. */
#include <string.h>
#include <time.h>

#include "likwid.h"
#include "matriz.h"
#include "utils.h"

/**
 * Exibe mensagem de erro indicando forma de uso do programa e termina
 * o programa.
 */

static void usage(char *progname) {
    fprintf(stderr, "Forma de uso: %s [ <ordem> ] \n", progname);
    exit(1);
}

/**
 * Programa principal
 * Forma de uso: matmult [ -n <ordem> ]
 * -n <ordem>: ordem da matriz quadrada e dos vetores
 *
 */

int main(int argc, char *argv[]) {
    int n = DEF_SIZE;

    MatRow mRow_1, mRow_2, resMat;
    Vetor vet, res;
    rtime_t tempoMultMatMat, tempoMultMatVet, tempoMultMatMatAntigo,
        tempoMultMatVetAntigo;

    /* =============== TRATAMENTO DE LINHA DE COMANDO =============== */

    if (argc < 2) usage(argv[0]);

    n = atoi(argv[1]);

    /* ================ FIM DO TRATAMENTO DE LINHA DE COMANDO ========= */

    srandom(20232);

    res = geraVetor(n, 1);  // (real_t *) malloc (n*sizeof(real_t));
    resMat = geraMatRow(n, n, 1);

    mRow_1 = geraMatRow(n, n, 0);
    mRow_2 = geraMatRow(n, n, 0);

    vet = geraVetor(n, 0);

    if (!res || !resMat || !mRow_1 || !mRow_2 || !vet) {
        fprintf(stderr, "Falha em alocação de memória !!\n");
        liberaVetor((void *)mRow_1);
        liberaVetor((void *)mRow_2);
        liberaVetor((void *)resMat);
        liberaVetor((void *)vet);
        liberaVetor((void *)res);
        exit(2);
    }

#ifdef _DEBUG_
    prnMat(mRow_1, n, n);
    prnMat(mRow_2, n, n);
    prnVetor(vet, n);
    printf("=================================\n\n");
#endif /* _DEBUG_ */

    LIKWID_MARKER_INIT;

    LIKWID_MARKER_START("MULT_MAT_VET");
    tempoMultMatVet = timestamp();
    multMatVet(mRow_1, vet, n, n, res);
    tempoMultMatVet = timestamp() - tempoMultMatVet;
    LIKWID_MARKER_STOP("MULT_MAT_VET");

    LIKWID_MARKER_START("MULT_MAT_MAT");
    tempoMultMatMat = timestamp();
    multMatMat(mRow_1, mRow_2, n, resMat);
    tempoMultMatMat = timestamp() - tempoMultMatMat;
    LIKWID_MARKER_STOP("MULT_MAT_MAT");

    LIKWID_MARKER_START("MULT_MAT_VET_ANTIGO");
    tempoMultMatVetAntigo = timestamp();
    multMatVetAntigo(mRow_1, vet, n, n, res);
    tempoMultMatVetAntigo = timestamp() - tempoMultMatVetAntigo;
    LIKWID_MARKER_STOP("MULT_MAT_VET_ANTIGO");

    LIKWID_MARKER_START("MULT_MAT_MAT_ANTIGO");
    tempoMultMatMatAntigo = timestamp();
    multMatMatAntigo(mRow_1, mRow_2, n, resMat);
    tempoMultMatMatAntigo = timestamp() - tempoMultMatMatAntigo;
    LIKWID_MARKER_STOP("MULT_MAT_MAT_ANTIGO");

    LIKWID_MARKER_CLOSE;

#ifdef _DEBUG_
    prnVetor(res, n);
    prnMat(resMat, n, n);
#endif /* _DEBUG_ */

    liberaVetor((void *)mRow_1);
    liberaVetor((void *)mRow_2);
    liberaVetor((void *)resMat);
    liberaVetor((void *)vet);
    liberaVetor((void *)res);

    printf("%lf\n", tempoMultMatVet);
    printf("%lf\n", tempoMultMatMat);
    printf("%lf\n", tempoMultMatVetAntigo);
    printf("%lf\n", tempoMultMatMatAntigo);

    return 0;
}
