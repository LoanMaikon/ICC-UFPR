#!/bin/bash

make

declare -A group_keywords
group_keywords["L2CACHE"]="miss ratio"
group_keywords["L3"]="L3 bandwidth"

groups=("FLOPS_DP" "ENERGY" "L2CACHE" "L3" "Tempo")
sizes=(64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000)

for group in "${groups[@]}"
do
    output_file1="${group}_mat_vet.dat"
    output_file2="${group}_mat_mat.dat"

    echo "TamanhoMatriz $group ANTES DEPOIS" > $output_file1
    echo "TamanhoMatriz $group ANTES DEPOIS" > $output_file2

    sizes=(64 100 128 200 256 512 600 900 1024 2000 2048 3000 4000)
    for size in "${sizes[@]}"
    do
        if [ "$group" == "ENERGY" ]; then
            energy_output=$(./perfctr 3 ENERGY ./matmult $size)
            energy1=$(echo "$energy_output" | grep "Energy" | awk 'NR==1{print $5}')
            energy2=$(echo "$energy_output" | grep "Energy" | awk 'NR==5{print $5}')
            energy1ANTES=$(echo "$energy_output" | grep "Energy" | awk 'NR==9{print $5}')
            energy2ANTES=$(echo "$energy_output" | grep "Energy" | awk 'NR==13{print $5}')
            echo "$size $energy1ANTES $energy1" >> $output_file1
            echo "$size $energy2ANTES $energy2" >> $output_file2
        elif [ "$group" == "FLOPS_DP" ]; then
            flops_output=$(./perfctr 3 FLOPS_DP ./matmult $size)
            dp_flops_mat_vet=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==1{print $5}')
            dp_flops_mat_mat=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==3{print $5}')
            dp_flops_mat_vet_antes=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==5{print $5}')
            dp_flops_mat_mat_antes=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==7{print $5}')

            avx_flops_mat_vet=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==2{print $6}')
            avx_flops_mat_mat=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==4{print $6}')
            avx_flops_mat_vet_antes=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==6{print $6}')
            avx_flops_mat_mat_antes=$(echo "$flops_output" | grep "DP MFLOP/s" | awk 'NR==8{print $6}')

            echo "$size $dp_flops_mat_vet_antes $dp_flops_mat_vet $avx_flops_mat_vet_antes $avx_flops_mat_vet" >> $output_file1
            echo "$size $dp_flops_mat_mat_antes $dp_flops_mat_mat $avx_flops_mat_mat_antes $avx_flops_mat_mat" >> $output_file2
        elif [ "$group" == "Tempo" ]; then
            tempo_output=$(./matmult $size)
            tempo_mat_vet=$(echo "$tempo_output" | awk 'NR==1{print $1}')
            tempo_mat_mat=$(echo "$tempo_output" | awk 'NR==2{print $1}')
            tempo_mat_vet_antes=$(echo "$tempo_output" | awk 'NR==3{print $1}')
            tempo_mat_mat_antes=$(echo "$tempo_output" | awk 'NR==4{print $1}')
            echo "$size $tempo_mat_vet_antes $tempo_mat_vet" >> $output_file1
            echo "$size $tempo_mat_mat_antes $tempo_mat_mat" >> $output_file2
        else
            keyword="${group_keywords[$group]}"
            output=$(./perfctr 3 $group ./matmult $size)
            value1=$(echo "$output" | grep "$keyword" | awk 'NR==1{print $6}')
            value2=$(echo "$output" | grep "$keyword" | awk 'NR==2{print $6}')
            value1ANTES=$(echo "$output" | grep "$keyword" | awk 'NR==3{print $6}')
            value2ANTES=$(echo "$output" | grep "$keyword" | awk 'NR==4{print $6}')
            echo "$size $value1ANTES $value1" >> $output_file1
            echo "$size $value2ANTES $value2" >> $output_file2
        fi
    done
done

rm main
