#!/bin/bash

pago_lanzamiento=(10 100 1000)
pago_juego=(100 1000 10000)

echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-yz.csv


for i in {1..100}
do
    for j in "${pago_lanzamiento[@]}"
    do
        for k in "${pago_juego[@]}"
        do
            ../lanzamonedas-generico 500 $j $k >> ../../datos/lanzamientos-yz.csv
        done
    done
done
