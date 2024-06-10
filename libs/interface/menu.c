#include "menu.h"

#include <stdlib.h>
#include <stdio.h>

#include "./libs/gets/gets.h"
#include "./libs/input/input.h"
#include "./libs/visualization/visualization.h"
#include "../export/export.h"

int find_menu(Node_Tree **tree)
{
    char *key;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&key, "\t> Введите ключ элемента, который хотите найти: ") == EOF) return EOF;
    size_t index;
    Iter_Tree iter = find_Tree(*tree, key, NULL, &index);
    if (iter == NULL)
    {
        printf("\t> Элемент с ключом %s не найден.\n", key);
        free(key);
        return NOT_FOUND;
    }
    else 
    {
        Node_info *node = iter->info[index];
        printf("\t> tree[%s] = %llu", key, node->info);
        node = node->next;
        while (node != NULL)
        {
            printf(" -> %llu", node->info);
            node = node->next;
        }
        printf("\n");
    }
    free(key);
    return SUCCESS;
}

int add_menu(Node_Tree **tree)
{
    char *key;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&key, "\t> Введите ключ: ") == EOF) return EOF;
    long long int info;
    if (GetLLInt(&info, "Введите хранимую информацию: ", check_no_negative) == EOF)
    {
        free(key);
        return EOF;
    }
    int result = add_Tree(tree, key, info, NULL);
    free(key);
    return result; 
}

int del_menu(Node_Tree **tree)
{
    char *key;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&key, "\t> Введите ключ: ") == EOF) return EOF;
    int result = del_Tree(tree, key);
    if (result == NOT_FOUND) 
    {
        printf("\t> Элемент с ключом %s не найден.\n", key);
        free(key);
        return SUCCESS;
    }
    free(key);
    return result; 
}

int bypass_menu(Node_Tree **tree)
{
    char *key;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&key, "\t> Введите ключ: ") == EOF) return EOF;
    bypass(*tree, key);
    free(key);
    return SUCCESS;
}

int individual_find_menu(Node_Tree **tree)
{
    char *key;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&key, "\t> Введите ключ: ") == EOF) return EOF;
    Node_Tree *result = max_dif_Tree(*tree, key);
    if (result == NULL)
    {
        printf("\t> Дерево пусте!\n");
    }
    else
    {
        printf("Ответ:");
        for (size_t i = 0; i < 2; i++)
        {
            printf(" %s", result->keys[i]);
        }
        printf("\n");
        free(result);
    }
    free(key);
    return SUCCESS;
}

int export_menu(Node_Tree **tree)
{
    char *path;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&path, "\t> Введите путь до файла: ") == EOF) return EOF;
    int result = export_graph(*tree, path);
    free(path);
    if (result != SUCCESS) printf("\t[ERROR] Запись завершилась ошибкой!\n");
    else printf("\tЗапись завершилась успешно.\n");
    return result;
}

void output_tree(Node_Tree **tree)
{
    consol_print_tree(*tree, 0);
}

bool check_option(const long long int option)
{
    return option >= 0 && option <= 6;
}

bool check_result_menu(const int result)
{
    return result == SUCCESS || result == NOT_FOUND || result == FOUND;
}

void print_menu()
{
    printf("1. Найти узел\n");
    printf("2. Добавить узел\n");
    printf("3. Удаление узла\n");
    printf("4. Обход дерева\n");
    printf("5. Специальный поиск\n");
    printf("6. Экспорт дерева для Graphviz\n");
    printf("0. Выход\n");
}

int main_menu(Node_Tree **tree)
{
    long long int option;
    int (*function[]) (Node_Tree **tree) = {find_menu, add_menu, del_menu, bypass_menu, individual_find_menu, export_menu};
    do 
    {
        output_tree(tree);
        print_menu();
        if (GetLLInt(&option, "Введите пункт меню: ", check_option) == EOF) return EOF; 
        if (option == 0) break;
        int result = function[option - 1](tree);
        if (!check_result_menu(result)) return result;
    } while (option != 0);
    return SUCCESS;
}