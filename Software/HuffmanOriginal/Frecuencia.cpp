#include "Frecuencia.h"

Frecuencia::Frecuencia()
{
    indice = -1;
    frecuencia = 0;
}

Frecuencia::Frecuencia(int i, int f)
{
    indice = i;
    frecuencia = f;
}


Frecuencia::~Frecuencia()
{
}

int Frecuencia::compareTo(Object * x)
{
    Frecuencia *p = dynamic_cast < Frecuencia * > ( x );
    return this->frecuencia  - p->frecuencia;
}

