#include "HuffmanNode.h"

HuffmanNode::HuffmanNode()
{
    frecuencia = 0;
    padre = -1;
    esIzquierdo = false;
    izq = der = -1;
}

HuffmanNode::HuffmanNode(int f, int p, bool e, int i, int d)
{
    frecuencia = f;
    padre = p;
    esIzquierdo = e;
    izq = i;
    der = d;
}

HuffmanNode::~HuffmanNode()
{
}

int HuffmanNode::compareTo(Object * x)
{
    HuffmanNode *p = dynamic_cast < HuffmanNode * > ( x );
    return this->frecuencia  - p->frecuencia;
}


