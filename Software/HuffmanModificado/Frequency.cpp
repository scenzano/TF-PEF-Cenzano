#include "Frequency.h"

Frequency::Frequency()
{
    indice = -1;
    frecuencia = 0;
}

Frequency::Frequency(int i, int f)
{
    indice = i;
    frecuencia = f;
}


Frequency::~Frequency()
{
}

int Frequency::compareTo(Object * x)
{
    Frequency *p = dynamic_cast < Frequency * > ( x );
    return this->frecuencia - p->frecuencia;
}

