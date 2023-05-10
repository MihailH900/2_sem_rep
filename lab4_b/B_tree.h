#ifndef B_TREE_H
#define B_TREE_H

#include <stdlib.h>

typedef struct Data
{
	void* data_ptr;
	size_t data_size;
} Data;

typedef struct Key
{
	void* key_ptr;
	size_t key_size;
} Key;

typedef struct Node
{
	Key* node_key_1;
	Key* node_key_2;
	
	size_t numb_of_sons;

	struct Node* left;
	struct Node* mid;
	struct Node* right;

	Data* node_data;

	struct Node* parent;
} Node;

typedef struct B_tree
{
	Node* root;
	size_t size;
	size_t depth;
	int (*cmp) (const void*, const void*);
} B_tree;

typedef enum B_tree_codes
{
	B_TREE_MEMORY_ERROR,
	B_TREE_OK
} B_tree_codes;

B_tree* B_tree_init(int (*cmp)(const void*, const void*) );
void B_tree_free(B_tree* tree);
void B_tree_nodes_free(Node* n);
Node* create_node(Key* key_1, Key* key_2, Data* data, Node* parent);
char malloc_memory_for_node_key(Key** node_key, Key* key);
char malloc_memory_for_node_data(Data** node_data, Data* data);
char check_equal(void* a, void* b, size_t size);

#endif
