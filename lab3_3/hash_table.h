#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

#define MOD 31

typedef struct Item
{
	void* data;
	size_t size;
} Item;

typedef struct Node
{
	size_t release;

	Item* data;

	struct Node* next;

} Node;

typedef struct Key
{
	char busy;
	
	void* key;
	size_t key_size;

	Node* variable_list;
} Key;

typedef struct Hash_table
{
	size_t capacity;
	size_t size;

	Key** key_arr;
} Hash_table;

Hash_table* hash_table_init(size_t capacity);
size_t hash_function(void* data_ptr, size_t size);

#endif
