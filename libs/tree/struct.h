#ifndef STRUCT_H
#define STRUCT_H

#include <stddef.h>
#include <stdbool.h>

#define ULLI unsigned long long int

typedef struct Node_info
{
    ULLI info;
    struct Node_info *next;
} Node_info;

typedef struct Node_Tree // Структура узла бинарного дерева
{
    char *keys[3]; // - Ключи
    Node_info *info[3]; // - Указатель на хранимую информацию
    struct Node_Tree *childs[4]; // - Указатели на дочерние элементы
    struct Node_Tree *parent;
} Node_Tree;

typedef Node_Tree * Iter_Tree; // Итератор, указывающий на узел бинарного дерева

typedef struct Iter_Tree_arr // Структура, содержащая информацию элемента дерева
{
    size_t len;
    Iter_Tree *arr;
} Iter_Tree_arr;

#endif // STRUCT_H