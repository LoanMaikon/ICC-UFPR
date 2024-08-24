#!/bin/bash

make

declare -A group_keywords
group_keywords["L2CACHE"]="miss ratio"
group_keywords["L3"]="L3 bandwidth"

groups="FLOPS_DP L2CACHE L3 Tempo"
sizes=(64 128 200 256 512 600 800 1024 2000 3000 4096 6000 7000 10000 50000 100000 1000000 10000000)

for group in $groups
do
    output_file1="${group}_geracao_SL.dat"
    output_file2="${group}_solucao_SL.dat"
    output_file3="${group}_calculo_residuo.dat"

    echo "NumeroPontos $group" > $output_file1
    echo "NumeroPontos $group" > $output_file2
    echo "NumeroPontos $group" > $output_file3
done

for size in "${sizes[@]}"
do
    gera_entrada_output=$(./gera_entrada $size)

    for group in $groups
    do
        output_file1="${group}_geracao_SL.dat"
        output_file2="${group}_solucao_SL.dat"
        output_file3="${group}_calculo_residuo.dat"

        if [ "$group" == "FLOPS_DP" ]; then
            flops_output=$(echo $gera_entrada_output | ./perfctr 3 FLOPS_DP ./ajustePol)
            dp_flops_geracao_sistema=$(echo "$flops_output" | grep "MFLOP/s" | awk 'NR==1{print $5}')
            dp_flops_solucao_sistema=$(echo "$flops_output" | grep "MFLOP/s" | awk 'NR==3{print $5}')
            dp_flops_calculo_residuo=$(echo "$flops_output" | grep "MFLOP/s" | awk 'NR==5{print $5}')

            avx_flops_geracao_sistema=$(echo "$flops_output" | grep "MFLOP/s" | awk 'NR==2{print $6}')
            avx_flops_solucao_sistema=$(echo "$flops_output" | grep "MFLOP/s" | awk 'NR==4{print $6}')
            avx_flops_calculo_residuo=$(echo "$flops_output" | grep "MFLOP/s" | awk 'NR==6{print $6}')

            echo "$size $dp_flops_geracao_sistema $avx_flops_geracao_sistema" >> $output_file1
            echo "$size $dp_flops_solucao_sistema $avx_flops_solucao_sistema" >> $output_file2
            echo "$size $dp_flops_calculo_residuo $avx_flops_calculo_residuo" >> $output_file3
        elif [ "$group" == "Tempo" ]; then
            tempo_output=$(echo $gera_entrada_output | ./perfctr 3 FLOPS_DP ./ajustePol)

            # get first line of output
            tempo_geracao_sistema=$(echo "$tempo_output" | awk 'NR==8{print $1}')
            tempo_solucao_sistema=$(echo "$tempo_output" | awk 'NR==9{print $1}')
            tempo_calculo_residuo=$(echo "$tempo_output" | awk 'NR==10{print $1}')
     
            echo "$size $tempo_geracao_sistema" >> $output_file1
            echo "$size $tempo_solucao_sistema" >> $output_file2
            echo "$size $tempo_calculo_residuo" >> $output_file3
        else
            keyword="${group_keywords[$group]}"
            output=$(echo $gera_entrada_output | ./perfctr 3 $group ./ajustePol)
            value1=$(echo "$output" | grep "$keyword" | awk 'NR==1{print $6}')
            value2=$(echo "$output" | grep "$keyword" | awk 'NR==2{print $6}') 
            value3=$(echo "$output" | grep "$keyword" | awk 'NR==3{print $6}')

            echo "$size $value1" >> $output_file1
            echo "$size $value2" >> $output_file2
            echo "$size $value3" >> $output_file3
        fi
    done
done
