#ifndef _HUFFMANNODE_H
#define	_HUFFMANNODE_H

#include <iostream>
#include "object.h"
#include "comparable.h"

class HuffmanNode  : public Comparable
{
	int  frecuencia;	
        int  padre;		// para la fase de compresion
	bool esIzquierdo;	
	int izq, der;		// para la fase de descompresion

            public:
    
        HuffmanNode();
	HuffmanNode(int f, int p, bool e, int i, int d);
        virtual ~HuffmanNode();
	
	int  getFrecuencia() { return frecuencia; }
	void setFrecuencia(int x) { frecuencia = x; }

	int  getPadre() { return padre; }
	void setPadre(int x) { padre = x; }

	bool isLeft() { return esIzquierdo; }
	void setLeft(bool x) { esIzquierdo = x; }

	int  getIzquierdo() { return izq; }
	void setIzquierdo(int x) { izq = x; }

	int  getDerecho() { return der; }
	void setDerecho(int x) { der = x; }

	int  compareTo(Object * x); 
};

#endif /* _HUFFMANNODE_H */
