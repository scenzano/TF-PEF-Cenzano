#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include <iostream>
#include "object.h"
#include "HuffmanCode.h"
#include "HuffmanNode.h"
#include "Frequency.h"
#include "Heap.h"

#define MAXSYMBS 256
#define MAXNODES 2 * MAXSYMBS - 1

class HuffmanTree : public Object
{
        private:
            
    HuffmanCode *codigos[MAXSYMBS];
    HuffmanNode arbol[MAXNODES];
    unsigned char signos[MAXSYMBS];
    int tam;

    int buscar(unsigned char x);

        public:
            
    HuffmanTree(int n);
    virtual ~HuffmanTree();

    int length() { return tam; }
    void setNodo(unsigned char x, int f, int i);
    void setNodo(HuffmanNode hn, int i);
    unsigned char getSigno(int i) { return signos[i]; }
    void setSigno(unsigned char x, int i) { signos[i] = x; }
    int  getFrecuencia(int i) { return arbol[i].getFrecuencia(); }
    void setFrecuencia(int i, int f) { arbol[i].setFrecuencia(f); }
    HuffmanCode *getCodigo(int i) { return codigos[i]; }
    void setCodigo(HuffmanCode *c, int i) { codigos[i] = c;}
    HuffmanCode *getCodigo(unsigned char x);
    void setCodigo(HuffmanCode *c, unsigned char x);
    HuffmanNode *getArbol() { return arbol; }
    void encode();
    void makeTree();
    void makeCodes();
};

#endif // HUFFMANTREE_H
