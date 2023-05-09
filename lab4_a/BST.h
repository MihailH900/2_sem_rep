#ifndef BST_H
#define BST_H

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
	Key* node_key;
	Data* node_data;

	struct Node* left;
	struct Node* right;
} Node;

typedef struct BST
{
	Node* root;
	size_t size;
	size_t depth;
	int (*cmp) (const void*, const void*);
} BST;

typedef enum BST_codes
{
	BST_NOT_INIT_ERROR,
	BST_FIND_ERROR,
	BST_MEMORY_ERROR,
	BST_OK
} BST_codes;

BST* BST_init(int (*cmp)(const void*, const void*) );
char BST_add(BST* tree, Key* k, Data* d);
char BST_delete(BST* tree, Key* k);
Data* BST_search(BST* tree, Key* k, char* flag);
const Key* BST_find_next(BST* tree, Key* k, char* flag);
void BST_print(Node* n, size_t h);
void set_tree_depth(BST* tree, Node* n, size_t h);
Node* BST_find_next_node(BST* tree, Key* k, Node** parent);
Node* BST_search_node(BST* tree, Key* k, Node** parent);
void BST_free(BST* tree);
void BST_nodes_free(Node* n);
Node* create_node(Key* k, Data* d);
char check_equal(void* a, void* b, size_t size);

#endif
