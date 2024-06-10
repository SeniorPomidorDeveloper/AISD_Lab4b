#include "tree.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

Error_code init_Tree(Node_Tree **tree)
{
    *tree = (Node_Tree *) malloc(sizeof(Node_Tree));
    if (*tree == NULL)
    {
        return ERROR_ALLOCATION;
    }
    (*tree)->parent = NULL;
    for (size_t i = 0; i < 3; ++i)
    {
        (*tree)->keys[i] = NULL;
    }
    for (size_t i = 0; i < 4; ++i)
    {
        (*tree)->childs[i] = NULL;
    }
    return 0;
}

int compare(const char *key1, const char *key2)
{
    return key2 == NULL ? -1 : strcmp(key1, key2);
}

Iter_Tree find_Tree(Node_Tree *tree, const char *key, size_t *index_Node, size_t *index)
{
    Iter_Tree iter = tree;
    if (index_Node != NULL) *index_Node = 0;
    if (index != NULL) *index = 0;
    while (iter != NULL)
    {
        size_t i;
        for (i = 0; i < 3; ++i)
        {
            if (compare(key, iter->keys[i]) <= 0) break;
        }
        if (i < 3) if (compare(key, iter->keys[i]) == 0)
        {
            if (index != NULL) *index = i;
            return iter;
        }
        iter = iter->childs[i];
        if (index_Node != NULL) *index_Node = i;
    }
    return iter;
}

bool is_full_Node(Iter_Tree node)
{
    return node->keys[2] != NULL;
}

void copy_value_Node(Iter_Tree node_1, Iter_Tree node_2, size_t index_1, size_t index_2)
{
    node_1->keys[index_1] = node_2->keys[index_2];
    node_1->info[index_1] = node_2->info[index_2];
}

int split_Tree(Node_Tree **tree, Iter_Tree node)
{
    Iter_Tree parent = node->parent;
    Node_Tree *new_node;
    if (init_Tree(&new_node) == ERROR_ALLOCATION) return ERROR_ALLOCATION;
    new_node->parent = parent;
    copy_value_Node(new_node, node, 0, 2);
    for (size_t i = 2; i < 4; ++i)
    {
        new_node->childs[i - 2] = node->childs[i];
        if (node->childs[i] != NULL) node->childs[i]->parent = new_node;
        node->childs[i] = NULL;
    }
    node->keys[2] = NULL;
    node->info[2] = NULL;
    if (parent != NULL)
    {
        size_t index;
        find_Tree(parent, node->keys[0], &index, NULL);
        for (size_t i = 3; i > index + 1; --i)
        {
            parent->keys[i - 1] = parent->keys[i - 2];
            parent->info[i - 1] = parent->info[i - 2];
        }
        copy_value_Node(parent, node, index, 1);
        node->keys[1] = NULL;
        node->info[1] = NULL;
        for (size_t i = 3; i > index + 1; --i) parent->childs[i] = parent->childs[i - 1];
        parent->childs[index + 1] = new_node;
    }
    else
    {
        if (init_Tree(&parent) == ERROR_ALLOCATION) return ERROR_ALLOCATION;
        parent->parent = NULL;
        copy_value_Node(parent, node, 0, 1);
        parent->childs[0] = node;
        parent->childs[1] = new_node;
        new_node->parent = parent;
        node->parent = parent;
        node->keys[1] = NULL;
        node->info[1] = NULL;
        *tree = parent;
    }
    return SUCCESS;
}

Iter_Tree find_leaf_Tree(Node_Tree **tree, const char *key)
{
    Iter_Tree iter = find_Tree(*tree, key, NULL, NULL);
    if (iter != NULL) return iter;
    iter = *tree;
    Iter_Tree iter_prev = iter;
    while (iter != NULL)
    {
        if (is_full_Node(iter)) 
        {
            if (split_Tree(tree, iter) == ERROR_ALLOCATION) return NULL;
            iter = iter->parent;
        }
        iter_prev = iter;
        size_t i;
        for (i = 0; i < 3 && compare(key, iter->keys[i]) > 0; ++i);
        if (compare(key, iter->keys[i]) == 0) return iter;
        iter = iter->childs[i];
    }
    return iter_prev;
}

