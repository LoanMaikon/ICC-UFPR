#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "likwid.h"

double timestamp(void) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}

void backSubstitution(double **A, double *B, double *X, int N) {
    for (int i = N - 1; i >= 0; i--) {
        X[i] = B[i];
        for (int j = i + 1; j < N; j++) {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
    }
}

int searchMax(double **A, int i, int N) {
    int max = i;

    for (int k = i + 1; k < N; ++k) {
        if (fabs(A[k][i]) > fabs(A[max][i])) {
            max = k;
        }
    }

    return max;
}

void tradeLines(double **A, double *B, int i, int iPivo, int N) {
    double aux;

    for (int j = 0; j < N; ++j) {
        aux = A[i][j];
        A[i][j] = A[iPivo][j];
        A[iPivo][j] = aux;
    }

    aux = B[i];
    B[i] = B[iPivo];
    B[iPivo] = aux;
}

void GaussElimination_1method(double **A, double *B, int N) {
    for (int i = 0; i < N; ++i) {
        int iPivo = searchMax(A, i, N);

        if (i != iPivo) {
            tradeLines(A, B, i, iPivo, N);
        }

        for (int k = i + 1; k < N; ++k) {
            double m = A[k][i] / A[i][i];
            A[k][i] = 0.0;

            for (int j = i + 1; j < N; ++j) {
                A[k][j] -= m * A[i][j];
            }

            B[k] -= m * B[i];
        }
    }
}

void GaussElimination_2method(double **A, double *B, int N) {
    for (int i = 0; i < N; ++i) {
        int iPivo = searchMax(A, i, N);

        if (i != iPivo) {
            tradeLines(A, B, i, iPivo, N);
        }

        for (int k = i + 1; k < N; ++k) {
            for (int j = i + 1; j < N; ++j) {
                A[k][j] = A[k][j]*A[i][i] - A[i][j]*A[k][i];
            }

            B[k] = B[k]*A[i][i] - B[i]*A[k][i];
        }
    }
}

void GaussElimination_3method(double **A, double *B, int N) {
    for (int i = 0; i < N; ++i) {
        double pivot = A[i][i];
        
        // dividing the row by the pivot
        for (int j = i; j < N; ++j) {
            A[i][j] /= pivot;
        }
        B[i] /= pivot;

        // eliminating elements of the column
        for (int k = i + 1; k < N; ++k) {
            double multiplier = A[k][i];
            
            for (int j = i; j < N; ++j) {
                A[k][j] -= multiplier * A[i][j];
            }
            B[k] -= multiplier * B[i];
        }
    }
}

double findResidue(double **A, double *B, double *X, int N) {
    double *residue = malloc(N * sizeof(double));
    double maxResidue = 0.0;

    for (int i = 0; i < N; i++) {
        residue[i] = B[i];
        for (int j = 0; j < N; j++) {
            residue[i] -= A[i][j] * X[j];
        }
        if (fabs(residue[i]) > maxResidue) {
            maxResidue = fabs(residue[i]);
        }
    }

    free(residue);
    return maxResidue;
}

int applyOperations(double **A, double *B, int N, double *X) {
    // creating copies of A, B and X
    double **A_copy1 = malloc(N * sizeof(double *));
    double *B_copy1 = malloc(N * sizeof(double));
    double *X_copy1 = malloc(N * sizeof(double));
    double **A_copy2 = malloc(N * sizeof(double *));
    double *B_copy2 = malloc(N * sizeof(double));
    double *X_copy2 = malloc(N * sizeof(double));
    double **A_copy3 = malloc(N * sizeof(double *));
    double *B_copy3 = malloc(N * sizeof(double));
    double *X_copy3 = malloc(N * sizeof(double));
    double start, end;

    for (int i = 0; i < N; i++) {
        A_copy1[i] = malloc(N * sizeof(double));
        A_copy2[i] = malloc(N * sizeof(double));
        A_copy3[i] = malloc(N * sizeof(double));
    }

    // copying A, B and X
    for (int i = 0; i < N; i++) {
        B_copy1[i] = B[i];
        X_copy1[i] = X[i];
        B_copy2[i] = B[i];
        X_copy2[i] = X[i];
        B_copy3[i] = B[i];
        X_copy3[i] = X[i];
        for (int j = 0; j < N; j++) {
            A_copy1[i][j] = A[i][j];
            A_copy2[i][j] = A[i][j];
            A_copy3[i][j] = A[i][j];
        }
    }

    // 1st method
    LIKWID_MARKER_START("Metodo_1");
    start = timestamp();
    GaussElimination_1method(A_copy1, B_copy1, N);
    end = timestamp();
    backSubstitution(A_copy1, B_copy1, X_copy1, N);
    LIKWID_MARKER_STOP("Metodo_1");

    printf("===== 1st method =====\n");
    for (int i = 0; i < N; i++) { // solution
        printf("%.6lf\n", X_copy1[i]);
    }
    printf("Residuo: %.6e\n", findResidue(A, B, X_copy1, N)); // residue
    printf("Tempo: %.6lf\n", end - start); // time

    // 2nd method
    LIKWID_MARKER_START("Metodo_2");
    start = timestamp();
    GaussElimination_2method(A_copy2, B_copy2, N);
    end = timestamp();
    backSubstitution(A_copy2, B_copy2, X_copy2, N);
    LIKWID_MARKER_STOP("Metodo_2");

    printf("\n===== 2nd method =====\n");
    for (int i = 0; i < N; i++) { // solution
        printf("%.6lf\n", X_copy2[i]);
    }
    printf("Residuo: %.6e\n", findResidue(A, B, X_copy2, N)); // residue
    printf("Tempo: %.6lf\n", end - start); // time

    // 3rd method
    LIKWID_MARKER_START("Metodo_3");
    start = timestamp();
    GaussElimination_3method(A_copy3, B_copy3, N);
    end = timestamp();
    backSubstitution(A_copy3, B_copy3, X_copy3, N);
    LIKWID_MARKER_STOP("Metodo_3");

    printf("\n===== 3rd method =====\n");
    for (int i = 0; i < N; i++) { // solution
        printf("%.6lf\n", X_copy3[i]);
    }
    printf("Residuo: %.6e\n", findResidue(A, B, X_copy3, N)); // residue
    printf("Tempo: %.6lf\n", end - start); // time
    printf("\n");

    // memory free
    for (int i = 0; i < N; i++) {
        free(A_copy1[i]);
        free(A_copy2[i]);
        free(A_copy3[i]);
    }
    free(A_copy1);
    free(A_copy2);
    free(A_copy3);
    free(B_copy1);
    free(B_copy2);
    free(B_copy3);
    free(X_copy1);
    free(X_copy2);
    free(X_copy3);

    return 0;
}

int main() {
    int N, i, j;
    double **A, *B;
    double *X;  // solution

    LIKWID_MARKER_INIT;

    // reading the matrix size
    scanf("%d", &N);

    A = malloc(N * sizeof(double *));
    B = malloc(N * sizeof(double));
    X = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(double));
    }

    // reading the matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j <= N; j++) {
            if (j < N) {
                scanf("%lf", &A[i][j]);
            } else {
                scanf("%lf", &B[i]);
            }
        }
    }
    applyOperations(A, B, N, X);

    // memory free
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(X);

    LIKWID_MARKER_CLOSE;

    return 0;
}