#!/bin/bash

echo "Veces,s-S,M-CostoTotal,M-CostoPedido,M-CostoMantenimiento,M-CostoDeficit" > ../../datos/simulacion-politica3.csv
spequena=(0 0 0 0 20 20 20 20 40 40 40 60 60)
sgrande=(40 60 80 100 40 60 80 100 60 80 100 80 100)
nsimulaciones=(1 5 10 50 100 500)

for i in {0..12}; do
    for k in ${nsimulaciones[@]}; do
        ../inventario3 $k ${spequena[$i]} ${sgrande[$i]} >> ../../datos/simulacion-politica3.csv
    done
done