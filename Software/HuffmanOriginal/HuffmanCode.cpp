#include "HuffmanCode.h"

HuffmanCode::HuffmanCode(HuffmanCode *c)
{
    for( int i = c->startPos; i < MAXBITS; i++ )
    {
        bits[i] = c->bits[i];
    }
    startPos = c->startPos;
}

HuffmanCode::~HuffmanCode()
{
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

string HuffmanCode::toString()
{
    string res = "";

    for(int i = startPos; i < MAXBITS; i++)
    {
        char sn[5];
        sprintf(sn, "%d", bits[i]);
        res.append(sn);
    }

    return res;
}
