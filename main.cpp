#include <iostream>
#include "HuffmanCompressor.h"
using namespace std;

int main(int argc, char *argv[])
{
    HuffmanCompressor *compresor = new HuffmanCompressor();
    int op;
    string nombre_archivo = "";

    cout << "Prueba de Compresión y Descompresión";

    do
    {
        system("clear");
        cout << endl <<"1. Fase de compresion...";
        cout << endl <<"2. Fase de descompresion...";
        cout << endl <<"3. Salir";
        cout << endl << "Ingrese opcion: ";
        cin >> op;

        system("clear");
        switch(op)
        {
            case 1: cout << "Archivo a comprimir: ";
					cin.ignore();
                    getline(cin, nombre_archivo);
                    compresor->comprimir(nombre_archivo);
                    
                    cout << endl <<"Hecho...";
                    cin.ignore();
                    cout << "Presione alguna tecla para continuar...";
                    getchar();
                    break;

            case 2: cout << "Archivo a descomprimir: ";
					cin.ignore();
					getline(cin, nombre_archivo);
					compresor->descomprimir(nombre_archivo);
					
                    cout << endl << "Hecho..." << endl;
                    cin.ignore();
                    cout << "Presione alguna tecla para continuar...";
                    getchar();
                    break;

			case 3: break;

            default: cout << "La opcion seleccionada no es valida." << endl;
                    system("pause");
        }
    }
    while( op != 3 );

    return 0;
}

