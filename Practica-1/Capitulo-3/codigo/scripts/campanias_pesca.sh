#!/bin/bash

periodos=(91 182 365 730 1460)

for periodo in ${periodos[@]}
do
    ../simulacion-lago 30000 10000 125 0.65 $periodo > ../../datos/apartado-3/periodo_${periodo}.csv
done