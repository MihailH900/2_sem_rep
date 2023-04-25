#ifndef INPUT_FUNCS_H
#define INPUT_FUNCS_H

#include "table.h"
#include "parse_input.h"

char menu(Table** t);
void print_menu();
Table* table_load();
char get_params_for_add(Table* t, unsigned int* key, unsigned int* parent_key, unsigned int* data);

#endif
