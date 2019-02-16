#include "Nodo.h"

Nodo::Nodo()
{
        info=0;
        next=0;
}

Nodo::Nodo(Comparable *x,Nodo *p)
{
	info=x;
	next = p;
}

Nodo :: ~Nodo()
{
}

Comparable * Nodo::getInfo()
{
	return info;
}

void Nodo :: setInfo(Comparable * x)
{
	info = x;
}

Nodo * Nodo::getNext()
{
	return next;
}

void Nodo :: setNext(Nodo *p)
{
	next=p;
}
