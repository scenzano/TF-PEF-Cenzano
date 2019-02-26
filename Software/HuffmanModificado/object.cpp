#include "object.h"

//********************Constructores y Destructor
Object::Object() {
}

Object::~Object() {
}

/*
 * Determina si los objetos son "iguales"... Lo unico que puede hacer
 * en un contexto polimorfico es comparar las direcciones de memoria...
 */
bool Object::equals( Object * otro ) {
    return ( this == otro );
}

// Obtencion de un identificador numérico
int Object::hashCode()
{
    return (int)this;
}
