#ifndef TAREA2_ALGORITMOS_BTREE_H
#define TAREA2_ALGORITMOS_BTREE_H

// B=3 da un arbol 3-4
#define B 3

typedef struct btree_nodo {
  int num_elems;
  int max_elems;
  int *elementos;
  struct btree_nodo **hijos;
} btree;

void btree_nodo_new(struct btree_nodo *btree);

//retorna bool
int btree_search(struct btree_nodo *btree, int clave);
void btree_eliminar(struct btree_nodo *btree, int clave);
struct btree_nodo *btree_insertar(struct btree_nodo *btree, int clave);

void btree_dispose(struct btree_nodo *btree);


#endif //TAREA2_ALGORITMOS_BTREE_H
