#!/bin/bash

tlleg=(0.15 4.5 6.75 9.0 540.0 5400.0 54000.0)
tserv=(0.1 3.0 4.5 6.0 360.0 3600.0 36000.0)
a_atender=10000

for i in {4..6}
do
    echo "porcentaje_ocio,media_en_cola,tiempo_ejecucion" > data/incremento_fijo_${tlleg[i]}_${tserv[i]}.csv
    echo "porcentaje_ocio,media_en_cola,tiempo_ejecucion" > data/incremento_variable_${tlleg[i]}_${tserv[i]}.csv
    bin/incremento_fijo $a_atender ${tlleg[i]} ${tserv[i]} >> data/incremento_fijo_${tlleg[i]}_${tserv[i]}.csv
    bin/incremento_variable $a_atender ${tlleg[i]} ${tserv[i]} >> data/incremento_variable_${tlleg[i]}_${tserv[i]}.csv
done
