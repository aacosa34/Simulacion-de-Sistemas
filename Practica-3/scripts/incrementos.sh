#!/bin/bash

tlleg=(0.15 4.5 6.75 9 540 5400 54000)
tserv=(0.1 3.0 4.5 6 360 3600 36000)
a_atender=10000

echo "porcentaje_ocio,media_en_cola" > data/incremento_fijo.csv
echo "porcentaje_ocio,media_en_cola" > data/incremento_variable.csv

for i in {0..6}
do
    bin/incremento_fijo $a_atender ${tlleg[i]} ${tserv[i]} >> data/incremento_fijo.csv
    bin/incremento_variable $a_atender ${tlleg[i]} ${tserv[i]} >> data/incremento_variable.csv
done
