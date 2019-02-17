#!/bin/bash

for nombre in "Ada" "background" "c++"; 
do
	mkdir Corrida-$nombre
	g++ -ftest-coverage -fprofile-arcs -fprofile-dir=./Corrida-$nombre ../../HuffmanOriginal/*.cpp -fpermissive -o HuffmanCompressor
	cp ../../../ArchivosDePrueba/* ./
	./HuffmanCompressor comprimir "$nombre.jpg"
	./HuffmanCompressor descomprimir "$nombre.cmp"
	./HuffmanCompressor
	sleep 2
	mv ./*.gcno ./Corrida-$nombre
	gcov -o ./Corrida-$nombre ../../HuffmanOriginal/* >> RESULTADOS-$nombre.txt
	sleep 2
	mv ./*.gcov ./Corrida-$nombre
	
done

