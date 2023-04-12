#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>

typedef unsigned int key_type;
typedef unsigned int variable_type;

typedef struct Key
{
	key_type* key;
	key_type* parent_key;
	
	size_t offset;
} Key;

typedef struct Table
{
	size_t capacity;
	size_t size;

	key_type base_key;

	Key** key_arr;

	FILE* f;
	char* file_name;
} Table;

Table* table_init(size_t capacity, key_type base_key);
Table* table_search_by_parent_key(Table* t, key_type parent_key);
char table_add(Table* t, key_type key, key_type parent_key, variable_type data);
char table_delete_by_key(Table* t, key_type key);
size_t table_search_by_key(Table* t, key_type key);
Item get_elem_with_this_key(Table* t, key_type key);
size_t table_search_first_with_parent_key(Table* t, key_type parent_key);
void table_print(Table* t); // depend on the specific implementation of ehe table
Table* table_init_from_file(char* file_name);
Key* table_elem_alloc(Key* k);
void table_free(Table* t);
void swap(void* a, void* b, size_t size);

#endif
