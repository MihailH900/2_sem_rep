#ifndef INPUT_FUNCS_H
#define INPUT_FUNCS_H

#include <stddef.h>
#include "table.h"

char menu(Table* t);
void print_menu();
char get_params_for_add(unsigned int* key, unsigned int* parent_key, unsigned int* data);
char set_item_numb(unsigned int* item, const char* s);
size_t get_numb_greater_zero(char* flag);

#endif
