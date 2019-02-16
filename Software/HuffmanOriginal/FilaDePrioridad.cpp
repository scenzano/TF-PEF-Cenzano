#include "FilaDePrioridad.h"

FilaDePrioridad::FilaDePrioridad()
{
    frente = 0;
}


FilaDePrioridad::~FilaDePrioridad()
{
   while (frente)
   {
      Nodo *p = frente;
      frente = frente->getNext();
      delete p;
   }
}

Nodo * FilaDePrioridad::getFrente()
{
    return frente;
}

void FilaDePrioridad::insertar (Comparable *nuevo)
{
   // insertar ordenado
   if ( nuevo )
   {
       if ( frente && typeid( *nuevo ) != typeid( * ( frente->getInfo() )  ) ) return;
       Nodo *nue = new Nodo (nuevo, 0);
       if (nue)
       {
           Nodo *p = frente, *q = 0;
           while(p && nuevo->compareTo(p->getInfo()) > 0)
           {
               q = p;
               p = p->getNext();
           }
           nue->setNext(p);
           if(q) q->setNext(nue);
           else frente = nue;
       }
   }
}

Comparable * FilaDePrioridad::borrar ()
{
   if (frente == 0) return 0;
   Comparable *x = (Comparable *)frente->getInfo();
   Nodo *p = frente;
   frente = frente->getNext();
   delete p;
   return x;
}
