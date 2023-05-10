#ifndef INPUT_FUNCS_H
#define INPUT_FUNCS_H

#include "B_tree.h"
#include "parse_input.h"

char menu(B_tree* tree);
void print_menu();
char get_params_for_add(B_tree* tree, Key* k, Data* d);

#endif
