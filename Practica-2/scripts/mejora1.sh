#!/bin/bash

veces=(1000 10000 50000 100000 1000000 10000000)

printf "reps\ttiempo\n" > data/mejora1.csv

for repes in ${veces[@]}
do
    printf "%d" "${repes}" >> data/mejora1.csv
    bin/mejora1.o $repes 1 >> data/mejora1.csv
done