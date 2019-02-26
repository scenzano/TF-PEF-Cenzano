#include "Heap.h"

/*
 * Crea un Heap vacio, orientado a la obtencion rapida del menor de n
 * elementos (un heap ascendente: el menor en la raiz).
 */
Heap::Heap()
{
    init(100, true);
}

/*
 * Crea un Heap vacio, con capacidad inicial para n componentes, orientado a
 * la obtencion rapida del menor de esos elementos (un heap ascendente: el menor
 * en la raiz).
 * @param n la capacidad inicial del heap.
 */
Heap::Heap(int n)
{
    init(n, true);
}

/*
 * Crea un Heap vacio, con capacidad inicial para 100 componentes. El tipo de heap
 * a crear depende del parametro t: si t = true, el heap sera ascendente (orientado a la
 * obtencion rapida del menor), si t = false entonces sera descendente (orientado a
 * la obtencion rapida del mayor)..
 * @param t el tipo de heap a crear (true: ascendente - false: descendente)
 */
Heap::Heap(bool t)
{
    init(100, t);
}

/*
 * Crea un Heap vacio, con capacidad inicial para n componentes. El tipo de heap a
 * crear depende del parametro t: si t = true, el heap sera ascendente (orientado a la
 * obtencion rapida del menor), si t = false entonces sera descendente (orientado a
 * la obtencion rapida del mayor).
 * @param n la capacidad inicial del heap.
 * @param t el tipo de heap a crear (true: ascendente - false: descendente)
 */
Heap::Heap(int n, bool t)
{
    init(n, t);
}

/*
 * Destructor. Libera la memoria ocupada por el heap.
 */
Heap::~Heap()
{
    delete []heap;
}

/*
 * Inserta un nuevo objeto en el heap. Se admiten repeticiones. La insercion se realiza
 * con tiempo de ejecucion de O(log(n)), siendo n la cantidad de elementos del heap.
 * @param data el objeto a insertar.
 */
void Heap::add(Comparable *data)
{
    if( ! isHomogeneus(data) ) return;

    int n = capacity;
    if(count == n) adjustCapacity(2*n);

    int s = count;
    heap[s] = data;
    while(s != 0)
    {
        int f = (s - 1) / 2;

        if( ! valid_change(s, f) ) break;

        Comparable *aux = heap[s];
        heap[s] = heap[f];
        heap[f] = aux;
        s = f;
    }

    count++;
}

/*
 * Remueve todos los elementos del heap y lo deja vacio. La capacidad vuelve
 * al valor de la capacidad con que inicialmente fue creado el heap. El tipo 
 * de heap (ascendente o descendente) se mantiene igual al que se tenia antes 
 * de invocar a clear.
 */
void Heap::clear()
{
    delete [] heap;

    heap = new (nothrow) Comparable * [initial_capacity];
    if( ! heap )
    {
        cout << "Memoria insuficiente..." << endl;
        system("pause");
        exit(1);
    }

    capacity = initial_capacity;
    count = 0;
}

/*
 * Retorna el elemento de la cima del Heap, sin removerlo. Si el Heap
 * es de tipo ascendente, el objeto retornado sera el menor del heap,
 * y si el heap es descendente, el objeto retornado sera el mayor. Si
 * el heap esta vacio, retorna null;
 */
Comparable * Heap::get()
{
    if(isEmpty()) return 0;
    return heap[0];
}

/*
 * Permite determinar si el Heap esta vacio.
 * @return true si el Heap esta vacio.
 */
bool Heap::isEmpty()
{
    return (count == 0);
}

/*
 * Obtiene y retorna el elemento de la cima del heap. Si el heap es de
 * tipo ascendente, ese elemento sera el menor del heap. En caso contrario
 * sera el mayor. Rearma el heap con los elementos restantes, de forma que
 * luego de terminada la operacion, la cima vuelve a contener al menor (o al
 * mayor) de los elementos que quedaban, y la cantidad de elementos se reduce
 * en uno. Si el heap esta vacio, retorna null. Tiempo de ejecucion esperado
 * (en el peor caso): O(log(n)).
 * @return el elemento menor (o el mayor) del heap.
 */
