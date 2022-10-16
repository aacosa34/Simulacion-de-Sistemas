#!/bin/bash

pago_lanzamiento=(10 100 1000)
pago_juego=(100 1000 10000)

for j in "${pago_lanzamiento[@]}"
do
    for k in "${pago_juego[@]}"
    do
        echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-${j}-${k}.csv
        for i in {1..100}
        do
            ../lanzamonedas-generico 10 $j $k >> ../../datos/lanzamientos-${j}-${k}.csv
        done
    done
done
