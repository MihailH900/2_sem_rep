#include "table.h"
#include <stdio.h>
#include <string.h>

Table* table_init(size_t capacity, key_type base_key, FILE* table_file, char* file_name)
{
	Table* t = (Table* ) malloc(sizeof(Table));
	if (t == NULL)
	{
		return NULL;
	}

	t->capacity = capacity;
	t->size = 0;
	t->base_key = base_key;

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
	
	t->table_file = table_file;
	t->file_name = strdup(file_name);
	if (t->file_name == NULL)
	{
		return NULL;
	}

	return t;
}

Table* table_load_from_binary_file(char* file_name)
{
	FILE* f = fopen(file_name, "r+b");
	if (f == NULL)
	{
		return NULL;
	}
	
	size_t capacity;
	fread(&capacity, sizeof(size_t), 1, f);
	size_t size;
	fread(&size, sizeof(size_t), 1, f);
	
	Table* t = table_init(capacity, 0, f, file_name);
	if (t == NULL)
	{
		return NULL;
	}
	
	Key** k = t->key_arr;
	for (size_t i = 0; i < size; i++, k++)
	{
		fread( ( *(t->key_arr) )->key, sizeof(key_type), 1, t->table_file);
		fread( ( *(t->key_arr) )->parent_key, sizeof(key_type), 1, t->table_file);
	}
	
	return t;
}

Table* create_new_table(char* file_name, size_t capacity)
{
	FILE* f = fopen(file_name, "w+b");
	if (f == NULL)
	{
		return NULL;	
	}
	
	Table* t = table_init(capacity, 0, f, file_name);
	if (t == NULL)
	{
		return NULL;
	}
	
	fseek(t->table_file, 0, SEEK_SET);
	
	fwrite(&(t->size), sizeof(size_t), 1, t->table_file);
        fwrite(&(t->capacity), sizeof(size_t), 1, t->table_file);
        
        Key** k = t->key_arr;
	for (size_t i = 0; i < t->size; i++, k++)
	{
		fread( ( *(t->key_arr) )->key, sizeof(key_type), 1, t->table_file);
		fread( ( *(t->key_arr) )->parent_key, sizeof(key_type), 1, t->table_file);
	}
        
        return t;
}