Comparable * Heap::remove()
{
    if(isEmpty()) return 0;

    Comparable *x = heap[0];

    heap[0] = heap[count - 1];
    count--;

    // si sobra demasiado lugar, achicar el vector...
    int n = capacity;
    int ic = initial_capacity;
    if(n/2 >= ic && count > ic && count < (n/2) * 0.9) adjustCapacity(n/2);

    int f = 0;
    while(f < count)
    {
        // calcular direcciones del hijo izquierdo (sl) y el derecho (sr)...
        int sl = f * 2 + 1;
        int sr = sl + 1;

        // si no hay hijos, cortar y terminar...
        if(sl >= count) break;

        // ...guardar en s el indice del hijo por el que se debe bajar...
        int s = sl;
        if(sr < count && !optimal_left(sl, sr) ) s = sr;

        // si ese hijo no debe cambiar de lugar con el padre, cortar y terminar...
        if( ! valid_change(s, f) ) break;

        // ... caso contrario, intercambiar padre (heap[f]) con el hijo correcto (heap[s])...
           Comparable *aux = heap[f];
           heap[f] = heap[s];
           heap[s] = aux;

        // ...seguir desde el hijo...
        f = s;
    }

    // ... y devolver el elemento que estaba originalmente en la cima...
    return x;
}


/*
 * Retorna la cantidad de elementos contenidos en el heap.
 * @return la cantidad de elementos del heap.
 */
int Heap::size()
{
    return count;
}

/*
 * Retorna el tipo de Heap: true si es ascendente, false si es descendente.
 * @return true: el heap es ascendente - false: es descendente.
 */
bool Heap::isAscendent()
{
    return ascendent;
}

/*
 * Privado. Ajusta la capacidad del arreglo al nuevo valor nc. Este valor puede ser
 * menor o mayor al anterior valor de capacidad. El metodo no controla si
 * la operacion es valida para la cantidad de elementos en el heap original.
 */
void Heap::adjustCapacity( int nc )
{
    int n = capacity;

    // cuantos elementos debo trasladar?
    int cant = n;
    if(nc < n) cant = count;

    // hacer el traslado...
    Comparable **newheap = new (nothrow) Comparable *[nc];
    if( ! newheap )
    {
        cout << "Memoria insuficiente..." << endl;
        system("pause");
        exit(1);
    }


    // copiar el bloque de memoria del viejo arreglo al nuevo...
    memcpy(newheap, heap, cant * sizeof(Comparable *));

    // eliminar el viejo arreglo...
    delete [] heap;

    // cambiar las referencias...
    heap = newheap;
    capacity = nc;
}

/*
 * Privado. Auxiliar de los constructores.
 */
void Heap::init(int n, bool t)
{
    int th = n;
    if(th <= 0) th = 100;

    heap = new (nothrow) Comparable *[th];
    if( ! heap )
    {
        cout << "Memoria insuficiente..." << endl;
        system("pause");
        exit(1);
    }

    capacity = th;
    initial_capacity = th;
    count = 0;
    ascendent = t;
}


/*
 * Privado. Chequea dos elementos hermanos y retorna true si el optimo es el izquierdo, o false si es
 * el derecho. Entendemos por "optimo" al menor de los dos si el heap es ascendente, o al mayor
 * si el heap es descendente.
 */
bool Heap::optimal_left(int sl, int sr)
{
    int r = heap[sl]->compareTo(heap[sr]);

    // si el heap es ascendente y el izquierdo es menor que el derecho, salir con true...
    if( ascendent && r < 0 ) return true;

    // si el heap es descendente y el izquierdo es mayor que el derecho, salir con true...
    if( ! ascendent && r > 0) return true;

    // el optimo no es el izquierdo...
    return false;
}

/*
 *  Privado. Retorna true el elemento en la posici�n s del heap deberia intercambiarse con el
 *  elemento en la posicion f del heap. Se supone que heap[s] es hijo (izquierdo o
 *  derecho) de heap[f], aunque el metodo no valida ese supuesto. La comprobacion se
 *  realiza de acuerdo al tipo de heap: si es un heap ascendente, se retornara true si
 *  heap[s] < heap[f], pero si el heap es descendente se retornara true si heap[s] > heap[f].
 */
bool Heap::valid_change(int s, int f)
{
    // comparar el hijo (heap[s]) con el padre (heap[f])...
    int r = heap[s]->compareTo(heap[f]);

    // ...si el menor debiera estar arriba, pero esta abajo, retorne true...
    if(ascendent && r < 0) return true;

    // ...si el mayor debiera estar arriba, pero esta abajo, retorne true...
    if( ! ascendent && r > 0) return true;

    // en cualquier otro caso, esta todo en orden... y no hay que hacer cambios...
    return false;
}

/*
 *  Privado. Controla que x sea compatible con el contenido del Heap.
 */
bool Heap::isHomogeneus(Comparable *x)
{
    if ( x == NULL ) return false;
    if( count != 0 && typeid(*x) != typeid(*heap[0]) ) return false;
    return true;
}
