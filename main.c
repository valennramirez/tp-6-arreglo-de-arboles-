#include <stdio.h>
#include <stdlib.h>
#include "librerias.h"

int main()
{

    //mostrarArchivoRegistros("animales.dat");

    celda ada[10];
    int i, validos;

    validos=pasarDeArchivoToADA(ada, 10, "animales.dat");

    for(i=0; i<validos; i++)
    {
        printf ("Arboles de animales n %i: \n", i);
        printf ("Especie %s: \n", ada[i].especie);
        mostrarPreorden(ada[i].arbolDeAnimales);
    }


    //pasarAdaToArchivo(ada, validos);

    /*
    for (i=0; i<validos; i++)
    {
        mostrarArchivoAnimal(ada[i].especie);
    }

*/
}
