#include "hash_table.h"
#include <stdlib.h>

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
	}

	return h;
}

char hash_table_add(Hash_table* h, void* key, size_t key_size, void* data, size_t data_size)
{

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
