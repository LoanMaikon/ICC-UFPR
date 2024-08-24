#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"
#include <likwid.h>

#define DIFF 0.0

#define NRAND    ((double) rand() / RAND_MAX)  // drand48() 
#define SRAND(a) srand(a) // srand48(a)

// Integral Monte Carlo da função Styblinski-Tang de 2 variáveis
double styblinskiTang(double a, double b, int namostras, int ndimensoes)
{
  double resultado;
  double soma = 0.0;
  
  printf("Metodo de Monte Carlo (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), variaveis = %d\n", a, b, namostras, ndimensoes);
  
  double t_inicial = timestamp();
  
  double h = b - a;
  for (int i = 0; i < namostras; i++)
  {
    for (int j = 0; j < ndimensoes; j++)
    {
      double x = a + NRAND * h;
      double x2 = x * x;
      soma += (x2 * x2 - 16 * x2 + 5 * x);
    }
  }
  soma /= 2;
  resultado = (soma / namostras) * (pow(h, ndimensoes));
  
  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}

double retangulos_xy(double a, double b, int npontos) {

  double h = (b - a) / npontos;
  double resultado;
  double soma = 0;
  
  printf("Metodo dos Retangulos (x, y).\n");
  printf("a = (%f), b = (%f), n = (%d), h = (%lg)\n", a, b, npontos, h);
  
  double t_inicial = timestamp();
  
  for (int i = 0; i < npontos; i++)
  {
    double x = a + i * h;
    double x2 = x * x;
    
    soma += (x2 * x2 - 16 * x2 + 5 * x);
  }
  resultado = soma * h * h * npontos;


  double t_final = timestamp();
  printf("Tempo decorrido: %f seg.\n", t_final - t_inicial);
  
  return resultado;
}

int main(int argc, char **argv) {

  if (argc < 5) {
    printf("Utilização: %s inicial final n_amostras n_variaveis\n", argv[0]);
    return 1;
  }

  // INICIAR VALOR DA SEMENTE
  SRAND(20232);
    
  // CHAMAR FUNÇÕES DE INTEGRAÇÃO E EXIBIR RESULTADOS
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int n_amostras = atoi(argv[3]);
  int n_variaveis = atoi(argv[4]);

  double resultado1 = styblinskiTang(a, b, n_amostras, n_variaveis);
  double resultado2 = retangulos_xy(a, b, n_amostras);

  printf("Resultado 1: %f\n", resultado1);
  printf("Resultado 2: %f\n", resultado2);
  printf("Diferença: %f\n", fabs(resultado1 - resultado2));
  
  return 0;
}
