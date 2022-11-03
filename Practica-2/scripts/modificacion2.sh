#!/bin/bash

ganancia_unidad_vendida=(10 10 25 25)
perdida_por_novendida=(5 10 5 10)
numero_repes=(10000 100000)
tablas=(1 2 3)

for i in {0..2}
do
    echo "x;y;z;veces;Best_s;Ganancia_esperada;tiempo" > data/modificacion2_${tablas[$i]}.csv 
    for j in {0..3}
    do
        for k in {0..1}
        do
            bin/modificacion2.o ${ganancia_unidad_vendida[$j]} ${perdida_por_novendida[$j]} 200 ${numero_repes[$k]} ${tablas[$i]} >> data/modificacion2_${tablas[$i]}.csv 
        done
    done
done