#ifndef FRECUENCIA_H
#define FRECUENCIA_H
#include "Object.h"
#include "Comparable.h"


class Frecuencia : public Comparable
{

private:
        int indice;
        int frecuencia;

public:
        Frecuencia();
        Frecuencia(int i, int f);
        virtual ~Frecuencia();

        int getIndice() {return indice;}
        void setIndice(int i) {indice = i;}

        int  getFrecuencia() { return frecuencia; }
        void setFrecuencia(int x) { frecuencia = x; }

        int compareTo(Object *x);
};

#endif // FRECUENCIA_H
