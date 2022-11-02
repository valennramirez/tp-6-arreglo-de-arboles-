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

void mostrarArchivoAnimal (char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo, "rb");
    nodoArbol *aux;

    if(archivo!=NULL)
    {
        while (fread(aux, sizeof(nodoArbol), 1, archivo)>0)
        {
            mostrarNodoArbol(aux);
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

void mostrarNodoArbol (nodoArbol *nn)
{
    printf ("Nombre animal: %s\n", nn->dato.nombreAnimal);
    printf ("Cantidad: %d\n", nn->dato.cantidad);
    printf ("Habitat: %d\n", nn->dato.habitat);
}

void mostrarPreorden (nodoArbol *arbol)
{
    if (arbol!=NULL)
    {
        mostrarNodoArbol(arbol);
        mostrarPreorden (arbol->izq);
        mostrarPreorden (arbol->der);
    }
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
int agregarEspecie (celda ada[], char especie[], int validos)
{
    strcpy(ada[validos].especie, especie);
    ada[validos].idEspecie=validos;
    ada[validos].arbolDeAnimales=inicarbol();

    validos++;

    return validos;
}

int alta (celda ada[], char especie[], char nombreAnimal[], int habitat, int cantidad, int validos)
{
    nodoArbol *aux=crearNodo(nombreAnimal, cantidad, habitat);

    int pos=buscarPosEspecie(ada, especie, validos);

    if (pos==-1)
    {
        validos=agregarEspecie(ada, especie, validos);
        pos=validos-1;
    }

    ada[pos].arbolDeAnimales=insertar(ada[pos].arbolDeAnimales, aux);

    return validos;
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


            validos=alta(ada, aux.especie, aux.animal, aux.habitat, aux.cant, validos);
        }
        fclose(archivo);
    }

    return validos;
}

void pasarArbolToArchivo (char nombreArchivo[], nodoArbol *arbol)
{
    FILE *archivo=fopen(nombreArchivo, "wb");

    if(archivo!=NULL)
    {
        while(arbol!=NULL)
        {
            pasarArbolToArchivo(nombreArchivo, arbol->izq);

            fwrite(arbol, sizeof(nodoArbol), 1, archivo);
        }

        fclose(archivo);
    }
}

void pasarAdaToArchivo (celda ada[], int validos)
{
    int i=0;

    while (i<validos)
    {
        pasarArbolToArchivo(ada[i].especie, ada[i].arbolDeAnimales->izq);
        pasarAdaToArchivo(ada[i].especie, ada[i].arbolDeAnimales->der);

        i++;
    }
}
