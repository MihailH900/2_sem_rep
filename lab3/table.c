#include "table.h"

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
		free(t);
		return NULL;
	}

	return t;
}

char table_add(Table* t, key_type* key, key_type* parent_key, variable_type* data)
{
	if (t->size == t->capacity)
	{
		return 2;
	}

	Key** k1_ptr = t->key_arr+t->size-1;
	Key** k2_ptr = t->key_arr+t->size;
	size_t i = t->size-1;
	for (i = t->size-1; i >= 0 && *( (*k1_ptr)->parent_key) > *parent_key; i--, k1_ptr--, k2_ptr--)
	{
		*k2_ptr = *k1_ptr;
	}

	Key* k_ptr = (Key* ) malloc(sizeof(Key));
	if (k_ptr == NULL)
	{
		return 1;
	}

	k_ptr->key = key;
	k_ptr->parent_key = parent_key;
	k_ptr->key_variable = (Item*) malloc(sizeof(Item));
	if (k_ptr->key_variable == NULL)
	{
		return 1;
	}
	k_ptr->key_variable->data = data;

	t->key_arr[i] = k_ptr;

	return 0;
}

char table_delete(Table* t, key_type* key)
{

}

Item* table_search(Table* t, key_type* key)
{
	size_t left = 0, right = t->size-1, m;
	while (left <= right)
	{
		m = (left+right)/2;
		if (t[m]->key == key)
		{
			Item* ans = (Item* ) malloc(sizeof(Item));
			if (ans == NULL)
			{
				return NULL;
			}
			
			ans->data = t[m]->key_variable->data;

			return ans;
		}
	}
}
