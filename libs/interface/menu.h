#ifndef MENU_H
#define MENU_H

#include "../error_codes.h"
#include "../tree/tree.h"

int find_menu(Node_Tree **tree);
int add_menu(Node_Tree **tree);
int del_menu(Node_Tree **tree);
int bypass_menu(Node_Tree **tree);

int individual_find_menu(Node_Tree **tree);

int export_menu(Node_Tree **tree);

int main_menu(Node_Tree **tree);

#endif // MENU_H