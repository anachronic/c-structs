#ifndef _RBST_H_
#define _RBST_H_

#include "entry.h"

typedef struct {
  struct rbst_node *root;
} rbst;

struct rbst_node
{
  entry *e;
  struct rbst_node *left;
  struct rbst_node *right;
  int size;
};

void rbst_new(rbst *t);
void rbst_insert(rbst *t, const char *key, void *val, int valsize);
entry *rbst_search(rbst *t, const char *key);
void rbst_delete(rbst *t, const char *key);
void rbst_dispose(rbst *t);


#endif // _RBST_H_
