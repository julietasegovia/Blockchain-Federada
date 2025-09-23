#include "blockchain.h"

Nodo* crear_nodo(char* msj, int id) {
    Nodo* n = malloc(sizeof(Nodo));
    if (!n) return NULL;
    n->mensaje = strdup(msj); // reserva memoria y copia
    n->id = id;
    n->ant = NULL;
    n->sig = NULL;
    return n;
}

Blockchain* crear_b() {
    Blockchain* b = malloc(sizeof(Blockchain));
    if (!b) return NULL;
    b->primerN = NULL;
    b->ultimoN = NULL;
    b->sig = NULL;
    return b;
}

void insertNodo(Blockchain* b, Nodo* n) {
    if (!b || !n) return;
    if (b->primerN == NULL) {
        b->primerN = n;
        b->ultimoN = n;
    } else {
        n->ant = b->ultimoN;
        b->ultimoN->sig = n;
        b->ultimoN = n;
    }
}

Nodo* buscarNodo(Blockchain* b, int id) {
    if (!b) return NULL;
    Nodo* act = b->primerN;
    while (act != NULL) {
        if (act->id == id)
            return act;
        act = act->sig;
    }
    return NULL;
}

void liberarMemBlockchain(Blockchain* b) {
    if (!b) return;
    Nodo* momentaneo = b->primerN;
    while (momentaneo != NULL) {
        Nodo* liberar = momentaneo;
        momentaneo = momentaneo->sig;
        free(liberar->mensaje);
        free(liberar);
    }
    free(b);
}

Federada* crear_f(int cant) {
    Federada* f = malloc(sizeof(Federada));
    if (!f) return NULL;
    f->arreglo = calloc(cant, sizeof(Blockchain*));
    f->cantB = cant;
    f->hojas = calloc(cant, sizeof(int)); // si no lo usas, podrías inicializar en NULL
    f->raiz = -1;
    return f;
}

void insertBlockchain(Federada* f, Blockchain* b) {
    if (!f || !b) return;
    for (int i = 0; i < f->cantB; i++) {
        if (f->arreglo[i] == NULL) {
            f->arreglo[i] = b;
            return;
        }
    }
    // Si está lleno, no inserta nada
}

void liberarMemFed(Federada* f) {
    if (!f) return;
    for (int i = 0; i < f->cantB; i++) {
        if (f->arreglo[i] != NULL) {
            liberarMemBlockchain(f->arreglo[i]);
        }
    }
    free(f->hojas);
    free(f->arreglo);
    free(f);
}
