#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

Hash_table* hash_table_init(size_t capacity)
{
	Hash_table* h = (Hash_table* ) malloc(sizeof(Hash_table));
	if (h == NULL)
	{
		return NULL;
	}

	h->capacity = capacity;
	h->size = 0;

	h->key_arr = (Key** ) malloc(capacity * sizeof(Key*));
	if (h->key_arr == NULL)
	{
		return NULL;
	}
	
	Key** k = h->key_arr;
	for (size_t i = 0; i < h->capacity; i++, k++)
	{
		(*k) = (Key* ) malloc(sizeof(Key));
		if ( (*k) == NULL)
		{
			return NULL;
		}

		(*k)->busy = 0;
		(*k)->variables_list = NULL;
	}

	return h;
}

char hash_table_add(Hash_table* h, void* key_ptr, size_t key_size, void* data_ptr, size_t data_size, size_t version)
{
	size_t elem_hash = hash_function(key_ptr, key_size) % h->capacity;
	if (h->key_arr[elem_hash]->busy == 1)
	{
		if (h->key_arr[elem_hash]->key_size != key_size || check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) )
		{
			size_t i = 0;
			
			while ( (h->key_arr[elem_hash]->key_size != key_size || check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) ) && i < h->capacity )
			{
				elem_hash = add_hash(elem_hash, h->capacity) % h->capacity;
				i++;
			}

			if (i < h->capacity)
			{
				return add_node_in_list_of_hash_table(h, elem_hash, data_ptr, data_size);
			}

			return HASH_TABLE_ADD_SIZE_ERROR;
		}
		else
		{
			return add_node_in_list_of_hash_table(h, elem_hash, data_ptr, data_size);
		}
	}
	else
	{
		h->key_arr[elem_hash]->busy = 1;

		h->key_arr[elem_hash]->key_ptr = malloc(key_size);
		if (h->key_arr[elem_hash]->key_ptr == NULL)
		{
			return HASH_TABLE_MEMORY_ERROR;
		}
		memcpy(h->key_arr[elem_hash]->key_ptr, key_ptr, key_size);
		h->key_arr[elem_hash]->key_size = key_size;


		return add_node_in_list_of_hash_table(h, elem_hash, data_ptr, data_size);
	}
}

Node* hash_table_search(Hash_table* h, void* key_ptr, size_t key_size)
{
	Node* ans = (Node*) malloc(sizeof(Node));

	size_t elem_hash = hash_function(key_ptr, key_size) % h->capacity;
	
	if (h->key_arr[elem_hash]->busy == 1)
	{
		if (h->key_arr[elem_hash]->key_size != key_size || check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) )
		{

		}
		else
		{

		}
	}
	else
	{

	}
}

char add_node_in_list_of_hash_table(Hash_table* h, size_t elem_hash, void* data_ptr, size_t data_size)
{
	Node* n = malloc_node();
	if (n == NULL)
	{
		return HASH_TABLE_MEMORY_ERROR;
	}

	n->release = h->key_arr[elem_hash]->variables_list->release+1;
			
	n->data->data_ptr = malloc(data_size);
	if (n->data->data_ptr == NULL)
	{
		return HASH_TABLE_MEMORY_ERROR;
	}
	memcpy(n->data->data_ptr, data_ptr, data_size);
	
	n->next = h->key_arr[elem_hash]->variables_list;
	h->key_arr[elem_hash]->variables_list = n;

	return HASH_TABLE_OK;
}

size_t add_hash(size_t hash, size_t add_val)
{
	return (hash + (add_val -1 ) );
}

size_t hash_function(void* data_ptr, size_t size)
{
	char* byte = data_ptr;
	size_t res = 0, m = 1;
	size_t i = 0;

	while (i < size)
	{
		res += m * (*byte);
		m = m * MOD;
		i++;
	}

	return res;
}

Node* malloc_node()
{
	Node* n = (Node*) malloc(sizeof(Node));
	if (n == NULL)
	{
		return NULL;
	}

	n->data = (Item*) malloc(sizeof(Item));
	if (n->data == NULL)
	{
		return NULL;
	}

	return n;
}

char check_equal(void* a, void* b, size_t size)
{
	char* a_byte = a;
	char* b_byte = b;

	size_t i = 0;
	while (i < size)
	{
		if ( (*a_byte) != (*b_byte) )
		{
			return 1;
		}

		a_byte++;
		b_byte++;
		i++;
	}

	return 0;
}

size_t min(size_t a, size_t b)
{
	if (a > b)
	{
		return b;
	}
	return a;
}
