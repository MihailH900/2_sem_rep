#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

		(*k)->key_ptr = NULL;

		(*k)->variables_list = (List*) malloc(sizeof(List));
		if ( (*k)->variables_list == NULL)
		{
			return NULL;
		}

		(*k)->variables_list->head = NULL;
	}

	return h;
}

char hash_table_add(Hash_table* h, void* key_ptr, size_t key_size, void* data_ptr, size_t data_size)
{
	size_t elem_hash = hash_function(key_ptr, key_size) % h->capacity;
	if (h->key_arr[elem_hash]->variables_list->head != NULL)
	{
		size_t i = 0;

		if (h->key_arr[elem_hash]->key_size != key_size || check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) )
		{
			while (i < h->capacity)
			{
				elem_hash = add_hash(elem_hash, h->capacity) % h->capacity;
				
				if (h->key_arr[elem_hash]->key_ptr == NULL)
				{
					break;
				}

				if (h->key_arr[elem_hash]->key_size == key_size && check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) == 0 )
				{
					break;
				}

				i++;
			}
		}

		if (i < h->capacity)
		{

			h->key_arr[elem_hash]->key_ptr = malloc(key_size);
			if (h->key_arr[elem_hash]->key_ptr == NULL)
			{
				return HASH_TABLE_MEMORY_ERROR;
			}
			memcpy(h->key_arr[elem_hash]->key_ptr, key_ptr, key_size);
			h->key_arr[elem_hash]->key_size = key_size;

			h->size++;
			
			return add_node_in_list_of_hash_table(h, elem_hash, data_ptr, data_size);
		}

		return HASH_TABLE_ADD_SIZE_ERROR;
	}
	else
	{
		h->key_arr[elem_hash]->key_ptr = malloc(key_size);
		if (h->key_arr[elem_hash]->key_ptr == NULL)
		{
			return HASH_TABLE_MEMORY_ERROR;
		}
		memcpy(h->key_arr[elem_hash]->key_ptr, key_ptr, key_size);
		h->key_arr[elem_hash]->key_size = key_size;


		h->size++;
		return add_node_in_list_of_hash_table(h, elem_hash, data_ptr, data_size);
	}
}

char hash_table_search(Hash_table* h, void* key_ptr, size_t key_size, Hash_table* ans)
{
	size_t elem_hash = hash_function(key_ptr, key_size) % h->capacity;
	
	if (h->key_arr[elem_hash]->variables_list->head != NULL)
	{
		size_t i = 0;
		if (h->key_arr[elem_hash]->key_size != key_size || check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) )
		{
			while (i < h->capacity)
			{
				elem_hash = add_hash(elem_hash, h->capacity) % h->capacity;
				
				if (h->key_arr[elem_hash]->key_ptr == NULL)
				{
					continue;
				}

				if (h->key_arr[elem_hash]->key_size != key_size || check_equal(h->key_arr[elem_hash]->key_ptr, key_ptr, min(h->key_arr[elem_hash]->key_size, key_size) ) )
				{
					break;
				}

				i++;
			}
		}

		if (i < h->capacity)
		{

			Node* n_1 = h->key_arr[elem_hash]->variables_list->head;
			char flag;
			while (n_1 != NULL)
			{
				flag = hash_table_add(ans, key_ptr, key_size, n_1->data->data_ptr, n_1->data->data_size);

				if (flag == HASH_TABLE_MEMORY_ERROR)
				{
					return flag;
				}

				n_1 = n_1->next;
			}

			return HASH_TABLE_OK;
			
		}

		return HASH_TABLE_FIND_ERROR;
	}
	else
	{
		return HASH_TABLE_FIND_ERROR;
	}
}

void hash_table_print(Hash_table* h)
{
	printf("Hash table size: %zu\nHash table capacity: %zu\n", h->size, h->capacity);

	Key** k = h->key_arr;
	printf("\n");
	for (size_t i = 0; i < h->capacity; i++, k++)
	{
		if ( (*k)->key_ptr == NULL)
		{
			printf("Key: NULL\n");
		}
		else
		{
			printf("Key: %s\n", (char*)(*k)->key_ptr);
		}

		if ( (*k)->variables_list->head == NULL)
		{
			printf("Variables: NULL\n");
		}
		else
		{
			printf("Variables:\n");
			Node* n = (*k)->variables_list->head;
			while (n != NULL)
			{
				printf("Data: %s, release: %zu\n", (char*)n->data->data_ptr, n->release);
				n = n->next;
			}
		}
	}
}

void hash_table_free(Hash_table* h)
{
	Key** k = h->key_arr;
	for (size_t i = 0; i < h->capacity; i++, k++)
	{
		if ( (*k)->variables_list->head != NULL)
		{
			Node* n = (*k)->variables_list->head;
			while ( (*k)->variables_list->head != NULL)
			{
				(*k)->variables_list->head = (*k)->variables_list->head->next;
				free(n->data->data_ptr);
				free(n->data);
				free(n);
				n = (*k)->variables_list->head;
			}
		}

		free( (*k)->variables_list);

		if ( (*k)->key_ptr != NULL)
		{
			free( (*k)->key_ptr);
		}

		free( (*k));
	}

	free(h->key_arr);
	free(h);
}

char add_node_in_list_of_hash_table(Hash_table* h, size_t elem_hash, void* data_ptr, size_t data_size)
{
	Node* n = malloc_node();
	if (n == NULL)
	{
		return HASH_TABLE_MEMORY_ERROR;
	}

	if (h->key_arr[elem_hash]->variables_list->head == NULL)
	{
		n->release = 1;
	}
	else
	{
		n->release = h->key_arr[elem_hash]->variables_list->head->release+1;
	}

	n->data->data_ptr = malloc(data_size);
	if (n->data->data_ptr == NULL)
	{
		return HASH_TABLE_MEMORY_ERROR;
	}
	memcpy(n->data->data_ptr, data_ptr, data_size);
	n->data->data_size = data_size;
	
	n->next = h->key_arr[elem_hash]->variables_list->head;
	h->key_arr[elem_hash]->variables_list->head = n;

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
