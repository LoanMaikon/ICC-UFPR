set terminal pngcairo enhanced font 'arial,10' size 800,600
set output 'plots/Tempo_solucao_SL.png'
set logscale x
set logscale y
set xlabel 'Numero de Pontos K'
set ylabel 'Tempo em milissegundos'
set title 'Desempenho de tempo'
plot 'resultados_finais/Tempo_solucao_SL.dat' using 1:2 with linespoints title 'Tempo em milissegundos (Original)',        '' using 1:3 with linespoints title 'Tempo em milissegundos (Otimizado)'
