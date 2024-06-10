#ifndef TREE_H
#define TREE_H

#include "../error_codes.h"

#include "struct.h"
#include "Instructions.h"

Error_code init_Tree(Node_Tree **tree);

void free_info(Node_info *info);

size_t get_height(Node_Tree *tree);
Iter_Tree find_Tree(Node_Tree *tree, const char *key, size_t *index_Node, size_t *index);
int add_Tree(Node_Tree **tree, const char *key, const ULLI info, Iter_Tree *iter);
int del_Tree(Node_Tree **tree, char *key);

Error_code bypass(Node_Tree *tree, const char *key);
Node_Tree *max_dif_Tree(Node_Tree *tree, char *key);

void free_Tree(Node_Tree *tree);

#endif // BIN_TREE_H