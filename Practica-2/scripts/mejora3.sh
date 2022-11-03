#!/bin/bash

veces=(1000 10000 50000 100000 1000000 10000000)

printf "reps\ttiempo\n" > data/mejora3.csv

for repes in ${veces[@]}
do
    printf "%d" "${repes}" >> data/mejora3.csv
    bin/mejora3.o $repes >> data/mejora3.csv
done