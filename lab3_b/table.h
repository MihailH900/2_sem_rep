#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCK_SIZE 0

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
	
	size_t offset;
} Key;

typedef struct Table
{
	size_t capacity;
	size_t size;

	key_type base_key;

	Key** key_arr;

	FILE* table_file;
	char* file_name;
} Table;

typedef enum Table_codes
{
	TABLE_OK,
	TABLE_ADD_KEY_ERROR,
	TABLE_ADD_PARENT_KEY_ERROR,
	TABLE_ADD_SIZE_ERROR,
	TABLE_FIND_ERROR,
	TABLE_FILE_ERROR,
	TABLE_MEMORY_ERROR
	
} Table_codes;

Table* table_init(size_t capacity, key_type base_key, FILE* f, char* file_name);
char table_get_elements_from_file(Table* t, char* file_name);
char table_load_from_binary_file(Table** t, char* file_name);
char table_create(Table** t, char* file_name, size_t capacity);
char table_save(Table* t);
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
