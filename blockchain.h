#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generador_primos.h"

typedef struct Nodo {
    char* mensaje;
    int id;
    struct Nodo* ant;
    struct Nodo* sig;
} Nodo;

typedef struct Blockchain {
    Nodo* primerN;
    Nodo* ultimoN;
    struct Blockchain* sig;
} Blockchain;

typedef struct Federada {
    Blockchain** arreglo;
    int cantB;
    int* hojas;
    int raiz;
} Federada;

Nodo* crear_nodo(char* msj, int nro_nodo);
Blockchain* crear_b();
void insertNodo (Blockchain* b, Nodo* n);
Nodo* buscarNodo(Blockchain* b, int id);
void liberarMemBlockchain(Blockchain* b); 

Federada* crear_f(int cant);
void insertBlockchain(Federada* f, Blockchain* b);
void liberarMemFed(Federada* f);

void alta(Federada*, int* nro_nodo, int, char*);
void actualizar(Federada* f, int id_bloc, int id_viejo, char* msj, int* nro_nodo);
int validar(Federada*);
int validar_subconjunto(Federada*, int n, int max, int min);

#endif
