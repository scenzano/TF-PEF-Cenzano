#ifndef HUFFMANCOMPRESSOR_H
#define HUFFMANCOMPRESSOR_H

#include <iostream>
#include <cstdio>
#include <string>
#include "object.h"
#include "HuffmanTree.h"

class HuffmanCompressor : public Object
{
    HuffmanTree *ht;
    int cantSignos;

        public:

    HuffmanCompressor();
    void comprimir(string fileName);
    void descomprimir(string fileName);
    float desafio3 (const char fileName[]);
};

#endif // HUFFMANCOMPRESSOR_H
