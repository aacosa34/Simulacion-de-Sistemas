#!/bin/bash

pago_lanzamiento=(10 100 1000)
pago_juego=(100 1000 10000)

echo "" > ../datos/lanzamientos-yz.csv


for i in {1..100}
do
    for j in 
    ./lanzamonedas-generico 500  100 >> ../datos/lanzamientos-yz.csv
    sleep 1
done
done