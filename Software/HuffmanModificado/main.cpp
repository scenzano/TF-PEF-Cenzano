#include <iostream>
#include "HuffmanCompressor.h"
using namespace std;

int main(int argc, char *argv[])
{
    HuffmanCompressor *compresor = new HuffmanCompressor();
    int op;
    string nombre_archivo = "";

    if(argc < 3)
    {
        cout << "Uso: " << endl;
        cout << "HuffmanCompressor.exe [ comprimir | descomprimir ] [ archivoParaComprimir | archivoParaDescomprimir ]" << endl;
    }
    else
    {
        if((std::string(argv[1]) == "comprimir"))
        {
            compresor->comprimir((std::string(argv[2])));
        }
        else if((std::string(argv[1]) == "descomprimir"))
        {
            compresor->descomprimir((std::string(argv[2])));
        }
    }
    return 0;
}

