#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbst.h"

static int intrand(int low, int high){
  if(high-low <= 0) return 0;
  return (rand()%(high-low)) + low;
}

void rbst_new(rbst *r){
  r->root = NULL;
}

static entry *_rbst_search(struct rbst_node *node, const char *key){
  if (node == NULL) return NULL;

  int cmp = strcmp(key, node->e->key);

  if(cmp == 0) return node->e;
  else if(cmp < 0) return _rbst_search(node->left, key);

  return _rbst_search(node->right, key);
}

entry *rbst_search(rbst *t, const char *key){
  return _rbst_search(t->root, key);
}


static int _nodesize(struct rbst_node *node){
  if (node == NULL) return 0;
  return node->size;
}

static void _fixsize(struct rbst_node *node){
  node->size = _nodesize(node->left) + _nodesize(node->right) + 1;
}

static struct rbst_node *_create_node(const char *key, void *val, int valsize){
  struct rbst_node *n = malloc(sizeof(struct rbst_node));
  n->left = NULL;
  n->right = NULL;
  n->size = 1;
  n->e = malloc(sizeof(entry));

  entry_new(n->e, key, val, valsize);
  return n;
}

static void _split(struct rbst_node *node, const char *key, struct rbst_node **left, struct rbst_node **right){
  if(node == NULL){
    *left = NULL;
    *right = NULL;
    return;
  }

  int cmp = strcmp(key, node->e->key);

  if(cmp < 0){
    *right = node;
    _split(node->left, key, left, &((*right)->left));
  } else {
    *left = node;
    _split(node->right, key, &((*right)->right), left);
  }

  // that's it
}

static struct rbst_node *_insert_root(struct rbst_node *node, const char *key, void *val, int valsize){
  struct rbst_node *left;
  struct rbst_node *right;

  _split(node, key, &left, &right);

  struct rbst_node *new_root = _create_node(key, val, valsize);
  new_root->left = left;
  new_root->right = right;

  return new_root;
}

static struct rbst_node *_rbst_insert(struct rbst_node *node, const char *key, void *val, int valsize){
  int rnd = intrand(0, _nodesize(node));

  if(rnd == _nodesize(node)) return _insert_root(node, key, val, valsize);

  int cmp = strcmp(key, node->e->key);
  if(cmp == 0){
    entry_replace_val(node->e, val, valsize);
    return node;
  }

  if(cmp < 0) node->left = _rbst_insert(node->left, key, val, valsize);
  else node->right = _rbst_insert(node->right, key, val, valsize);

  _fixsize(node);

  return node;
}


void rbst_insert(rbst *t, const char *key, void *val, int valsize){
  t->root = _rbst_insert(t->root, key, val, valsize);
}
