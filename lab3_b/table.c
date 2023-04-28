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
	if (file_name == NULL)
	{
		t->file_name = NULL;
	}
	else
	{
		t->file_name = strdup(file_name);
		
		if (t->file_name == NULL)
		{
			return NULL;
		}
	}

	return t;
}

char table_get_elements_from_file(Table* t, char* file_name)
{
	FILE* file_with_table = fopen(file_name, "r");
	
	if (file_with_table == NULL)
	{
		return TABLE_FILE_ERROR;
	}


	Key** k = t->key_arr;
	for (size_t i = 0; i < t->size; i++, k++)
	{
		fscanf(file_with_table, "%u %u", (*k)->key, (*k)->parent_key);
		variable_type data;
		fscanf(file_with_table, "%u", &data);
		
		fseek(t->table_file, 0, SEEK_END);
		size_t offset = ftell(t->table_file);
		fwrite(&data, sizeof(variable_type), 1, t->table_file);
		 
	}

	fclose(file_with_table);

	return TABLE_OK;
}

char table_load_from_binary_file(Table** t, char* file_name)
{
	FILE* f = fopen(file_name, "r+b");
	if (f == NULL)
	{
		return TABLE_FILE_ERROR;
	}
	
	size_t capacity;
	fread(&capacity, sizeof(size_t), 1, f);
	size_t size;
	fread(&size, sizeof(size_t), 1, f);
	
	(*t) = table_init(capacity, 0, f, file_name);
	if ( (*t) == NULL)
	{
		return TABLE_MEMORY_ERROR;
	}

	(*t)->size = size;
	
	Key** k = (*t)->key_arr;
	size_t offset_in_the_start = sizeof( (*t)->capacity) + sizeof( (*t)->size) + (sizeof(key_type) * 2 * (*t)->capacity);
	for (size_t i = 0; i < size; i++, k++)
	{
		fread( (*k)->key, sizeof(key_type), 1, f);
		fread( (*k)->parent_key, sizeof(key_type), 1, f);
		(*k)->offset = offset_in_the_start;
		offset_in_the_start += sizeof(variable_type);
	}
	
	return TABLE_OK;
}

char table_create(Table** t, char* file_name, size_t capacity)
{
	FILE* f = fopen(file_name, "w+b");
	if (f == NULL)
	{
		return TABLE_FILE_ERROR;	
	}
	
	(*t) = table_init(capacity, 0, f, file_name);
	if ( (*t) == NULL)
	{
		return TABLE_MEMORY_ERROR;
	}
	
	fseek( (*t)->table_file, 0, SEEK_SET);
	
	fwrite(&( (*t)->capacity), sizeof(size_t), 1, (*t)->table_file);
        fwrite(&( (*t)->size), sizeof(size_t), 1, (*t)->table_file);
        
        Key** k = (*t)->key_arr;
	for (size_t i = 0; i < (*t)->capacity; i++, k++)
	{
		fwrite( (*k)->key, sizeof(key_type), 1, (*t)->table_file);
		fwrite( (*k)->parent_key, sizeof(key_type), 1, (*t)->table_file);
	}
        
        return TABLE_OK;
}

char table_save(Table* t)
{
	variable_type* elems_in_the_end = (variable_type*) malloc(sizeof(variable_type) * t->size);
	if (elems_in_the_end == NULL)
	{
		return TABLE_MEMORY_ERROR;
	}
	
	variable_type v;
	variable_type* e = elems_in_the_end;
	Key** k = t->key_arr;
	
	size_t offset_in_the_end = sizeof(t->capacity) + sizeof(t->size) + (sizeof(key_type) * 2 * t->capacity);
	for(int i = 0; i < t->size; i++, e++, k++)
	{
                fseek(t->table_file, (*k)->offset, SEEK_SET);
                fread(&v, sizeof(variable_type), 1, t->table_file);
                *e = v;

                (*k)->offset = offset_in_the_end;
                offset_in_the_end += sizeof(variable_type);
        }
        fclose(t->table_file);
        
        t->table_file = fopen(t->file_name, "w+b");
        if (t->table_file == NULL)
	{
		return TABLE_FILE_ERROR;
	}
	
	fwrite(&( t->capacity), sizeof(size_t), 1, t->table_file);
        fwrite(&( t->size), sizeof(size_t), 1, t->table_file);
        
        k = t->key_arr;
	for (size_t i = 0; i < t->capacity; i++, k++)
	{
		fwrite( (*k)->key, sizeof(key_type), 1, t->table_file);
		fwrite( (*k)->parent_key, sizeof(key_type), 1, t->table_file);
	}
	
	e = elems_in_the_end;
	for (size_t i = 0; i < t->size; i++, e++)
	{
		fwrite(e, sizeof(variable_type), 1, t->table_file);
	}
        
        free(elems_in_the_end);
        
        return TABLE_OK;
}

