#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef union {
    int64_t i;
    double d;
    struct {
        uint64_t mantissa : 52;
        uint64_t exponent : 11;
        uint64_t sign : 1;
    } parts;
} Double_t;

typedef struct {
    Double_t intervaloMenor;
    Double_t intervaloMaior;
} Intervalo;

Intervalo soma(Intervalo x, Intervalo y) {
    Intervalo resultado;

    resultado.intervaloMenor.d = x.intervaloMenor.d + y.intervaloMenor.d;
    resultado.intervaloMaior.d = x.intervaloMaior.d + y.intervaloMaior.d;

    return resultado;
}

Intervalo subtracao(Intervalo x, Intervalo y) {
    Intervalo resultado;

    resultado.intervaloMenor.d = x.intervaloMenor.d - y.intervaloMaior.d;
    resultado.intervaloMaior.d = x.intervaloMaior.d - y.intervaloMenor.d;

    return resultado;
}

Intervalo multiplicacao(Intervalo x, Intervalo y) {
    Intervalo resultado;

    resultado.intervaloMenor.d = x.intervaloMenor.d * y.intervaloMenor.d;
    resultado.intervaloMaior.d = x.intervaloMaior.d * y.intervaloMaior.d;

    return resultado;
}

Intervalo divisao(Intervalo x, Intervalo y) {
    Intervalo resultado;

    if (y.intervaloMenor.d == 0 || y.intervaloMaior.d == 0) {
        resultado.intervaloMenor.d = -INFINITY;
        resultado.intervaloMaior.d = INFINITY;
        return resultado;
    }

    resultado.intervaloMenor.d = x.intervaloMenor.d / y.intervaloMaior.d;
    resultado.intervaloMaior.d = x.intervaloMaior.d / y.intervaloMenor.d;

    return resultado;
}


int calcularULPS(Double_t A, Double_t B)
{
    int ulpsDiff = abs(A.i - B.i);

    return ulpsDiff;
}


int main() {
    double X[5];  // numero real
    char O[4];    // operação
    Intervalo resultado;
    Intervalo intervaloX;
    Intervalo intervaloY;

    double erroAbsoluto;
    double erroRelativo;
    int ulps;

    scanf("%lf %c %lf %c %lf %c %lf %c %lf", &X[0], &O[0], &X[1], &O[1], &X[2],
          &O[2], &X[3], &O[3], &X[4]);

    resultado.intervaloMenor.d = nextafter(X[0], -HUGE_VAL);
    resultado.intervaloMaior.d = nextafter(X[0], +HUGE_VAL);

    fesetround(FE_DOWNWARD);

    for (int i = 1, j = 0; i < 5; i++, j++) {
        intervaloX.intervaloMenor.d = resultado.intervaloMenor.d;
        intervaloX.intervaloMaior.d = resultado.intervaloMaior.d;
        intervaloY.intervaloMenor.d = X[i] == 0 ? 0 : nextafter(X[i], -HUGE_VAL);
        intervaloY.intervaloMaior.d = X[i] == 0 ? 0 : nextafter(X[i], HUGE_VAL);

        switch (O[j]) {
            case '+':
                resultado = soma(intervaloX, intervaloY);
                break;
            case '-':
                resultado = subtracao(intervaloX, intervaloY);
                break;
            case '*':
                resultado = multiplicacao(intervaloX, intervaloY);
                break;
            case '/':
                resultado = divisao(intervaloX, intervaloY);
                break;
        }

        /* calculando erro absoluto, erro relativo e ulp */
        erroAbsoluto = resultado.intervaloMaior.d - resultado.intervaloMenor.d;
        erroRelativo =
            (resultado.intervaloMaior.d - resultado.intervaloMenor.d) /
            resultado.intervaloMenor.d;
        ulps = calcularULPS(resultado.intervaloMenor, resultado.intervaloMaior);

        /* imprimindo informações */
        printf("\n%d:\n", i);
        printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =", intervaloX.intervaloMenor.d,
               intervaloX.intervaloMaior.d, O[j], intervaloY.intervaloMenor.d,
               intervaloY.intervaloMaior.d);
        printf("[%1.8e,%1.8e]\n", resultado.intervaloMenor.d,
               resultado.intervaloMaior.d);

        printf("EA: %1.8e; ER: %1.8e; ULPs: %d\n", erroAbsoluto, erroRelativo,
               ulps);
    }

    return 0;
}