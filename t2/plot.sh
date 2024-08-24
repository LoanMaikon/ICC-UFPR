#!/bin/bash

# Set the path for the output folder
output_folder="resultados_finais"

# Create the output folder if it doesn't exist
mkdir -p "plots"

for output_file in "${output_folder}"/FLOPS_DP*; do  # Extract the file name without the path
  file_name=$(basename "$output_file")

  # Set the plot file path
  plot_file="plots/${file_name%.dat}.png"

  # Use gnuplot to create a log-scaled plot
  echo "set terminal pngcairo enhanced font 'arial,10' size 800,600" > plot_script.gnu
  echo "set output '$plot_file'" >> plot_script.gnu
  echo "set logscale x" >> plot_script.gnu
  echo "set xlabel 'Numero de Pontos K'" >> plot_script.gnu
  echo "set ylabel 'FLOPS_DP / AVX_FLOPS'" >> plot_script.gnu
  echo "set title 'Desempenho de operações aritméticas'" >> plot_script.gnu
  echo "plot '$output_file' using 1:2 with linespoints title 'FLOPS_DP (Original)', \
       '' using 1:4 with linespoints title 'FLOPS_DP (Otimizado)', \
       '' using 1:3 with linespoints title 'AVX_FLOPS (Original)', \
       '' using 1:5 with linespoints title 'AVX_FLOPS (Otimizado)'" >> plot_script.gnu

  # Use gnuplot with the temporary script
  gnuplot plot_script.gnu


  # Print a message indicating success
  echo "Plot created successfully. Output file: $plot_file"
done


for output_file in "${output_folder}"/L3*; do  # Extract the file name without the path
  file_name=$(basename "$output_file")

  # Set the plot file path
  plot_file="plots/${file_name%.dat}.png"

  # Use gnuplot to create a log-scaled plot
  echo "set terminal pngcairo enhanced font 'arial,10' size 800,600" > plot_script.gnu
  echo "set output '$plot_file'" >> plot_script.gnu
  echo "set logscale x" >> plot_script.gnu
  echo "set xlabel 'Numero de Pontos K'" >> plot_script.gnu
  echo "set ylabel 'Memory bandwidth [MBytes/s]'" >> plot_script.gnu
  echo "set title 'Memory bandwidth [MBytes/s]'" >> plot_script.gnu
  echo "plot '$output_file' using 1:2 with linespoints title 'L3 (Original)', \
       '' using 1:3 with linespoints title 'L3 (Otimizado)'" >> plot_script.gnu

  # Use gnuplot with the temporary script
  gnuplot plot_script.gnu


  # Print a message indicating success
  echo "Plot created successfully. Output file: $plot_file"
done

for output_file in "${output_folder}"/L2CACHE*; do  # Extract the file name without the path
  file_name=$(basename "$output_file")

  # Set the plot file path
  plot_file="plots/${file_name%.dat}.png"

  # Use gnuplot to create a log-scaled plot
  echo "set terminal pngcairo enhanced font 'arial,10' size 800,600" > plot_script.gnu
  echo "set output '$plot_file'" >> plot_script.gnu
  echo "set logscale x" >> plot_script.gnu
  echo "set xlabel 'Numero de Pontos K'" >> plot_script.gnu
  echo "set ylabel 'data cache miss RATIO'" >> plot_script.gnu
  echo "set title 'data cache miss RATIO'" >> plot_script.gnu
  echo "plot '$output_file' using 1:2 with linespoints title 'data cache miss RATIO (Original)', \
       '' using 1:3 with linespoints title 'data cache miss RATIO (Otimizado)'" >> plot_script.gnu

  # Use gnuplot with the temporary script
  gnuplot plot_script.gnu


  # Print a message indicating success
  echo "Plot created successfully. Output file: $plot_file"
done


for output_file in "${output_folder}"/Tempo*; do  # Extract the file name without the path
  file_name=$(basename "$output_file")

  # Set the plot file path
  plot_file="plots/${file_name%.dat}.png"

  # Use gnuplot to create a log-scaled plot
  echo "set terminal pngcairo enhanced font 'arial,10' size 800,600" > plot_script.gnu
  echo "set output '$plot_file'" >> plot_script.gnu
  echo "set logscale x" >> plot_script.gnu
  echo "set logscale y" >> plot_script.gnu
  echo "set xlabel 'Numero de Pontos K'" >> plot_script.gnu
  echo "set ylabel 'Tempo em milissegundos'" >> plot_script.gnu
  echo "set title 'Desempenho de tempo'" >> plot_script.gnu
  echo "plot '$output_file' using 1:2 with linespoints title 'Tempo em milissegundos (Original)', \
       '' using 1:3 with linespoints title 'Tempo em milissegundos (Otimizado)'" >> plot_script.gnu

  # Use gnuplot with the temporary script
  gnuplot plot_script.gnu


  # Print a message indicating success
  echo "Plot created successfully. Output file: $plot_file"
done