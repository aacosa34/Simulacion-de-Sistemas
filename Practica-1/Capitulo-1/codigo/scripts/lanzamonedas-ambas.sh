#!/bin/bash

echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-ambas.csv

probabilidad=(0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1)
diff=(3 4 5 6 7 8 9 10)

for i in {1..10}
do
    for j in "${probabilidad[@]}"
    do
        for k in "${diff[@]}"
        do
            ../lanzamonedas-generico 500 10 100 $j $k >> ../../datos/lanzamientos-ambas.csv
        done
    done
done