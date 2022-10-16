#!/bin/bash

echo "Veces,Probabilidad,Diferencia,Pago_Lanzamiento,Pago_Finalizar,Esperado" > ../../datos/lanzamientos-cantidad.csv

for i in {1..100}
do
	../lanzamonedas-generico 10 10 100 >> ../../datos/lanzamientos-cantidad.csv
	../lanzamonedas-generico 500 10 100 >> ../../datos/lanzamientos-cantidad.csv
	../lanzamonedas-generico 10000 10 100 >> ../../datos/lanzamientos-cantidad.csv
done

