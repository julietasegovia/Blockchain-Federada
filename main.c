#include "stdlib.h"
#include "stdio.h"
#include "generador_primos.h"
#include "blockchain.h"

int main() {
  // Genero y muestro los primeros 100 números primos
  int *p = primos(100);
  for(int i = 0; i < 100; i++)
    printf("%d ",p[i]);

  // Uso los números primos

  int nro_nodo = 1;

  Blockchain *bc_1 = crear_b();
  Blockchain *bc_2 = crear_b();
  Blockchain *bc_3 = crear_b();

  char msj1[10] = "hola", msj2[10] = "chau", msj3[10] = "que";

  Nodo *n_1 = crear_nodo(msj1, nro_nodo);
  Nodo *n_2 = crear_nodo(msj2, nro_nodo);
  Nodo *n_3 = crear_nodo(msj3, nro_nodo);

  insertNodo(bc_1, n_1);
  insertNodo(bc_2, n_2);
  insertNodo(bc_3, n_3);

  // IMPORTANTE: libero la memoria pedida para el arreglo de números primos
  free(p);
  return 0;
}
