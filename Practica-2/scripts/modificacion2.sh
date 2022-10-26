#!/bin/bash

ganancia_unidad_vendida=(10 10 10)
perdida_por_novendida=(1 5 8)
numero_repes=(100 1000 5000 10000 100000)
tablas=(1 2 3)

for i in {0..2}
do
    for j in {0..2}
    do
        for k in {0..4}
        do
            bin/modificacion2.o ${ganancia_unidad_vendida[$j]} ${perdida_por_novendida[$j]} 200 ${numero_repes[$k]} ${tablas[$i]} >> data/modificacion2.txt
        done
    done
done