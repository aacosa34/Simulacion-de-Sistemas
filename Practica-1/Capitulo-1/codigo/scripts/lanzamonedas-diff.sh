#!/bin/bash

echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-diff.csv

diff=1

while (( $diff < 11 ))
do
    for i in {1..100}
    do
        ../lanzamonedas-generico 500 10 100 0.5 $diff >> ../../datos/lanzamientos-diff.csv
    done
    
    let diff=$diff+1
done