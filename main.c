#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "generador_primos.h"
#include "blockchain.h"

int main() {
    int nro_nodo = 1;

    /* Crear federada con 3 blockchains */
    Blockchain *bc_1 = crear_b();
    Blockchain *bc_2 = crear_b();
    Blockchain *bc_3 = crear_b();

    Federada *fede = crear_f(3);
    insertBlockchain(fede, bc_1);
    insertBlockchain(fede, bc_2);
    insertBlockchain(fede, bc_3);

    alta(fede, &nro_nodo, 0, "hola");
    alta(fede, &nro_nodo, 1, "chau");
    alta(fede, &nro_nodo, 2, "que");

    //valido después de agregar nodos con alta
    assert(validar(fede) == 1);


    int id_viejo = bc_2->primerN->id;
    actualizar(fede, 1, id_viejo, "so", &nro_nodo);
    assert(validar(fede) == 1);


    int esperado = fede->hojas[0] * fede->hojas[1];
    assert(validar_subconjunto(fede, esperado, 0, 1) == 1);
    assert(validar_subconjunto(fede, 123456, 0, 1) == 0);


    // alta fuera de rango
    alta(fede, &nro_nodo, -1, "fuera");
    alta(fede, &nro_nodo, 99, "fuera");
    assert(validar(fede) == 1);
   
    //maximos y minimos fuera de rango
    assert(validar_subconjunto(fede, 0, -1, 1) == 0);
    assert(validar_subconjunto(fede, 0, 1, 99) == 0);
    assert(validar_subconjunto(fede, 0, 2, 0) == 0);
    
    printf("El arbol se corresponde con el producto de los ids? %i\n", validar(fede));
    printf("El producto de los ids de los subconjuntos da el valor esperado? %i\n", validar_subconjunto(fede, 14, 0, 1));
    printf("Todos los tests pasaron correctamente\n");

    liberarMemFed(fede);
    return 0;
}
