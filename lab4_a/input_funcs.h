#ifndef INPUT_FUNCS_H
#define INPUT_FUNCS_H

#include "BST.h"
#include "parse_input.h"

char menu(BST* tree);
void print_menu();
char get_params_for_add(BST* tree, unsigned int* key, unsigned int* data);

#endif
