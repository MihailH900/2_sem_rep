#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>

typedef unsigned int key_type;
typedef unsigned variable_type;

typedef struct Item
{
	variable_type* data;
	//Key** key_of_variable;
} Item;

typedef struct Key
{
	key_type* key;
	key_type* parent_key;

	Item* variable;
} Key;

typedef struct Table
{
	size_t capacity;
	size_t size;

	Key** key_arr;
} Table;

Table* table_init(size_t capacity);
char table_add(Table* t, key_type key, key_type parent_key, variable_type data);
char table_delete_by_key(Table* t, key_type key);
size_t table_search_by_key(Table* t, key_type key);
size_t table_search_by_parent_key(Table* t, key_type parent_key);
size_t table_search_first_with_parent_key(Table* t, key_type parent_key);
void table_print(Table* t); // depend on the specific implementation of the table
Table* table_init_from_file(char* file_name);
Key* table_elem_alloc(Key* k);

#endif
