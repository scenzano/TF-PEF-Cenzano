#include "HuffmanCompressor.h"
#include "string.h"

HuffmanCompressor::HuffmanCompressor()
{
}

void HuffmanCompressor::comprimir (string fileName)
{
        //obtengo el nombre del archivo, sin la extension
        unsigned int point_pos = fileName.find(".");
        
        if( point_pos == string::npos ) point_pos = fileName.length();
        string nombre = fileName.substr(0, point_pos );

        // abro los archivos
        char * f1 = new char[fileName.length() + 1];
        strcpy(f1, fileName.c_str());

        nombre.append(".cmp");
        char * f2 = new char[nombre.length() + 1];
        strcpy(f2, nombre.c_str());

        FILE *fuente = fopen(f1, "rb");
        if( !fuente ) { cout<<"Error de apertura: " << f1 << endl; getchar(); return; }

        FILE *comprimido = fopen(f2, "wb");
        if( !comprimido ) { cout<<"Error de apertura: " << f2 << endl; getchar(); fclose(fuente); return; }

        // contamos cuantas veces aparece cada byte en el archivo fuente
        int conteo[256];
        unsigned char byte;
        int t = sizeof(unsigned char);

        // contamos los bytes diferentes que hay en el archivo ...
        int i;
        for(i=0; i<256; i++) conteo[i] = 0;

        fread(&byte, t, 1, fuente);
        while( !feof(fuente) )
        {
            conteo[byte]++;
            fread(&byte, t, 1, fuente);
        }

        // cuento cuantos bytes diferentes hay...
        cantSignos = 0;
        for(i = 0; i < 256; i++)
        {
            if( conteo[i] != 0 ) cantSignos++;
        }

        // creamos el Arbol con lugar para esa cantidad de signos
        ht = new HuffmanTree(cantSignos);

        // inicializamos el arbol de Huffman con los signos y sus frecuencias
        int ind = 0;
        for( i = 0;  i < 256;  i++ )
        {
              if( conteo[i] != 0 )
              {
                  ht->setNodo((unsigned char)i , conteo[i], ind);
                  ind++;
              }
        }

        // armamos el arbol y obtenenos el codigo Huffman de cada signo
        ht->encode();

        // cantidad de bytes del archivo fuente
        fseek(fuente, 0, SEEK_END);
        long tArch = ftell( fuente );

        // guardo en el archivo comprimido informacion para el descompresor...

        // ...empiezo guardando el tamaño del nombre, el nombre y la extension del original...
        int tf = strlen(f1);
        fwrite( &tf, sizeof(int), 1, comprimido );
        fwrite( f1, tf, 1, comprimido );  // no graba el caracter nulo del final...

        // ... luego guardo la longitud en bytes del archivo original...
        fwrite( &tArch, sizeof(long), 1, comprimido);

        // ... la cantidad de simbolos (o sea, la cantidad de hojas del arbol)...
        fwrite( &cantSignos, sizeof(int), 1, comprimido );

        // ... ahora la tabla de simbolos tal como esta en el arbol...
        for( i = 0; i < cantSignos; i++ )
        {
            unsigned char signo = (unsigned char) ht->getSigno(i);
            fwrite( &signo, sizeof(unsigned char), 1, comprimido );
        }

        // ... ahora el vector que representa al arbol...
        HuffmanNode *a = ht->getArbol();
        int n = cantSignos * 2 - 1;  // cantidad total de nodos del arbol
        for( i = 0; i < n; i++ )
        {
            // ...por cada nodo, guardar todos sus datos...
            int f = a[i].getFrecuencia();
            fwrite( &f, sizeof(int), 1, comprimido );

            int p = a[i].getPadre();
            fwrite(&p, sizeof(int), 1, comprimido );

            bool is = a[i].isLeft();
            fwrite( &is, sizeof(bool), 1, comprimido );

            int izq = a[i].getIzquierdo();
            fwrite( &izq, sizeof(int), 1, comprimido );

            int der = a[i].getDerecho();
            fwrite( &der, sizeof(int), 1, comprimido );
        }

        // comienza fase de compresion (por fin...)
        unsigned char mascara = 0x80;  // el valor 1000 0000
        unsigned char salida  = 0x00;  // el valor 0000 0000
        int bit = 0; // en que bit vamos?

        rewind( fuente );   // vuelvo el fp al principio
        fread( &byte, sizeof(unsigned char), 1, fuente );
        while( !feof( fuente ) )
        {

            // codigo Huffman del caracter tomado
            HuffmanCode *hc = ht->getCodigo( byte );
            int *v = hc->getCodigo();
            int ini = hc->getStartPos();

            for( i = ini; i < MAXBITS; i++ )
            {
                if( v[i] == 1 )
                {
                    // si era 1, lo bajamos al byte de salida (si era cero, ni modo...)
                    salida = salida | mascara;
                }
                mascara = mascara >> 1;  // corremos el uno a la derecha, rellenando con ceros a la izquierda...
                bit++;
                if( bit == 8 )
                {
                    //se lleno el byte de salida...
                    fwrite( &salida, sizeof(unsigned char), 1, comprimido);
                    bit = 0;
                    mascara = 0x80;
                    salida  = 0x00;
                }
            }

            fread( &byte, sizeof(unsigned char), 1, fuente );
        }

        if ( bit != 0 )
        {
            // grabar el ultimo byte que estaba incompleto
            fwrite( &salida, sizeof(unsigned char), 1, comprimido);
        }
        fclose( comprimido );
        fclose( fuente );
}


