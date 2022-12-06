#!/bin/bash

simulaciones=(1 5 10 50 100 500 1000 10000)

for i in ${simulaciones[@]}
do
    echo "espera_carga,dt_espera_carga,espera_descarga,dt_espera_descarga,procesados,dt_procesados,estancia,dt_estancia,porcent_ocio,dt_porcent_ocio" > data/ejer3/ejer3-1-A-$i.csv
    echo "espera_carga,dt_espera_carga,espera_descarga,dt_espera_descarga,procesados,dt_procesados,estancia,dt_estancia,porcent_ocio,dt_porcent_ocio" > data/ejer3/ejer3-1-B-$i.csv
    for j in {0..100}
    do
        bin/ejer3-1-A $i >> data/ejer3/ejer3-1-A-$i.csv
        bin/ejer3-1-B $i >> data/ejer3/ejer3-1-B-$i.csv
    done
done