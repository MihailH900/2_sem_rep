#ifndef BST_H
#define BST_H

#include <stdlib.h>

typedef struct Item
{
	void* data_ptr;

} Item;

typedef struct Node
{
	void* key_ptr;
	size_t key_size;

	void* data_ptr;
	size_t data_size;

	struct Node* left;
	struct Node* right;
} Node;

typedef struct BST
{
	Node* root;
	int (*cmp) (const void*, const void*);
} BST;

typedef enum BST_codes
{
	BST_MEMORY_ERROR,
	BST_OK
} BST_codes;

BST* BST_init(int (*cmp)(const void*, const void*) );
char BST_add(BST* tree, void* key_ptr, size_t key_size, void* data_ptr, size_t data_size);
char BST_delete(BST* tree, void* key_ptr, size_t key_size);
void BST_print(Node* n, size_t h);
const void* BST_search(BST* tree, void* key_ptr, size_t key_size);
const void* BST_find_next(BST* tree, void* key_ptr, size_t key_size);
Node* create_node(void* key_ptr, size_t key_size, void* data_ptr, size_t data_size);

#endif
