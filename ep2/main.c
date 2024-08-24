#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "likwid.h"

double timestamp(void) {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return ((double)tp.tv_sec * 1.0e3 + (double)tp.tv_nsec * 1.0e-6);
}

double dividedDifference(double *x, double *y, int start, int end) {
    if (start == end) return y[start];
    return (dividedDifference(x, y, start + 1, end) -
            dividedDifference(x, y, start, end - 1)) /
           (x[end] - x[start]);
}

double lagrange(double *x, double *y, int N, double xp) {
    double yp = 0;
    double p;

    for (int i = 0; i < N; i++) {
        p = 1;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                p *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        yp += p * y[i];
    }

    return yp;
}

double newton(double *x, double *y, int N, double xp) {
    double yp = y[0];  // Initialize with f(x0)
    double term = 1.0;

    for (int i = 1; i < N; i++) {
        term *= (xp - x[i - 1]);
        yp += term * dividedDifference(x, y, 0, i);
    }

    return yp;
}

int main(int argc, char *argv[]) {
    int N;
    double *x, *y, yp;
    double tLagrange, tNewton;

    double xp = atof(argv[1]);

    scanf("%d", &N);

    x = malloc(N * sizeof(double));
    y = malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }

    LIKWID_MARKER_INIT;

    LIKWID_MARKER_START("LAGRANGE");
    tLagrange = timestamp();
    yp = lagrange(x, y, N, xp);
    tLagrange = timestamp() - tLagrange;
    LIKWID_MARKER_STOP("LAGRANGE");

    printf("%lf\n", yp);

    LIKWID_MARKER_START("NEWTON");
    tNewton = timestamp();
    yp = newton(x, y, N, xp);
    tNewton = timestamp() - tNewton;
    LIKWID_MARKER_STOP("NEWTON");

    printf("%lf\n", yp);

    printf("%.6lf\n", tLagrange);
    printf("%.6lf\n", tNewton);

    LIKWID_MARKER_CLOSE;

    return 0;
}
