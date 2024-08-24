// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include <fenv.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculoIntervalar.h"

// soma recebe como argumentos dois intervalos a serem somados
// retorna soma intervalar de x + y
Intervalo soma(Intervalo x, Intervalo y) {
    Intervalo resultado;

    resultado.intervaloMenor.d = x.intervaloMenor.d + y.intervaloMenor.d;
    resultado.intervaloMaior.d = x.intervaloMaior.d + y.intervaloMaior.d;
    resultado.intervaloMenor.d = nextafter(resultado.intervaloMenor.d, -HUGE_VAL);
    resultado.intervaloMaior.d = nextafter(resultado.intervaloMaior.d, +HUGE_VAL);

    return resultado;
}

// subtracao recebe como argumentos dois intervalos a serem subtraidos
// retorna subtracao intervalar de x - y
Intervalo subtracao(Intervalo x, Intervalo y) {
    Intervalo resultado;

    resultado.intervaloMenor.d = x.intervaloMenor.d - y.intervaloMaior.d;
    resultado.intervaloMaior.d = x.intervaloMaior.d - y.intervaloMenor.d;

    resultado.intervaloMenor.d = nextafter(resultado.intervaloMenor.d, -HUGE_VAL);
    resultado.intervaloMaior.d = nextafter(resultado.intervaloMaior.d, +HUGE_VAL);

    //imprimeIntervalo(x);
    //printf("-\n");
    //imprimeIntervalo(y);
    //printf("=\n");
    //imprimeIntervalo(resultado);

    return resultado;
}

// multiplicacao recebe como argumentos dois intervalos a serem multiplicados
// retorna multiplicacao intervalar de x * y
Intervalo multiplicacao(Intervalo x, Intervalo y) {
    Intervalo resultado;

    if ((x.intervaloMenor.d > 0) && (y.intervaloMenor.d > 0)) {
        resultado.intervaloMenor.d = x.intervaloMenor.d * y.intervaloMenor.d;
        resultado.intervaloMaior.d = x.intervaloMaior.d * y.intervaloMaior.d;
    }
    else
    if ((x.intervaloMenor.d < 0) && (x.intervaloMaior.d < 0) && (y.intervaloMenor.d < 0) && (y.intervaloMaior.d < 0)) {
        resultado.intervaloMenor.d = x.intervaloMaior.d * y.intervaloMaior.d;
        resultado.intervaloMaior.d = x.intervaloMenor.d * y.intervaloMenor.d;
    }
    else
    if ((x.intervaloMenor.d < 0) && (x.intervaloMaior.d < 0) && (y.intervaloMenor.d > 0) && (y.intervaloMaior.d > 0)) {
        resultado.intervaloMenor.d = x.intervaloMenor.d * y.intervaloMaior.d;
        resultado.intervaloMaior.d = x.intervaloMaior.d * y.intervaloMenor.d;
    }
    else
    if ((x.intervaloMenor.d > 0) && (x.intervaloMaior.d > 0) && (y.intervaloMenor.d < 0) && (y.intervaloMaior.d < 0)) {
        resultado.intervaloMenor.d = x.intervaloMaior.d * y.intervaloMenor.d;
        resultado.intervaloMaior.d = x.intervaloMenor.d * y.intervaloMaior.d;
    }
    else
    {
        if (x.intervaloMenor.d == 0 || y.intervaloMenor.d == 0)
            resultado.intervaloMenor.d = 0;
        if (x.intervaloMaior.d == 0 || y.intervaloMaior.d == 0)
            resultado.intervaloMaior.d = 0;
    }

    resultado.intervaloMenor.d = nextafter(resultado.intervaloMenor.d, -HUGE_VAL);
    resultado.intervaloMaior.d = nextafter(resultado.intervaloMaior.d, +HUGE_VAL);

    return resultado;
}

// divisao recebe como argumentos dois intervalos a serem divididos
// retorna divisao intervalar de x / y
Intervalo divisao(Intervalo x, Intervalo y) {
    Intervalo resultado;

    if ((y.intervaloMaior.parts.sign != y.intervaloMenor.parts.sign) || (y.intervaloMaior.d == 0) || (y.intervaloMenor.d == 0)) {
        resultado.intervaloMenor.d = -INFINITY;
        resultado.intervaloMaior.d = INFINITY;

        return resultado;
    }

    // Calcule a inversa dos intervalos de y
    Intervalo inversa_y;
    inversa_y.intervaloMenor.d = 1.0 / y.intervaloMaior.d;
    inversa_y.intervaloMaior.d = 1.0 / y.intervaloMenor.d;

    resultado = multiplicacao(x, inversa_y);

    return resultado;
}

// potenciacao recebe um intervalo e aplica a pontenciacao em p
// retorna x elevado a p
Intervalo potenciacao(Intervalo x, int p) {
    Intervalo resultado;

    if (p == 0) {
        resultado.intervaloMenor.d = 1.0;
        resultado.intervaloMaior.d = 1.0;
    }
    else
    if (p % 2 == 1 || (p % 2 == 0 && x.intervaloMenor.d >= 0))
    {
        resultado.intervaloMenor.d = pow(x.intervaloMenor.d, p);
        resultado.intervaloMaior.d = pow(x.intervaloMaior.d, p);
    }
    else
    if (p % 2 == 0 && x.intervaloMaior.d < 0)
    {
        resultado.intervaloMenor.d = pow(x.intervaloMaior.d, p);
        resultado.intervaloMaior.d = pow(x.intervaloMenor.d, p);
    }
    else
    if (p % 2 == 0 && x.intervaloMenor.d < 0 && x.intervaloMaior.d >= 0)
    {
        resultado.intervaloMenor.d = 0;
        resultado.intervaloMaior.d = fmax(pow(x.intervaloMenor.d, p), pow(x.intervaloMaior.d, p));
    }

    return resultado;
}

// recebe um double x e calcula o intervalo com nextafter a partir de x
Intervalo criaIntervalo(double x) {
    Intervalo resultado;

    fesetround(FE_DOWNWARD);
    resultado.intervaloMenor.d = x;

    fesetround(FE_UPWARD);
    resultado.intervaloMaior.d = x;

    return resultado;
}

// imprime o intervalo menor e o intervalo maior
void imprimeIntervalo(Intervalo x) {
    printf("[%1.8e,%1.8e]", x.intervaloMenor.d, x.intervaloMaior.d);
}