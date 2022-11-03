#!/bin/bash

ganancia_unidad_vendida=(10 10 10 15)
perdida_por_novendida=(1 5 8 10)
numero_repes=(100 1000 5000 10000 100000)
tablas=(1 2 3)



for i in {0..2}
do
    echo "x;y;veces;Best_s;Ganancia_esperada;tiempo" > data/montecarlo_datos_${tablas[$i]}.csv 

    for j in {0..3}
    do
        for k in {0..4}
        do
            bin/montecarlo.o ${ganancia_unidad_vendida[$j]} ${perdida_por_novendida[$j]} ${numero_repes[$k]} ${tablas[$i]} >> data/montecarlo_datos_${tablas[$i]}.csv
        done
    done
done