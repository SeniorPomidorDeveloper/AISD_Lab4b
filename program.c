#include "program.h"

#include <stdio.h>
#include <stdlib.h>

#include "./libs/tree/tree.h"
#include "./libs/interface/menu.h"
#include "./libs/import/import.h"
#include "./libs/interface/libs/input/input.h"
#include "./libs/interface/libs/gets/gets.h"

int import_menu(Node_Tree **tree)
{
    char *path;
    char symbol;
    do 
    {
        symbol = fgetc(stdin);
        if (symbol == EOF) return EOF;
    } while (symbol != '\n');
    if (input(&path, "\t> Введите путь до файла: ") == EOF) return EOF;
    int result = import_tree(tree, path);
    free(path);
    if (result > WARNING_FILE_READ) return result;
    else if (result == WARNING_FILE_READ) printf("[WARNING] Файл был считан не до конца!");
    return SUCCESS;
}

int new_tree_menu(Node_Tree **tree)
{
    return init_Tree(tree);
}

bool check_option_input_menu(const long long int num)
{
    return num > 0 && num <= 2;
}

bool check_result_input_menu(const int result)
{
    return result <= WARNING_FILE_READ;
}

void print_input_menu()
{
    printf("1. Импортировать дерево из текстового файла\n");
    printf("2. Создать новое дерево\n");
}

int input_tree(Node_Tree **tree)
{
    long long int option;
    int (*function[]) (Node_Tree **table) = {import_menu, new_tree_menu};
    print_input_menu();
    if (GetLLInt(&option, "Введите пункт меню: ", check_option_input_menu) == EOF) return EOF; 
    int result = function[option - 1](tree);
    if (!check_result_input_menu(result)) return result;
    return SUCCESS;
}

int program()
{
    Node_Tree *tree;
    int result = input_tree(&tree);
    if (result > WARNING_FILE_READ || result == EOF) return result;
    result = main_menu(&tree);
    if (result != SUCCESS)
    { 
        free_Tree(tree);
        return result;
    } 
    free_Tree(tree);
    return SUCCESS;
}