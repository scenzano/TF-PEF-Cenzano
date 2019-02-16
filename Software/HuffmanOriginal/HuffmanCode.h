#ifndef _HUFFMANCODE_H
#define	_HUFFMANCODE_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "object.h"
using namespace std;

#define MAXBITS 175

class HuffmanCode : public Object 
{             
        int * bits;	// aca guardamos los bits, de atras hacia adelante
        int startPos;   // indica donde comienza la cadena de bits

             public:
                 
        HuffmanCode() { startPos = MAXBITS; bits = new int[MAXBITS]; }
	HuffmanCode(HuffmanCode *c);
        virtual ~HuffmanCode();
        int getStartPos() { return startPos; }
        void setBit( int bit );
        int  * getCodigo() { return bits; }
        string toString();
};

#endif /* _HUFFMANCODE_H */
