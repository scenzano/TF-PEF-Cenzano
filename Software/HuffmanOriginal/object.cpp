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

// Conversion a String
string Object::toString()
{
    string res( typeid(*this).name() );
    char cad[10];
    sprintf( cad, "%x", (int)this );
    res.append( "@" );
    res.append( cad );
    return res;
}

// Obtencion de un identificador numérico
int Object::hashCode()
{
    return (int)this;
}
