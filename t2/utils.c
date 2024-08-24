// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

/*  Retorna tempo em milisegundos desde EPOCH

    Forma de uso:

    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/
double timestamp(void) {
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
    return ((double)tp.tv_sec * 1.0e3 + (double)tp.tv_nsec * 1.0e-6);
}
