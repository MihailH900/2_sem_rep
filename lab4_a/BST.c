#include "BST.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

BST* BST_init(int (*cmp)(const void*, const void*) )
{
	BST* tree = (BST*) malloc(sizeof(BST));
	if (tree == NULL)
	{
		return NULL;
	}

	tree->cmp = cmp;
	tree->root = NULL;
	return tree;
}

char BST_add(BST* tree, void* key_ptr, size_t key_size, void* data_ptr, size_t data_size)
{
	if (tree->root == NULL)
	{
		tree->root = create_node(key_ptr, key_size, data_ptr, data_size);
		if (tree->root == NULL)
		{
			return BST_MEMORY_ERROR;
		}

		return BST_OK;
	}

	Node* n = tree->root;
	Node* parent = NULL;

	while (n != NULL)
	{
		parent = n;
		if ( tree->cmp(key_ptr, n->key_ptr) )
		{
			n = n->left;
		}
		else
		{
			n = n->right;
		}
	}

	
	if ( tree->cmp(key_ptr, parent->key_ptr) )
	{
		parent->left = create_node(key_ptr, key_size, data_ptr, data_size);
		if (parent->left == NULL)
		{
			return BST_MEMORY_ERROR;
		}

		return BST_OK;
	}
	else
	{
		parent->right = create_node(key_ptr, key_size, data_ptr, data_size);
		if (parent->right == NULL)
		{
			return BST_MEMORY_ERROR;
		}

		return BST_OK;
	}
}

char BST_delete(BST* tree, void* key_ptr, size_t key_size)
{

}

const void* BST_find_next(BST* tree, void* key_ptr, size_t key_size)
{

}

void BST_print(Node* n, size_t h)
{
	size_t i = h;
	if (n != NULL)
	{
		BST_print(n->right, h+1);
		while (i-- > 0)
		{
			printf("  ");
		}
		printf("%u\n", *( (unsigned int*)(n->data_ptr) ));
		BST_print(n->left, h+1);
	}
}

const void* BST_search(BST* tree, void* key_ptr, size_t key_size)
{

}

Node* create_node(void* key_ptr, size_t key_size, void* data_ptr, size_t data_size)
{	
	Node* n = (Node*) malloc(sizeof(Node));
	if (n == NULL)
	{
		return NULL;
	}

	
	n->key_ptr = malloc(sizeof(key_size));
	if(n->key_ptr == NULL)
	{
		return NULL;
	}
	memcpy(n->key_ptr, key_ptr, key_size);
	n->key_size = key_size;

	n->data_ptr = malloc(sizeof(data_size));
	if(n->data_ptr == NULL)
	{
		return NULL;
	}
	memcpy(n->data_ptr, data_ptr, data_size);
	n->data_size = data_size;

	n->left = NULL;
	n->right = NULL;

	return n;
}
