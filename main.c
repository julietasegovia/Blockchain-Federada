#include "stdlib.h"
#include "stdio.h"
#include "assert.h"
#include "generador_primos.h"
#include "blockchain.h"

int main() {
  /* Genero y muestro los primeros 100 números primos
  int *p = primos(100);
  for(int i = 0; i < 100; i++)
    printf("%d ",p[i]);

    Uso los números primos
  */

  int nro_nodo = 1;

  Blockchain *bc_1 = crear_b();
  Blockchain *bc_2 = crear_b();
  Blockchain *bc_3 = crear_b();

  Federada *fede = crear_f(3);

  insertBlockchain(fede, bc_1);
  insertBlockchain(fede, bc_2);
  insertBlockchain(fede, bc_3);

  char msj1[4] = "hola", msj2[4] = "chau", msj3[3] = "que", msj4[2] = "so";

  alta(fede, &nro_nodo, 0, msj1);
  alta(fede, &nro_nodo, 1, msj2);
  alta(fede, &nro_nodo, 2, msj3);

  assert(validar(fede) == 1);

  actualizar(fede, 1, bc_2->primerN->id, msj4, &nro_nodo);

  assert(strcmp(bc_2->primerN->mensaje, "so") == 0);
  assert(validar(fede) == 1);

  int esperado = fede->hojas[0] * fede->hojas[1];
  assert(validar_subconjunto(fede, esperado, 0, 1) == 1);
  assert(validar_subconjunto(fede, 99999, 0, 1) == 0);

  printf("El arbol se corresponde con el producto de los ids? %i", validar(fede));

  printf("\nEl producto de los ids de los subconjuntos da el valor esperado? %i\n", validar_subconjunto(fede, 14, 0, 1));

  // IMPORTANTE: libero la memoria pedida para el arreglo de números primos
  //free(p);
  return 0;
}
