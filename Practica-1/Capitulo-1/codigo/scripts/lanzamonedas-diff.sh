#!/bin/bash

echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-diff.csv

for i in {1..100}
do
    diff=1

    while (( $diff < 11 ))
    do
        ../lanzamonedas-generico 500 10 100 0.5 $diff >> ../../datos/lanzamientos-diff.csv
        let diff=$diff+1
    done
done