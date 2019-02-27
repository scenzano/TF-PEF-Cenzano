#!/bin/bash

for nombre in "Ada" "background" "c++" "deadpool"; 
do
	mkdir Corrida-$nombre-compresion
	mkdir Corrida-$nombre-descompresion
	g++ -g ../../HuffmanModificado/*.cpp -fpermissive -o HuffmanCompressor
	cp ../../../ArchivosDePrueba/* ./
	sleep 2
	valgrind -v --tool=cachegrind --cache-sim=yes ./HuffmanCompressor comprimir "$nombre.jpg" 2>&1 | tee ./Resultados-$nombre-compresion.txt
	mv cachegrind.* ./Corrida-$nombre-compresion
	sleep 2
	valgrind -v --tool=cachegrind --cache-sim=yes ./HuffmanCompressor descomprimir "$nombre.cmp" 2>&1 | tee ./Resultados-$nombre-descompresion.txt
	mv cachegrind.* ./Corrida-$nombre-descompresion
	sleep 2
done

