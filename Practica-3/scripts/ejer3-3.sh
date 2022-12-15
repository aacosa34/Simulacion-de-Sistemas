#!/bin/bash

echo "espera_carga,dt_espera_carga,espera_descarga,dt_espera_descarga,procesados,dt_procesados,estancia,dt_estancia,porcent_ocio,dt_porcent_ocio" > data/ejer3/3-3/ejer3-3-1.csv
echo "espera_carga,dt_espera_carga,espera_descarga,dt_espera_descarga,procesados,dt_procesados,estancia,dt_estancia,porcent_ocio,dt_porcent_ocio" > data/ejer3/3-3/ejer3-3-2.csv
echo "espera_carga,dt_espera_carga,espera_descarga,dt_espera_descarga,procesados,dt_procesados,estancia,dt_estancia,porcent_ocio,dt_porcent_ocio" > data/ejer3/3-3/ejer3-3-3.csv
echo "espera_carga,dt_espera_carga,espera_descarga,dt_espera_descarga,procesados,dt_procesados,estancia,dt_estancia,porcent_ocio,dt_porcent_ocio" > data/ejer3/3-3/ejer3-3-4.csv
for i in {1..100}
do
    bin/ejer3-3-1 1000 >> data/ejer3/3-3/ejer3-3-1.csv
    bin/ejer3-3-2 1000 >> data/ejer3/3-3/ejer3-3-2.csv
    bin/ejer3-3-3 1000 >> data/ejer3/3-3/ejer3-3-3.csv
    bin/ejer3-3-4 1000 >> data/ejer3/3-3/ejer3-3-4.csv
done