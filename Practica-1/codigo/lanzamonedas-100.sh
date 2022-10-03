#!/bin/bash

echo "" > ../datos/lanzamientos-10.csv
echo "" > ../datos/lanzamientos-500.csv
echo "" > ../datos/lanzamientos-10000.csv

for i in {1..100}
do
	./lanzamonedas-generico 10 10 100 >> ../datos/lanzamientos-10.csv
	./lanzamonedas-generico 500 10 100 >> ../datos/lanzamientos-500.csv
	./lanzamonedas-generico 10000 10 100 >> ../datos/lanzamientos-10000.csv
	sleep 1
done

