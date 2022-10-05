#!/bin/bash

echo "Veces,M-CostoTotal,M-CostoPedido,M-CostoMantenimiento,M-CostoDeficit" > ../../datos/simulacion-politica1.csv
spequena=(0 0 0 0 20 20 20 20 40 40 40 60 60)
sgrande=(40 60 80 100 40 60 80 100 60 80 80 100)
nsimulaciones=(1 5 10 50 100 500)

for i in ${spequena[@]}; do
    for j in ${sgrande[@]}; do
        for k in ${nsimulaciones[@]}; do
            ../inventario $k $i $j >> ../../datos/simulacion-politica1.csv
        done
    done
done
