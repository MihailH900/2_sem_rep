#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>

typedef unsigned int key_type;
typedef unsigned int variable_type;

typedef struct Item
{
	variable_type* data;
} Item;

typedef struct Key
{
	key_type* key;
	key_type* parent_key;

	Item* key_variable;
} Key;

typedef struct Table
{
	size_t capacity;
	size_t size;

	Key** key_arr;
} Table;

Table* table_init(size_t capacity);
char table_add(Table* t, key_type* key, key_type* parent_key, variable_type* data);
char table_delete(Table* t, key_type* key);
Item* table_search(Table* t, key_type* key);
void table_print(Table* t); // depend on the specific implementation of the table
Table* table_init_from_file(char* file_name);
Table* table_search_by_parent_key(Table* t, key_type* parent_key);

#endif
