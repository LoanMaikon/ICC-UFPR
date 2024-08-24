set terminal png
set output "FLOPS_DP_mat_vet.png"
set title "Desempenho FLOPS_DP"
set xlabel "Tamanho da Matriz"
set ylabel "MFLOP/s"
plot "FLOPS_DP_mat_vet.dat" using 1:2 with linespoints title 'Não Otimizado', "FLOPS_DP_mat_vet.dat" using 1:3 with linespoints title "Otimizado", \
"FLOPS_DP_mat_vet.dat" using 1:4 with linespoints title "Não Otimizado AVX", "FLOPS_DP_mat_vet.dat" using 1:5 with linespoints title "Otimizado AVX"