int set_value(Iter_Tree node, const char *key, const ULLI info)
{
    for (size_t i = 0; i < 3; ++i)
    {
        int result = compare(key, node->keys[i]);
        if (result < 0)
        {
            for (size_t j = 3; j >= i + 2; --j) 
            {
                node->keys[j - 1] = node->keys[j - 2];
                node->info[j - 1] = node->info[j - 2];
            }
            node->keys[i] = (char *) malloc((strlen(key) + 1) * sizeof(char));
            if (node->keys[i] == NULL) return ERROR_ALLOCATION;
            node->info[i] = (Node_info *) malloc(sizeof(Node_info));
            if (node->info[i] == NULL) return ERROR_ALLOCATION;
            strcpy(node->keys[i], key);
            node->info[i]->info = info;
            node->info[i]->next = NULL;
            break;
        } 
        else if (result == 0)
        {
            Node_info *new_info = (Node_info *) malloc(sizeof(Node_info));
            if (new_info == NULL) return ERROR_ALLOCATION;
            new_info->info = info;
            new_info->next = node->info[i];
            node->info[i] = new_info;
            break;
        }
    }
    return SUCCESS;
}

int add_Tree(Node_Tree **tree, const char *key, const ULLI info, Iter_Tree *iter)
{
    Iter_Tree leaf = find_leaf_Tree(tree, key);
    if (set_value(leaf, key, info) == ERROR_ALLOCATION) return ERROR_ALLOCATION;
    if (iter != NULL) *iter = leaf;
    return SUCCESS;
}

bool is_leaf_Node(Node_Tree *leaf)
{
    return leaf->childs[0] == NULL;
}

void free_info(Node_info *info)
{
    while (info != NULL)
    {
        Node_info *prev = info;
        info = info->next;
        free(prev);
    }
}

bool is_empty_Node_Tree(Node_Tree *node)
{
    return node->keys[0] == NULL;
}

void left_shift_key(Iter_Tree node, size_t index)
{
    for (size_t i = index; i < 3; ++i)
    {
        if (node->keys[i] == NULL) break;
        node->keys[i] = node->keys[i + 1];
        node->info[i] = node->info[i + 1];
    }
    node->keys[2] = NULL;
}

void right_shift_key(Iter_Tree node, size_t index)
{
    for (size_t i = 2; i > index; --i)
    {
        node->keys[i] = node->keys[i - 1];
        node->info[i] = node->info[i - 1];
    }
}

void left_shift_childs(Iter_Tree node, size_t index)
{
    for (size_t i = index; i < 3; ++i)
    {
        if (node->childs[i] == NULL) break;
        node->childs[i] = node->childs[i + 1];
    }
    node->childs[3] = NULL;
}

void right_shift_childs(Iter_Tree node, size_t index)
{
    for (size_t i = 3; i > index; --i)
    {
        node->childs[i] = node->childs[i - 1];
    }
}

size_t find_max_in_Node(Iter_Tree node)
{
    size_t i;
    for (i = 0; i < 3 && node->keys[i] != NULL; ++i);
    return i == 0 ? 0 : i - 1;
}

size_t find_in_Node(const Iter_Tree iter, const Iter_Tree find_iter)
{
    for (size_t i = 0; i < 4; ++i) if (iter->childs[i] == find_iter) return i;
    return 5;
}

int merge(Node_Tree **tree ,Iter_Tree parent, const size_t index_Node, const Side side) // Проверенно!
{
    if (parent == NULL) return IS_ROOT;
    if (parent->childs[index_Node]->keys[1] != NULL) return NO_NEED;
    size_t index_neighbour;

    if (side == LEFT)
    {
        index_neighbour = index_Node - 1;
    }
    else
    {
        index_neighbour = index_Node + 1;
    }
    size_t index_shift_key;
    size_t index_shift_childs;
    if (index_Node > index_neighbour)
    {

        right_shift_key(parent->childs[index_Node], 0);
        right_shift_childs(parent->childs[index_Node], 0);
        copy_value_Node(parent->childs[index_Node], parent, 0, index_neighbour); 
        parent->childs[index_Node]->childs[0] = parent->childs[index_neighbour]->childs[1];
        parent->childs[index_Node]->childs[0]->parent = parent->childs[index_Node];

        right_shift_key(parent->childs[index_Node], 0);
        right_shift_childs(parent->childs[index_Node], 0);
        copy_value_Node(parent->childs[index_Node], parent->childs[index_neighbour], 0, 0); 
        parent->childs[index_Node]->childs[0] = parent->childs[index_neighbour]->childs[0];
        parent->childs[index_Node]->childs[0]->parent = parent->childs[index_Node];

        index_shift_key = index_neighbour;
        index_shift_childs = index_neighbour;
    }
    else
    {
        copy_value_Node(parent->childs[index_Node], parent, 1, index_Node);
        parent->childs[index_Node]->childs[2] = parent->childs[index_neighbour]->childs[0];
        parent->childs[index_Node]->childs[2]->parent = parent->childs[index_Node];

        copy_value_Node(parent->childs[index_Node], parent->childs[index_neighbour], 2, 0);
        parent->childs[index_Node]->childs[3] = parent->childs[index_neighbour]->childs[1];
        parent->childs[index_Node]->childs[3]->parent = parent->childs[index_Node];
        
        index_shift_key = index_Node;
        index_shift_childs = index_neighbour;
    }
    Iter_Tree iter = parent->childs[index_Node];
    free(parent->childs[index_shift_childs]);
    left_shift_key(parent, index_shift_key);
    left_shift_childs(parent, index_shift_childs);
    if (parent->keys[0] == NULL)
    {
        if (parent == *tree)
        {
            *tree = iter;
        }
        iter->parent = parent->parent;
        if (iter->parent != NULL) iter->parent->childs[find_in_Node(iter->parent, parent)] = iter;
        free(parent);
    }
    return MERGED;
}