Table* table_search_by_parent_key(Table* t, key_type parent_key)
{
	size_t ans_size = 0;
	size_t ind = table_search_first_with_parent_key(t, parent_key);

	FILE* f = fopen("help", "w+b");

	if (ind == -1)
	{
		Table* ans = table_init(ans_size, parent_key, f, "help");
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

	Table* ans = table_init(ans_size, parent_key, f, "help");
	k = t->key_arr+ind;
	i = ind;
	while ( (i < t->size) && ( *( (*k)->parent_key ) == parent_key ) )
	{
                fseek(t->table_file, (*k)->offset, SEEK_SET);
		variable_type v;	
                fread(&v, sizeof(variable_type), 1, t->table_file);
		table_add(ans, *( (*k)->key ), *( (*k)->parent_key ), v);
		k++;
		i++;
	}

	return ans;
}

char table_add(Table* t, key_type key, key_type parent_key, variable_type data)
{
	if (table_search_by_key(t, key) != t->size)
	{
		return TABLE_ADD_KEY_ERROR;
	}

	if (table_search_by_key(t, parent_key) == t->size && parent_key != 0 && parent_key != t->base_key)
	{
		return TABLE_ADD_PARENT_KEY_ERROR;
	}

	if (t->size == t->capacity)
	{
		return TABLE_ADD_SIZE_ERROR;
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

	*(t->key_arr[i]->key) = key;
	*(t->key_arr[i]->parent_key) = parent_key;

	fseek(t->table_file, 0, SEEK_END);
	size_t offset = ftell(t->table_file);
	fwrite(&data, sizeof(variable_type), 1, t->table_file);
	t->key_arr[i]->offset = offset;

	t->size++;

	return 0;
}

char table_delete_by_key(Table* t, key_type key)
{
	size_t i, pos_first_elem_with_deleted_parent_key = table_search_first_with_parent_key(t, key);
	if ( (i = table_search_by_key(t, key)) == t->size && t->base_key != key)
	{ 
		return TABLE_FIND_ERROR;
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

	t->size--;

	k2_ptr = t->key_arr;
	size_t count = 0;
	while ( (count < t->size) && ( *( (*k2_ptr)->parent_key ) == 0) )
	{
		count++;
		k2_ptr++;
	}

	if (count == t->size)
	{
		return TABLE_OK;
	}

	if (count == 0)
	{
		return TABLE_OK;
	}

	if (pos_first_elem_with_deleted_parent_key > 0)
	{
		pos_first_elem_with_deleted_parent_key--;
	}

	k1_ptr = t->key_arr + pos_first_elem_with_deleted_parent_key;
	size_t c = 0;
	while ( *( (*k1_ptr)->parent_key ) == key) // this is working because parent key of last element not equal key
						   // (we alreade have deleted this elemnt, now it is on the end of table)
						   // this while can't work infinitly
	{
		c++;
		*( (*k1_ptr)->parent_key ) = 0;
		k1_ptr++;
	}
	k1_ptr++;

	if (c == 0)
	{
		return TABLE_OK;
	}
	
	if (c < MAX_BLOCK_SIZE)
	{
		void* ptr = malloc (c*sizeof(Key*));
		memcpy(ptr, t->key_arr+pos_first_elem_with_deleted_parent_key, c*sizeof(Key*) );
		memmove(t->key_arr + count + c - 1, t->key_arr+count, (pos_first_elem_with_deleted_parent_key+1-count-c)*sizeof(Key*) );
		memmove(t->key_arr + count, ptr, c*sizeof(Key*) );
	}
	else
	{
		Key* ptr;
		
		for (size_t i = 0; i < c; i++)
		{
			ptr = *(t->key_arr + pos_first_elem_with_deleted_parent_key + i);
			size_t j = count;
			Key** k1 =  t->key_arr + pos_first_elem_with_deleted_parent_key + i - 1;
			Key** k2 =  t->key_arr + pos_first_elem_with_deleted_parent_key + i;

			for (size_t j = pos_first_elem_with_deleted_parent_key + i; j > 0; j--, k1--, k2--)
			{
				*(k2) = *(k1);
			}

			t->key_arr[count+i] = ptr;
		}
	}

	return TABLE_OK;
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

	return t->size;
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

                	fseek(t->table_file, (*k)->offset, SEEK_SET);
			ans.data = (variable_type* ) malloc(sizeof(variable_type));
                	fread(ans.data, sizeof(variable_type), 1, t->table_file);
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

void table_print(Table* t)
{
	Key** k = t->key_arr;
	printf("Table size: %zu\n", t->size);
	for (int i = 0; i < t->size; i++, k++)
	{
		printf("Key - %u, parent_key - %u, ", *( (*k)->key ), *( (*k)->parent_key ));
		fseek(t->table_file, (*k)->offset, SEEK_SET);
                variable_type data;
                fread(&data, sizeof(variable_type), 1, t->table_file);
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
	fclose(t->table_file);
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
	*(k->key) = 0;

	k->parent_key = (key_type* ) malloc(sizeof(key_type));
	if (k->parent_key == NULL)
	{
		return NULL;
	}
	*(k->parent_key) = 0;

	return k;
}
