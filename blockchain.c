#include "blockchain.h"

Nodo* crear_nodo(char* msj, int id) {
    Nodo* n = malloc(sizeof(Nodo));

    if (!n) return NULL;

    n->mensaje = strdup(msj);
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

    f->arreglo = malloc(sizeof(Blockchain*) * cant);
    f->cantB = cant;
    f->hojas = malloc(cant * sizeof(int));
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


void alta(Federada* f, int idNodo, int posB, char* msj) {
    if (!f || posB < 0 || posB >= f->cantB) return;

    Blockchain* b = f->arreglo[posB];
    Nodo* n = crear_nodo(msj, idNodo);
    insertNodo(b, n);

    f->hojas[posB] = b->ultimoN->id;
    int raiz = 1;
    for (int i = 0; i < f->cantB; i++) {
        if (f->hojas[i] > 0) raiz *= f->hojas[i];
    }
    f->raiz = raiz;
}

void actualizar(Blockchain* b, Nodo* n, char* msj, Federada* f) {
    if (!b || !n) return;

    int contador = 0;
    Nodo* actual = n;
    while (actual) {
        contador++;
        actual = actual->sig;
    }

    int* lista = primos(contador + 10);

    if (n->mensaje) free(n->mensaje);  
    n->mensaje = strdup(msj);

    actual = n;
    int i = 0;
    while (actual) {
        actual->id = lista[i];
        f->hojas[i] = actual->id;
        f->raiz *= f->hojas[i];
        i++;
        actual = actual->sig;
    }


    free(lista);
}

int validar(Federada *fed){
    int producto;

    if(!fed->arreglo && !fed->raiz)
        return 1;

    for(int i = 0; i < fed->cantB; i++){
        producto *= fed->arreglo[i]->ultimoN->id;

        Nodo *actual = fed->arreglo[i]->primerN;
        while(actual->sig){

            if(actual->id > actual->sig->id) //si no se cumple la condicion de orden, devuelve falso
                return 0;
            
                actual = actual->sig;
        }
    }

    if(producto == fed->raiz)
        return 1;

    return 0;
}