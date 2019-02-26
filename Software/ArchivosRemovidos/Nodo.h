#ifndef _NODO_H
#define	_NODO_H
#include <iostream>
#include "Object.h"
#include "Comparable.h"

class Nodo  : public Object
{

private:
        Comparable *info;
	Nodo *next;

public:
	
	Nodo();
	Nodo(Comparable *x, Nodo *p);
	virtual ~Nodo();
	Comparable *getInfo();
	Nodo *getNext();
	void setInfo(Comparable *x);
	void setNext(Nodo *p);
};

#endif /* NODO_H */
