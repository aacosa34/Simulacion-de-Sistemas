#!/bin/bash

echo "Veces,M-CostoTotal,M-CostoPedido,M-CostoMantenimiento,M-CostoDeficit" > ../../datos/simulacion-politica2.csv
nsimulaciones=(1 5 10 50 100 500)

for i in {0..12}; do
    for k in ${nsimulaciones[@]}; do
        ../inventario2 $k >> ../../datos/simulacion-politica2.csv
    done
done 