/*
Table* table_search_by_parent_key(Table* t, key_type parent_key)
{
	size_t ans_size = 0;
	size_t ind = table_search_first_with_parent_key(t, parent_key);

	if (ind == -1)
	{
		Table* ans = table_init(ans_size, parent_key, NULL, NULL);
		return ans;
	}
	
	Key** k = t->key_arr+ind;
	size_t i = ind;
	while ( (i < t->size) && ( *( (*k)->parent_key ) == parent_key) )
	{
		ans_size++;
		k++;
		i++;
	}

	Table* ans = table_init(ans_size, parent_key, NULL, NULL);
	k = t->key_arr+ind;
	i = ind;
	while ( (i < t->size) && ( *( (*k)->parent_key ) == parent_key ) )
	{
		table_add(ans, *( (*k)->key ), *( (*k)->parent_key ), *( (*k)->variable->data ) );
		k++;
		i++;
	}

	return ans;
}


char table_add(Table* t, key_type key, key_type parent_key, variable_type data)
{
	if (table_search_by_key(t, key) != -1)
	{
		return 2;
	}

	if (table_search_by_key(t, parent_key) == -1 && parent_key != 0 && t->base_key != parent_key)
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
		Key* k = *(k2_ptr);
		for (i = t->size; i >= 0 && *( (*k1_ptr)->parent_key) > parent_key; i--, k1_ptr--, k2_ptr--)
		{
			*(k2_ptr) = *(k1_ptr);
		}

		if (i == -1)
		{
			i = 0;
		}
		
		t->key_arr[i] = k;
	}

	if (i == -1)
	{
		i = 0;
	}

	//printf("%d\n, in - %d, after - %d\n", i, t->key_arr[i], t->key_arr[i+1]);

	*(t->key_arr[i]->key) = key;
	*(t->key_arr[i]->parent_key) = parent_key;
	*(t->key_arr[i]->variable->data) = data;
	t->size++;

	return 0;
}

char table_delete_by_key(Table* t, key_type key)
{
	size_t i, pos_p_elem = table_search_first_with_parent_key(t, key);
	if ( (i = table_search_by_key(t, key)) == -1 && t->base_key != key)
	{
		return 2;
	}

	Key** k1_ptr = t->key_arr + i;
	Key** k2_ptr = t->key_arr + i + 1;
	Key* k = *(t->key_arr + i);
	size_t j;
	for (j = i; j < t->size-1; j++, k1_ptr++, k2_ptr++)
	{
		*(k1_ptr) = *(k2_ptr);
	}

	t->key_arr[j] = k;
	//table_print(t);

	t->size--;

	k2_ptr = t->key_arr;
	size_t count = 0;
	while ( (count < t->size) && ( *( (*k2_ptr)->parent_key ) == 0) )
	{
		count++;
		k2_ptr++;
	}

	//printf("count is - %d\n", count);

	if (count == t->size)
	{
		return 0;
	}

	//printf("%d %d\n", *( (*k2_ptr)->key ), *( (*k2_ptr)->parent_key ) );

	if (count == 0)
	{
		return 0;
	}

	//printf("%d\n", pos_p_elem);
	k1_ptr = t->key_arr + pos_p_elem;
	size_t c = 0;
	while ( *( (*k1_ptr)->parent_key ) == key)
	{
		c++;
		*( (*k1_ptr)->parent_key ) = 0;
		k1_ptr++;
	}
	k1_ptr++;

	//table_print(t);

	if (c == 0)
	{
		return 0;
	}

	swap(k2_ptr, t->key_arr+pos_p_elem, sizeof(k1_ptr)*c);

	return 0;
}

size_t table_search_by_key(Table* t, key_type key)
{
	Key** k = t->key_arr;
	for (size_t i = 0; i < t->size; i++, k++)
	{
		if ( *( (*k)->key ) == key)
		{
			return i;
		}
	}

	return -1;
}

Item get_elem_with_this_key(Table* t, key_type key)
{
	Item ans;
	ans.data = NULL;
	Key** k = t->key_arr;
	for (size_t i = 0; i < t->size; i++, k++)
	{
		if ( *( (*k)->key ) == key)
		{
			ans.data = (variable_type* ) malloc(sizeof(variable_type));
			*(ans.data) = *( (*k)->variable->data );
			return ans;	
		}
	}

	return ans;
}

size_t table_search_first_with_parent_key(Table* t, key_type parent_key)
{
	size_t left = -1, right = t->size, mid;
	while (right - left > 1)
	{
		mid = (left+right)/2;
		if ( *(t->key_arr[mid]->parent_key) < parent_key)
		{
			left = mid;
		}
		else
		{
			right = mid;
		}
	}
	
	if (right >= t->size)
	{
		return -1;
	}

	if ( *(t->key_arr[right]->parent_key) != parent_key)
	{
		return -1;
	}	

	return right;
}

*/
void table_print(Table* t)
{
	Key** k = t->key_arr;
	printf("Table size: %ld\n", t->size);
	for (int i = 0; i < t->size; i++, k++)
	{
		printf("Key - %u, parent_key - %u, ", *( (*k)->key ), *( (*k)->parent_key ));
		fseek(t->table_file, (*k)->offset, SEEK_SET);
                unsigned int data;
                fread(&data, sizeof(unsigned), 1, t->table_file);
                printf("data - %u\n", data);
	}
}

void table_free(Table* t)
{
	Key** k = t->key_arr;
	for (size_t i = 0; i < t->capacity; i++, k++)
	{
		free( (*k)->key );
		free( (*k)->parent_key );
		free( (*k) );
	}

	free(t->key_arr);
	free(t->table_file);
	free(t->file_name);
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

	return k;
}

void swap(void* a, void* b, size_t size)
{
	char* aCh = (a);
	char* bCh = (b);

	do
	{
		char tmp = *(aCh);
		*aCh++ = *bCh;
		*bCh++ = tmp;
	} while (--size > 0);
}
