#!/bin/bash

pequenyos=10000
grandes=(0 100 125 200 250 500)
dias=$((365*10))

for i in {0..5}
do
    ../simulacion-lago $dias $pequenyos ${grandes[$i]} > ../../datos/apartado-1/simulacion_${pequenyos}_${grandes[$i]}.csv
done