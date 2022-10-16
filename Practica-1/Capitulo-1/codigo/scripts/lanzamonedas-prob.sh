#!/bin/bash

echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-prob.csv

for i in {25..95}
do
    x=`echo "scale=2; $i/100" | bc`
    ../lanzamonedas-generico 500 10 100 $x 3 >> ../../datos/lanzamientos-prob.csv
done