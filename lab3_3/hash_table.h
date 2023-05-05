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

typedef struct List
{
	Node* head;
} List;

typedef struct Key
{
	void* key_ptr;
	size_t key_size;

	List* variables_list;
} Key;

typedef struct Hash_table
{
	size_t capacity;
	size_t size;

	Key** key_arr;
} Hash_table;

typedef enum Hash_table_codes
{
	HASH_TABLE_OK,
	HASH_TABLE_MEMORY_ERROR,
	HASH_TABLE_ADD_SIZE_ERROR,
	HASH_TABLE_FIND_ERROR
} Table_codes;

Hash_table* hash_table_init(size_t capacity);
char hash_table_add(Hash_table* h, void* key, size_t key_size, void* data, size_t data_size);
char hash_table_search(Hash_table* h, void* key_ptr, size_t key_size, Hash_table* ans);
void hash_table_free(Hash_table* h);
char add_node_in_list_of_hash_table(Hash_table* h, size_t elem_hash, void* data_ptr, size_t data_size);
void hash_table_print(Hash_table* h);
size_t add_hash(size_t hash, size_t add_val);
size_t hash_function(void* data_ptr, size_t size);
Node* malloc_node();
char check_equal(void* a, void* b, size_t size);
size_t min(size_t a, size_t b);

#endif
