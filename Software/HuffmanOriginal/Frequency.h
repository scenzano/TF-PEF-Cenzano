#include "object.h"
#include "comparable.h"

#ifndef FREQUENCY_H
#define	FREQUENCY_H

class Frequency : public Comparable
{
        int indice;
        int frecuencia;

                public:
                    
        Frequency();
        Frequency(int i, int f);
        virtual ~Frequency();

        int getIndice() {return indice;}
        void setIndice(int i) {indice = i;}

        int  getFrecuencia() { return frecuencia; }
        void setFrecuencia(int x) { frecuencia = x; }

        int compareTo(Object *x);
};

#endif	/* FREQUENCY_H */

