#!/bin/bash

num_simulaciones=(1 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000)

echo "num_simulaciones,media_tiempo_ocio" > data/ejer2/mm1t_simulaciones.csv
for i in ${num_simulaciones[@]}
do
    bin/mm1t $i >> data/ejer2/mm1t_simulaciones.csv
done