void HuffmanCompressor::descomprimir( string fileName )
{
        unsigned int point_pos = fileName.find(".");
        if( point_pos == string::npos ) { cout << "El archivo no parece un archivo comprimido..." << endl; getchar(); return; }

        string ext = fileName.substr( point_pos + 1, fileName.length() );
        if( ext.compare("cmp") != 0 ) { cout << "El archivo no tiene la extension cmp..." << endl; getchar(); return; }

        // abro el archivo comprimido...
        char * f1 = new char[ fileName.length() ];
        strcpy( f1, fileName.c_str() );

        FILE * comprimido = fopen(f1, "rb");
        if( !comprimido ) { cout<<"Error de apertura: " << f1 << endl; getchar(); return; }

        // ... y recupero el nombre del archivo original
        int tf;
        fread( &tf, sizeof(int), 1, comprimido );

        char *f2 = new char[tf + 1];
        fread( f2, tf, 1, comprimido );
        f2[tf] = '\0';

        // creo el archivo con el nombre del original
        FILE * original = fopen(f2, "wb");
        if( !original ) { cout<<"Error de apertura: " << f2 << endl; getchar(); fclose( comprimido ); return; }

        // y ahora, recupero todos los datos que el compresor dejo adelante...

        // ... empezando por el tamaño del archivo original...
        long tArch;
        fread( &tArch, sizeof(long), 1, comprimido);


        // ... la cantidad de signos de la tabla (o sea, la cantidad de hojas)...
        fread( &cantSignos, sizeof(int), 1, comprimido);

        // ...creo de nuevo el arbol en memoria...
        ht = new HuffmanTree(cantSignos);

        // ... y recupero uno a uno los signos originales, guardandolos de nuevo en el arbol...
        int i;
        for( i = 0; i < cantSignos; i++ )
        {
            unsigned char signo;
            fread( &signo, sizeof(unsigned char), 1, comprimido );
            ht->setSigno(signo, i);
        }

        // ...ahora le toca al vector del arbol...
        int n = cantSignos * 2 - 1;  // cantidad total de nodos del arbol
        for( i = 0; i < n; i++ )
        {
            // ...por cada nodo, recuperar todos sus datos y volver a armar el arbol...
            int f;
            fread( &f, sizeof(int), 1, comprimido);       // frecuencia

            int padre;
            fread( &padre, sizeof(int), 1, comprimido);   // padre

            bool left;
            fread( &left, sizeof(bool), 1, comprimido);   // es izquierdo?

            int hi;
            fread( &hi, sizeof(int), 1, comprimido);      // hijo izquierdo

            int hd;
            fread( &hd, sizeof(int), 1, comprimido);      // hijo derecho

            HuffmanNode nh( f, padre, left, hi, hd );
            ht->setNodo(nh, i);
        }

        // y habiendo llegado aca, el descompresor vuelve a pedir que se creen los codigos de Huffman
        ht->makeCodes();

        // de aca saco el vector que representa al arbol y el indice de la raiz...
        HuffmanNode *v2 = ht->getArbol();
        int raiz =  n - 1;  // la raiz esta en la ultima casilla del vector!!!!

        // comienza la fase de descompresion
        unsigned char aux;             // auxiliar para desenmascarar
        unsigned char mascara;
        int bit, nodo = raiz;          // comenzamos desde la raiz y vamos bajando
        long cantBytes = 0;            // cuantos bytes llevo grabados??

        // leo byte por byte el archivo comprimido... sigo desde donde quedo el file pointer
        unsigned char car;
        fread( &car, sizeof(unsigned char), 1, comprimido );
        while( !feof(comprimido) )
        {
            mascara = 0x80;
            for( bit = 0; bit < 8 && cantBytes != tArch; bit++ )
            {
                aux = car & mascara;
                if(aux == mascara)
                {
                    // el bit en la posicion "bit" era un uno...
                    nodo = v2[nodo].getDerecho();
                }
                else
                {
                    // era un cero...
                    nodo = v2[nodo].getIzquierdo();
                }
                mascara = mascara >> 1;  // corremos el 1 a la derecha y rellenamos con ceros a la izquierda...

                if ( v2[nodo].getIzquierdo() == -1 )
                {
                    // llegamos a una hoja... grabar el signo que esta en ella
                    unsigned char sal = ht->getSigno( nodo );
                    fwrite( &sal, sizeof(unsigned char), 1, original );
                    cantBytes++;

                    // volver a la raiz
                    nodo = raiz;
                }
            }

            fread( &car, sizeof(unsigned char), 1, comprimido );
        }
        fclose( original );
        fclose( comprimido );
}
float HuffmanCompressor :: desafio3 (const char fileName[])
{

        FILE *fuente = fopen(fileName, "rb");
        if( !fuente ) { cout<<"Error de apertura: " << endl; system("pause"); return 0; }

        // contamos cuantas veces aparece cada byte en el archivo fuente
        int conteo[256];
        unsigned char byte;
        int t = sizeof(unsigned char);

        // contamos los bytes diferentes que hay en el archivo ...
        int i;
        for(i=0; i<256; i++) conteo[i] = 0;

        fread(&byte, t, 1, fuente);
        while( !feof(fuente) )
        {
            conteo[byte]++;
            fread(&byte, t, 1, fuente);
        }

        // cuento cuantos bytes diferentes hay...
        cantSignos = 0;
        for(i = 0; i < 256; i++)
        {
            if( conteo[i] != 0 ) cantSignos++;
        }

        // creamos el Arbol con lugar para esa cantidad de signos
        ht = new HuffmanTree(cantSignos);

        // inicializamos el arbol de Huffman con los signos y sus frecuencias
        int ind = 0;
        for( i = 0;  i < 256;  i++ )
        {
              if( conteo[i] != 0 )
              {
                  ht->setNodo((unsigned char)i , conteo[i], ind);
                  ind++; //cantidad de signos en el nuevo vector
              }
        }
        
        // armamos el arbol y obtenenos el codigo Huffman de cada signo
        ht->encode();
        
        
        // cantidad de bytes del archivo fuente
        fseek(fuente, 0, SEEK_END);
        long tArch = ftell( fuente );
        fclose (fuente);
        float ac = 0;
        for (int i= 0; i<256; i++)
        {
            if (conteo[i]!=0)
            {
                float pi = conteo[i] / (float)tArch;
                
                HuffmanCode *hc = ht->getCodigo((unsigned char) i );
                float bi = MAXBITS - hc->getStartPos();
                ac = ac + (pi * bi);
            }
        }
    
        return ac;
}