#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rbst.h"


void rbst_new(rbst *r)
{
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

// We're gonna use splay tree notation, where zig is a clockwise rotation
// and zag is counterclockwise rotation. Its kind of a no-brainer, but you
// can read about it @ http://kukuruku.co/hub/cpp/randomized-binary-search-trees
static struct rbst_node *_zig(struct rbst_node *node){
  struct rbst_node *new_root = node->left;

  if(new_root == NULL) return node;
  node->left = new_root->right;
  new_root->right = node;
  new_root->size = node->size;

  _fixsize(node);
  return new_root;
}

static struct rbst_node *_zag(struct rbst_node *node){
  struct rbst_node *new_root = node->right;

  node->right = new_root->left;
  new_root->left = node;
  new_root->size = node->size;

  _fixsize(node);
  return new_root;
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

static struct rbst_node *_bst_insert(struct rbst_node *node, const char *key, void *val, int valsize){
  if (node == NULL) return _create_node(key, val, valsize);

  int cmp = strcmp(key, node->e->key);
  if(cmp == 0){
    entry_replace_val(node->e, val, valsize);
    return node;
  }

  if(cmp < 0) node->left = _bst_insert(node->left, key, val, valsize);
  else node->right = _bst_insert(node->right, key, val, valsize);

  return node;
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
}

static struct rbst_node *_insert_root(struct rbst_node *node, const char *key, void *val, int valsize){
  if (node == NULL) return _create_node(key, val, valsize);

  
}

