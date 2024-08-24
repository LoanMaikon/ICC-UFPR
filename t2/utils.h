// Gustavo F. Jakobi   GRR20221253
// Luan Marko Kujavski GRR20221236

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*  Retorna tempo em milisegundos desde EPOCH

    Forma de uso:

    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/
double timestamp(void);

#endif // __UTILS_H__

