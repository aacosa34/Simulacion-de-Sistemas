#!/bin/bash

tlleg=(0.15 4.5 6.75 9 540 5400)
tserv=(0.1 3 4.5 6 360 3600)
a_atender=10000

echo "porcentaje_ocio,media_en_cola" > ../data/incremento_fijo.csv
echo "porcentaje_ocio,media_en_cola" > ../data/incremento_variable.csv

for i in {0..5}
do
    ../bin/incremento_fijo ${tlleg[i]} ${tserv[i]} $a_atender >> ../data/incremento_fijo.csv
    ../bin/incremento_variable ${tlleg[i]} ${tserv[i]} $a_atender >> ../data/incremento_variable.csv
done
