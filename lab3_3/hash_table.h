#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

#define MOD 31

typedef struct Item
{
	void* data_ptr;
	size_t data_size;
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
	
	void* key_ptr;
	size_t key_size;

	Node* variables_list;
} Key;

typedef struct Hash_table
{
	size_t capacity;
	size_t size;

	Key** key_arr;
} Hash_table;

typedef enum Hash_table_elem_states
{
	DELETED = -1,
	FREE,
	BUSY
} Hash_table_elem_states;

typedef enum Hash_table_codes
{
	HASH_TABLE_OK,
	HASH_TABLE_MEMORY_ERROR,
	HASH_TABLE_ADD_SIZE_ERROR,
	HASH_TABLE_FIND_ERROR
} Table_codes;

Hash_table* hash_table_init(size_t capacity);
char hash_table_add(Hash_table* h, void* key, size_t key_size, void* data, size_t data_size, size_t version);
size_t add_hash(size_t hash, size_t add_val);
size_t hash_function(void* data_ptr, size_t size);
Node* malloc_node();
char check_equal(void* a, void* b, size_t size);
size_t min(size_t a, size_t b);

#endif