int moving(Iter_Tree parent, const size_t index_Node, const Side side)  // Проверено!
{
    if (parent == NULL) return IS_ROOT;
    if (parent->childs[index_Node]->keys[1] != NULL) return NO_NEED;
    size_t index_neighbour;
    if (side == LEFT)
    {
        index_neighbour = index_Node - 1;
    }
    else
    {
        index_neighbour = index_Node + 1;
    }
    if (index_Node > index_neighbour)
    {
        size_t index_max_in_neighbour = find_max_in_Node(parent->childs[index_neighbour]);
        right_shift_key(parent->childs[index_Node], 0);
        right_shift_childs(parent->childs[index_Node], 0);
        copy_value_Node(parent->childs[index_Node], parent, 0, index_neighbour);
        copy_value_Node(parent, parent->childs[index_neighbour], index_neighbour, index_max_in_neighbour);
        parent->childs[index_Node]->childs[0] = parent->childs[index_neighbour]->childs[index_max_in_neighbour + 1];
        parent->childs[index_neighbour]->keys[index_max_in_neighbour] = NULL;
        parent->childs[index_neighbour]->info[index_max_in_neighbour] = NULL;
        parent->childs[index_neighbour]->childs[index_max_in_neighbour + 1] = NULL;
    }
    else
    {
        size_t index_max_in_node = find_max_in_Node(parent->childs[index_Node]);
        copy_value_Node(parent->childs[index_Node], parent, index_max_in_node + 1, index_Node);
        copy_value_Node(parent, parent->childs[index_neighbour], index_Node, 0);
        left_shift_key(parent->childs[index_neighbour], 0);
        parent->childs[index_Node]->childs[index_max_in_node + 2] = parent->childs[index_neighbour]->childs[0];
        left_shift_childs(parent->childs[index_neighbour], 0);
    }
    return MOVING;
}

Iter_Tree find_Node_for_del(Node_Tree **tree, Iter_Tree node, char *key, size_t *index_Node, size_t *index)
{
    
    if (index != NULL) *index = 0;
    if (node == NULL) return NULL;
    if (node->keys[1] == NULL && node->parent != NULL)
    {
        bool check = false;
        if (*index_Node > 0) if (node->parent->childs[*index_Node - 1]->keys[1] != NULL)
        {
            check = true;
            moving(node->parent, *index_Node, LEFT);
        }
        if (*index_Node <= 0) if(!check && node->parent->childs[*index_Node + 1]->keys[1] != NULL)
        {
            check = true;
            moving(node->parent, *index_Node, RIGHT);
        }
        if (!check && *index_Node > 0) merge(tree, node->parent, *index_Node, LEFT);
        else if (!check) merge(tree, node->parent, *index_Node, RIGHT);
    }
    size_t i;
    for (i = 0; i < 3; ++i) if (compare(key, node->keys[i]) <= 0) break;
    if (i < 3) if (compare(key, node->keys[i]) == 0)
    {
        if (index != NULL) *index = i;
        return node;
    }
    if (index_Node != NULL) *index_Node = i;
    return find_Node_for_del(tree, node->childs[i], key, index_Node, index);
}

void del_leaf_Node_Tree(Iter_Tree leaf, const size_t index)
{
    free_info(leaf->info[index]);
    free(leaf->keys[index]);
    left_shift_key(leaf, index);
}

Iter_Tree find_max_in_Tree(Node_Tree *tree, size_t *index)
{
    Iter_Tree iter = tree;
    while (iter != NULL)
    {
        *index = find_max_in_Node(iter);
        Iter_Tree next_iter = iter->childs[*index + 1];
        if (next_iter == NULL) return iter;
        iter = next_iter;
    }
    return NULL;
}

