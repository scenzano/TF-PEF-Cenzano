#!/bin/bash

for nombre in "Ada" "background" "c++" "deadpool"; 
do
	mkdir Corrida-$nombre-compresion
	mkdir Corrida-$nombre-descompresion
	g++ -pg ../../HuffmanModificado/*.cpp -fpermissive -o HuffmanCompressor
	cp ../../../ArchivosDePrueba/* ./
	sleep 2
	./HuffmanCompressor comprimir "$nombre.jpg"
	gprof ./HuffmanCompressor > RESULTADOS-$nombre-compresion.txt
	mv gmon.out ./Corrida-$nombre-compresion/gmon_$nombre.out
	sleep 2
	./HuffmanCompressor descomprimir "$nombre.cmp"
	gprof ./HuffmanCompressor > RESULTADOS-$nombre-descompresion.txt
	mv gmon.out ./Corrida-$nombre-descompresion/gmon_$nombre.out
	sleep 2
done

