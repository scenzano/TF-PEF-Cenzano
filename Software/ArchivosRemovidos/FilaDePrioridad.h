// FilaDePrioridad.h: interface for the FilaDePrioridad class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _FILADEPRIORIDAD_H
#define	_FILADEPRIORIDAD_H

#include <iostream>
#include "Object.h"
#include "Comparable.h"
#include "Nodo.h"


class FilaDePrioridad  : public Object
{

private:
        Nodo *frente;

public:
	FilaDePrioridad();
	virtual ~FilaDePrioridad();
	Nodo * getFrente();
	void insertar (Comparable *nuevo);
	Comparable * borrar ();
};

#endif /* _FILADEPRIORIDAD_H */