Iter_Tree find_min_in_Tree(Node_Tree *tree)
{
    Iter_Tree iter = tree;
    while (iter != NULL)
    {
        if (iter->childs[0] == NULL) return iter;
        iter = iter->childs[0];
    }
    return NULL;
}

void del_no_leaf_Node_Tree(Node_Tree **tree, Iter_Tree node, const size_t index)
{
    bool check = false;
    char *del_key = node->keys[index];
    Node_info *del_info = node->info[index];
    if (node->childs[index]->keys[1] != NULL)
    {
        size_t max_index;
        Iter_Tree max_in_left = find_max_in_Tree(node->childs[index], &max_index);
        if (max_in_left->keys[1] != NULL)
        {
            check = true;
            copy_value_Node(node, max_in_left, index, max_index);
            max_in_left->keys[max_index] = NULL;
        }
    }
    if (!check && node->childs[index + 1]->keys[1] != NULL)
    {
        Iter_Tree min_in_right = find_min_in_Tree(node->childs[index + 1]);
        if (min_in_right->keys[1] != NULL)
        {
            check = true;
            copy_value_Node(node, min_in_right, index, 0);
            left_shift_key(min_in_right, 0);
        }
    }
    if (!check)
    {
        Iter_Tree new_node = node->childs[index];
        merge(tree, node, index, RIGHT);
        del_no_leaf_Node_Tree(tree, new_node, 1);
    }
    else
    {
        free_info(del_info);
        free(del_key);
    }
}

int del_Tree(Node_Tree **tree, char *key)
{
    size_t index_Node, index;
    Iter_Tree iter = find_Node_for_del(tree, *tree, key, &index_Node, &index);
    if (iter == NULL) return NOT_FOUND;
    if (is_leaf_Node(iter)) del_leaf_Node_Tree(iter, index);
    else del_no_leaf_Node_Tree(tree, iter, index);
    return SUCCESS;
}

size_t count_dif(char *key1, char *key2)
{
    bool result = strlen(key1) > strlen(key2);
    char *k_key1 = key1, *k_key2 = key2;;
    if (!result)
    {
        k_key1 = key2;
        k_key2 = key1;
    }
    size_t sum = strlen(k_key1) - strlen(k_key2);
    for (size_t i = 0; i < strlen(k_key2); ++i)
    {
        if (k_key1[i] != k_key2[i]) sum++;
    }
    return sum;
}

Node_Tree *max_dif_Tree(Node_Tree *tree, char *key)
{
    size_t max_index;
    Iter_Tree max_iter = find_max_in_Tree(tree, &max_index);
    size_t max_max_dif = count_dif(key, max_iter->keys[max_index]);
    Iter_Tree min_iter = find_min_in_Tree(tree);
    size_t min_max_dif = count_dif(key, min_iter->keys[0]);
    Node_Tree *answer;
    if (init_Tree(&answer) == ERROR_ALLOCATION) return NULL;
    if (min_max_dif > max_max_dif) copy_value_Node(answer, min_iter, 0, 0);
    else if (max_max_dif > min_max_dif) copy_value_Node(answer, max_iter, 0, max_index);
    else
    {
        copy_value_Node(answer, min_iter, 0, 0);
        copy_value_Node(answer, max_iter, 1, max_index);
    }
    return answer;
}

size_t get_height(Node_Tree *tree)
{
    Iter_Tree iter = tree;
    size_t height = 0;
    while (iter != NULL)
    {
        if (iter->childs[0] == NULL) return height;
        iter = iter->childs[0];
        height++;
    }
    return 0;
}

int n_compare(const char *key1, const char *key2)
{
    return key2 == NULL ? -1 : strncmp(key1, key2, strlen(key1));
}

Error_code bypass(Node_Tree *tree, const char *key)
{
    if (tree == NULL) return SUCCESS;
    size_t i;
    for (i = 0; i < 3; ++i)
    {
        if (compare(key, tree->keys[i]) <= 0) break;
    }
    for (size_t j = i; j <= 3; ++j)
    {
        if (j < 3) if (n_compare(key, tree->keys[j]) == 0)
        {
            printf("%s\n", tree->keys[j]);
        } 
        bypass(tree->childs[j], key);
    }
    return SUCCESS;
}

void free_Tree(Node_Tree *tree)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (tree->childs[i] == NULL) break;
        free_Tree(tree->childs[i]);
    }
    for (size_t i = 0; i < 3; ++i)
    {
        if (tree->keys[i] == NULL) break;
        free(tree->keys[i]);
        free_info(tree->info[i]);
    }
    free(tree);
}