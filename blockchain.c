#include "blockchain.h"

Nodo* crear_nodo(char* msj, int id){
    Nodo* n = malloc(sizeof(Nodo));
    strcpy(n->mensaje, msj);
    n->id = id;
    n->ant = NULL;
    n->sig = NULL;
    return n;
}

Blockchain* crear_b(int id){
    Blockchain* b = malloc(sizeof(Blockchain));
    b->primerN = NULL;
    b->ultimoN = NULL;
    b->sig = NULL;
    return b;
}
void insertNodo (Blockchain* b, Nodo* n){
    if(b->primerN == NULL) {
        b->primerN = n;
        b->ultimoN = n;
    } else {
        n->ant = b->ultimoN;
        b->ultimoN->sig = n;
        b->ultimoN = n;
    }
}

Nodo* buscarNodo(Blockchain* b, int id) {
    Nodo* act = b->primerN;
    while (act != NULL) {
        if(act->id == id)
            return actual
        act = act->sig;
    }
    return NULL;
}

void liberarMemBlockchain(Blockchain* b) {
    Nodo* momentaneo = b->primerN;
    while(momentaneo != NULL) {
        Nodo* liberar = momentaneo;
        momentaneo = momentaneo->sig;
        free(librerar->mensaje);
        free(liberar)
    }
    free(b);
}

Federada* crear_f(){
    Federada* f = malloc(sizeof(Federada));
    f->primerB = NULL;
    return f;
}
void insertBlockchain(Federada* f, Blockchain* b){
    b->sig = f->ultimoB;
    f->ultimoB = b;
}

