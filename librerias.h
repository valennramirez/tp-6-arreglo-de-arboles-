#ifndef LIBRERIAS_H_INCLUDED
#define LIBRERIAS_H_INCLUDED

typedef struct {
   char especie[20];
   char animal[30];
   int habitat;
   int cant;
   int idEspecie;

} registroArchivo;

typedef struct {
    char nombreAnimal [30];
    int cantidad;
    int habitat; // 1 - selva, 2- savana, 3-bosque, 4-mar
} animal;

typedef struct
{  animal dato;
   struct nodoArbol * izq;
   struct nodoArbol * der;
} nodoArbol;

typedef struct
{
   int idEspecie;
   char especie [50];// "Mamiferos", "Aves" // "Reptiles", "Peces",”Anfibios”
   nodoArbol * arbolDeAnimales;
} celda;

#endif // LIBRERIAS_H_INCLUDED
