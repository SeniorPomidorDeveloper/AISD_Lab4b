#include "visualization.h"

#include <stdio.h>

void consol_print_tree(Node_Tree *tree, const size_t level)
{
    if (tree == NULL)
        return;   
    consol_print_tree(tree->childs[3], level + 1);
    consol_print_tree(tree->childs[2], level + 1);
    for (size_t i = 0; i < 9 + 10 * level; ++i) printf(" ");
    for (size_t i = 0; i < 3 && tree->keys[i] != NULL; ++i) printf(" %s", tree->keys[i]);
    printf("\n");
    consol_print_tree(tree->childs[1], level + 1);
    consol_print_tree(tree->childs[0], level + 1);
}