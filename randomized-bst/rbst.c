#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "rbst.h"


void rbst_new(rbst *r)
{
  r->root = NULL;
}

entry *_rbst_search(struct rbst_node *node, const char *key){
  if (node == NULL) return NULL;

  int cmp = strcmp(key, node->e->key);

  if(cmp == 0) return node->e;
  else if(cmp < 0) return _rbst_search(node->left, key);

  return _rbst_search(node->right, key);
}

entry *rbst_search(rbst *t, const char *key){
  return _rbst_search(t->root, key);
}
