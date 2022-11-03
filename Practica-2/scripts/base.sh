#!/bin/bash

veces=(1000 10000 50000 100000 1000000 10000000)

printf "reps\ttiempo\n" > data/base.csv

for repes in ${veces[@]}
do
    printf "%d" "${repes}" >> data/base.csv
    bin/generador_base.o $repes 3 >> data/base.csv
done