#!/bin/bash

echo "" > ../../datos/simulacion1.csv

for anyos in {1..5}
do
    for pequenyos in {10000..5000000..50000}
    do
        for grandes in {200..36000..10000}
        do
            dias=$((365*$anyos))
            ../simulacion-lago $dias $pequenyos $grandes >> ../../datos/simulacion1.csv
        done
    done
done