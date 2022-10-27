#include "librerias.h"
#include <stdio.h>
#include <stdlib.h>

///archivo

void mostrarArchivoRegistros (char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo, "rb");

    registroArchivo aux;
    int i=1;

    if (archivo!=NULL)
    {
        while (fread(&aux, sizeof(registroArchivo), 1, archivo)>0)
        {
            printf ("Registro n %d\n", i);

            printf ("Animal: %s\n", aux.animal);

            printf ("Cantidad: %d\n", aux.cant);

            printf ("Habitat: %d\n", aux.habitat);

            printf ("Id especie: %d\n", aux.idEspecie);

            printf ("Especie: %s\n", aux.especie);

            printf ("\n\n");

            i++;
        }

        fclose(archivo);
    }
}

/// arboles

nodoArbol *inicarbol ()
{
    return NULL;
}

nodoArbol *crearNodo (char nombreAnimal[], int cantidad, int habitat)
{
    nodoArbol *nn=(nodoArbol*)malloc(sizeof(nodoArbol));

    strcpy(nn->dato.nombreAnimal, nombreAnimal);
    nn->dato.cantidad=cantidad;
    nn->dato.habitat=habitat;

    nn->der=NULL;
    nn->izq=NULL;

    return nn;
}

nodoArbol *insertar (nodoArbol *arbol, nodoArbol *nn)
{
    if (arbol==NULL)
    {
        arbol=nn;
    }
    else
    {
        if(arbol->dato.cantidad<nn->dato.cantidad)
        {
            arbol->der=insertar(arbol->der, nn);
        }
        else
        {
            arbol->izq=insertar(arbol->izq, nn);
        }
    }

    return arbol;
}

///arreglo de arboles

int buscarPosEspecie (celda ada[], char especie[], int validos)
{
    int i=0;
    int rta=-1;

    while (i<validos && rta==-1)
    {
        if (strcmpi(ada[i].especie, especie)==0)
        {
            rta=i;
        }

        i++;
    }

    return rta;
}



///funciones para el tp

int pasarDeArchivoToADA (celda ada[], int dimension, char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo, "rb");

    registroArchivo aux;
    int validos=0;

    if (archivo!=NULL)
    {
        while (fread(&aux, sizeof(registroArchivo), 1, archivo)>0 && validos<dimension)
        {
           mostrarArchivoRegistros("animales.dat");
        }
        fclose(archivo);
    }

    return validos;
}
