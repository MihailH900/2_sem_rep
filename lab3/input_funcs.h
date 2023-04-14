#ifndef INPUT_FUNCS_H
#define INPUT_FUNCS_H

#include <stddef.h>
#include "table.h"

typedef enum Input_codes
{
	BAD_INPUT = -2,
	INPUT_ERROR,
	OK
} Input_codes;

char menu(Table* t);
char get_params_for_add(Table* t, unsigned int* key, unsigned int* parent_key, unsigned int* data);
char set_size_t_item_numb(size_t* item, const char* s);
char set_unsigned_item_numb(unsigned int* item, const char* s);
void print_menu();
size_t get_size_t_numb(char* flag);
unsigned int get_unsigned_numb(char* flag);

#endif
