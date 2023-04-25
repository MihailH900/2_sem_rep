#ifndef PARSE_INPUT_H
#define PARSE_INPUT_H

#include <stddef.h>

typedef enum Input_codes
{
	BAD_INPUT = -2,
	INPUT_ERROR,
	OK
} Input_codes;

char set_size_t_item_numb(size_t* item, const char* s);
char set_unsigned_item_numb(unsigned int* item, const char* s);
size_t get_size_t_numb(char* flag);
unsigned int get_unsigned_numb(char* flag);
char* readline(char* in);

#endif
