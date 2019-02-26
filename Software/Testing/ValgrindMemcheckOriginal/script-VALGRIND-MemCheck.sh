#!/bin/bash

for nombre in "Ada" "background" "c++" "deadpool"; 
do
	mkdir Corrida-$nombre-compresion
	mkdir Corrida-$nombre-descompresion
	g++ -g ../../HuffmanOriginal/*.cpp -fpermissive -o HuffmanCompressor
	cp ../../../ArchivosDePrueba/* ./
	sleep 2
	valgrind --leak-check=full --log-file=./Resultados$nombre-compresion -v ./HuffmanCompressor comprimir "$nombre.jpg"
	sleep 2
	valgrind --leak-check=full --log-file=./Resultados$nombre-descomprimir -v ./HuffmanCompressor descomprimir "$nombre.cmp"
	sleep 2
done

