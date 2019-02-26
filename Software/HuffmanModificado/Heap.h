#ifndef HEAP_H
#define HEAP_H

#include <cstdlib>
#include <cstring>
#include "object.h"
#include "comparable.h"

/*
 * Implementa el concepto de Heap o Monticulo Binario.  El Heap puede ser ascendente, en cuyo caso
 * el Heap esta preparado para obtener en forma rapida el menor elemento del conjunto, o puede ser
 * descendente, en cuyo caso esta preparado para obtener en forma rapida el mayor. Se puede crear un
 * Heap ascendente enviando al constructor de la clase el valor true como segundo parametro, o crear
 * un Heap descendente enviando un false a ese mismo constructor:
 *
 *   Heap *ah = new Heap(10, true);  // un heap ascendente con capacidad inicial = 10
 *   Heap *dh = new Heap(false);     // un heap descendente con capacidad inicial = 100 (por default)
 *
 * La capacidad del Heap ira variando a medida que se requiera. Si la capacidad no alcanza para una
 * nueva insercion, entonces la capacidad sera duplicada automaticamente. Si al realizar extracciones
 * se detecta que el espacio ocupado es inferior al 90% de la mitad de la capacidad actual, entonces
 * la capacidad sera automaticamente disminuida a la mitad.
 *
 * @author Ing. Frittelli - Catedra: AEDII.
 * @version Octubre de 2012.
 */

class Heap : public Object
{
    Comparable **heap;     // el arreglo para representar al arbol.
    int capacity;          // la longitud del arreglo.
    int initial_capacity;  // la capacidad inicial del arreglo.
    int count;             // la cantidad de elementos que tiene el Heap.
    bool ascendent;        // true: ascendente  -  false: descendente.

    void adjustCapacity(int nc);
    void init(int n, bool t);
    bool optimal_left(int sl, int sr);
    bool valid_change(int s, int f);
    bool isHomogeneus(Comparable *x);

       public:

    Heap();
    Heap(int n);
    Heap(bool t);
    Heap(int n, bool t);
    ~Heap();

    void add(Comparable *data);
    void clear();
    Comparable *get();
    bool isAscendent();
    bool isEmpty();
    Comparable *remove();
    int size();
};

#endif // HEAP_H
