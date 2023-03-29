#include "table.h"
#include <stdio.h>

Table* table_init(size_t capacity)
{
	Table* t = (Table* ) malloc(sizeof(Table));
	if (t == NULL)
	{
		return NULL;
	}

	t->capacity = capacity;
	t->size = 0;

	t->key_arr = (Key** ) malloc(capacity * sizeof(Key*));
	if (t->key_arr == NULL)
	{
		return NULL;
	}

	Key** k = t->key_arr;
	for (size_t i = 0; i < t->capacity; i++, k++)
	{
		(*k) = table_elem_alloc( (*k) );
		if ( (*k) == NULL)
		{
			return NULL;
		}
	}

	return t;
}

char table_add(Table* t, key_type key, key_type parent_key, variable_type data)
{
	if (table_search_by_key(t, key) != -1)
	{
		return 2;
	}

	if (table_search_by_key(t, parent_key) == -1 && parent_key != 0)
	{
		return 2;
	}

	if (t->size == t->capacity)
	{
		return 2;
	}

	Key** k1_ptr = t->key_arr+t->size-1;
	Key** k2_ptr = t->key_arr+t->size;
	size_t i = t->size-1;
	if (t->size >= 1)
	{
		for (i = t->size; i >= 0 && *( (*k1_ptr)->parent_key) > parent_key; i--, k1_ptr--, k2_ptr--)
		{
			printf("ASD\n");
			*(k2_ptr) = *(k1_ptr);
		}
	}

	if (i == -1)
	{
		i = 0;
	}

	*(t->key_arr[i]->key) = key;
	*(t->key_arr[i]->parent_key) = parent_key;
	*(t->key_arr[i]->variable->data) = data;
	t->size++;

	return 0;
}

char table_delete_by_key(Table* t, key_type key)
{
	size_t i;
	if ( (i = table_search_by_key(t, key)) == -1)
	{
		return 2;
	}


	Key** k1_ptr = t->key_arr + i;
	Key** k2_ptr = t->key_arr + i + 1;
	for (; i < t->size-1; i++, k1_ptr++, k2_ptr++)
	{
		*(k2_ptr) = *(k1_ptr);
	}

	t->size--;

	i = table_search_first_with_parent_key(t, key);
	k1_ptr = t->key_arr + i;
	while ( *( (*k1_ptr)->parent_key ) == key)
	{
		*( (*k1_ptr)->parent_key ) = 0;
		k1_ptr++;
	}

	return 0;
}

size_t table_search_by_key(Table* t, key_type key)
{
	Key** k = t->key_arr;
	for (size_t i = 0; i < t->size; i++, k++)
	{
		if ( *( (*k)->key) == key)
		{
			return i;
		}
	}

	return -1;
}

size_t table_search_by_parent_key(Table* t, key_type parent_key)
{
	
}

size_t table_search_first_with_parent_key(Table* t, key_type parent_key)
{
	size_t left = 0, right = t->size-1, mid;
	while (right - left > 1)
	{
		mid = (left+right)/2;
		if ( *(t->key_arr[mid]->parent_key) >= parent_key)
		{
			right = mid;
		}
		else
		{
			left = mid;
		}
	}

	return right;
}

void table_print(Table* t)
{
	Key** k = t->key_arr;
	printf("Table size: %d\n", t->size);
	for (int i = 0; i < t->size; i++, k++)
	{
		printf("Key - %u, parent_key - %u, data - %u\n", *( (*k)->key ), *( (*k)->parent_key ), *( (*k)->variable->data ) );
	}
}

void table_free(Table* t)
{
	Key** k = t->key_arr;
	for (size_t i = 0; i < t->capacity; i++, k++)
	{
		free( (*k)->variable->data );
		free( (*k)->variable );
		free( (*k)->key );
		free( (*k)->parent_key );
		free( (*k) );
	}

	free(t->key_arr);
	free(t);
}

Key* table_elem_alloc(Key* k)
{
	k = (Key* ) malloc(sizeof(Key));
	if (k == NULL)
	{
		return NULL;
	}

	k->key = (key_type* ) malloc(sizeof(key_type));
	if (k->key == NULL)
	{
		return NULL;
	}

	k->parent_key = (key_type* ) malloc(sizeof(key_type));
	if (k->parent_key == NULL)
	{
		return NULL;
	}

	k->variable = (Item* ) malloc(sizeof(Item));
	if (k->variable == NULL)
	{
		return NULL;
	}

	k->variable->data = (variable_type* ) malloc(sizeof(variable_type));
	if (k->variable->data == NULL)
	{
		return NULL;
	}

	return k;
}
