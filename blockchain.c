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


void alta(Federada* f, int *nro_nodo, int posB, char* msj) {
    
    if (!f || posB < 0 || posB >= f->cantB) return;
    
    int *ids = primos(*nro_nodo);
    int idNodo = ids[*nro_nodo - 1];

    Blockchain* b = f->arreglo[posB];
    Nodo* n = crear_nodo(msj, idNodo);
    insertNodo(b, n);

    f->hojas[posB] = b->ultimoN->id;
    int raiz = 1;
    for (int i = 0; i < f->cantB; i++) {
        if (f->hojas[i] > 0) raiz *= f->hojas[i];
    }
    f->raiz = raiz;

    (*nro_nodo) ++;
}

void actualizar(Federada* f, int id_bloc, int id_viejo, char* msj, int* nro_nodo) {
    if (!f || id_bloc < 0 || id_bloc >= f->cantB || id_viejo <= 0 || !nro_nodo) 
        return;
    
    Blockchain *b = f->arreglo[id_bloc];
    if (!b) return;

    Nodo *actual = b->primerN;
    int empezar_actualizar = 0;
    while(actual){
        if(actual->id == id_viejo)
            empezar_actualizar = 1;
        
        if(empezar_actualizar) {
            if(actual->id == id_viejo)
                actual->mensaje = msj;
            
            int *nuevos_ids = primos(*nro_nodo);
            actual->id = nuevos_ids[*nro_nodo - 1];
            free(nuevos_ids);
            (*nro_nodo)++;
        }
        actual = actual->sig;
    }

    f->hojas[id_bloc] = b->ultimoN->id;
    actual = b->primerN;
    f->raiz = 1;
    for(int i = 0; i < f->cantB; i++)
        if (f->arreglo[i] && f->arreglo[i]->ultimoN) {
            f->raiz *= f->hojas[i];
        }

}

int validar(Federada *fed){
    int producto = 1;

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

int validar_subconjunto(Federada *fed, int expect, int min, int max){
    if (!fed || min < 0 || max >= fed->cantB || min > max) return 0;
    
    int producto = 1;

    for(int i = min; i <= max; i++){
        if(!fed->arreglo || !fed->arreglo[i] || !fed->arreglo[i]->ultimoN)
            return 0;

        producto *= fed->hojas[i];
    }

    return (producto == expect) ? 1 : 0;
}