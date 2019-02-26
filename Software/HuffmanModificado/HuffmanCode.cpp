#include "HuffmanCode.h"

HuffmanCode::HuffmanCode(HuffmanCode *c)
{
    int i = 0;
    int offset = MAXBITS % 8;
    int posicion_comienzo = c->startPos;

    for (i = offset - 1; i >= 0; --i)
    {
        bits[i] = c->bits[i];
    }
    for(int i = MAXBITS - 1; i >= (offset + posicion_comienzo); i-=8)
    {
        bits[i] = c->bits[i];
        bits[i - 1] = c->bits[i - 1];
        bits[i - 2] = c->bits[i - 2];
        bits[i - 3] = c->bits[i - 3];
        bits[i - 4] = c->bits[i - 4];
        bits[i - 5] = c->bits[i - 5];
        bits[i - 6] = c->bits[i - 6];
        bits[i - 7] = c->bits[i - 7];
    }
    startPos = posicion_comienzo;
}

HuffmanCode::~HuffmanCode()
{
    delete bits;
}

void HuffmanCode::setBit(int bit)
{
    if( startPos == 0 )
    {
        cout << "Codigo muy largo";
        exit(1);
    }
    startPos--;
    bits[startPos] = bit;
}

