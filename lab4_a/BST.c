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
	tree->size = 0;
	tree->depth = 0;
	return tree;
}

char BST_add(BST* tree, Key* k, Data* d)
{
	if (tree == NULL)
	{
		return BST_NOT_INIT_ERROR;
	}

	if (tree->root == NULL)
	{
		tree->root = create_node(k, d);
		if (tree->root == NULL)
		{
			return BST_MEMORY_ERROR;
		}

		tree->size++;
		return BST_OK;
	}

	Node* n = tree->root;
	Node* parent = NULL;

	while (n != NULL)
	{
		parent = n;
		if ( tree->cmp(k->key_ptr, n->node_key->key_ptr) )
		{
			n = n->left;
		}
		else
		{
			n = n->right;
		}
	}

	
	if ( tree->cmp(k->key_ptr, parent->node_key->key_ptr) )
	{
		parent->left = create_node(k, d);
		if (parent->left == NULL)
		{
			return BST_MEMORY_ERROR;
		}

		tree->size++;
		return BST_OK;
	}
	else
	{
		parent->right = create_node(k, d);
		if (parent->right == NULL)
		{
			return BST_MEMORY_ERROR;
		}

		tree->size++;
		return BST_OK;
	}
}

char BST_delete(BST* tree, Key* k)
{
	if (tree == NULL)
	{
		return BST_NOT_INIT_ERROR;
	}

	Node* n;
	Node* parent;
	n = BST_search_node(tree, k, &parent);

	if (n == NULL)
	{
		return BST_FIND_ERROR;
	}

	if (n->left == NULL && n->right == NULL)
	{
		if (parent->left == n)
		{
			parent->left = NULL;
		}
		if (parent->right == n)
		{
			parent->right = NULL;
		}


	}
	else if (n->left == NULL || n->right == NULL)
	{
		if (n->left == NULL)
		{
			if (parent->left == n)
			{
				parent->left = n->right;
			}
			else
			{
				parent->right = n->right;
			}
		}
		else
		{
			if (parent->left == n)
			{
				parent->left = n->left;
			}
			else
			{
				parent->right = n->left;
			}
		}
	}
	else
	{
		Node* next_parent;
		Node* next = BST_find_next_node(tree, k, &next_parent);
		
		if (next_parent->left == next)
		{
			next_parent->left = next->right;
		}
		else
		{
			next_parent->right = next->right;
		}

		//BST_print(tree->root, 1);
		
		if (parent != NULL)
		{
			if (parent->left == n)
			{
				parent->left = next;
			}
			else
			{
				parent->right = next;
			}
		}

		next->left = n->left;
		next->right = n->right;
	
		if (parent == NULL)
		{
			tree->root = next;
		}
	}

	
	free(n->node_key->key_ptr);
	free(n->node_key);
	free(n->node_data->data_ptr);
	free(n->node_data);
	free(n);

	tree->size--;

	return BST_OK;
}

Data* BST_search(BST* tree, Key* k, char* flag)
{
	if (tree == NULL)
	{
		(*flag) == BST_NOT_INIT_ERROR;
		return NULL;
	}

	if (tree->root == NULL)
	{
		(*flag) = BST_OK;
		return NULL;
	}

	Node* n = tree->root;

	while (n != NULL)
	{
		if (n->node_key->key_size == k->key_size && check_equal(n->node_key->key_ptr, k->key_ptr, k->key_size) == 0)
		{
			(*flag) = BST_OK;
			return n->node_data;
		}

		if (tree->cmp(k->key_ptr, n->node_key->key_ptr))
		{
			n = n->left;
		}
		else
		{
			n = n->right;
		}
	}

	(*flag) = BST_OK;
	return NULL;
}

const Key* BST_find_next(BST* tree, Key* k, char* flag)
{
	if (tree == NULL)
	{
		(*flag) == BST_NOT_INIT_ERROR;
		return NULL;
	}

	Node* n_1 = tree->root;
	Node* n_2 = NULL;

	while (n_1 != NULL)
	{
		if (tree->cmp(n_1->node_key->key_ptr, k->key_ptr))
		{
			n_1 = n_1->right;
		}
		else
		{	
			if (n_1->node_key->key_size == k->key_size && check_equal(n_1->node_key->key_ptr, k->key_ptr, k->key_size) == 0)
			{
				if (n_1->right == NULL)
				{
					break;
				}
				else
				{
					n_1 = n_1->right;
					continue;
				}
			}
			n_2 = n_1;
			n_1 = n_1->left;
		}
	}

	(*flag) = BST_OK;

	if (n_2 == NULL)
	{
		return NULL;
	}

	return n_2->node_key;
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
		printf("%u\n", *( (unsigned int*)(n->node_key->key_ptr) ));
		BST_print(n->left, h+1);
	}
}


void set_tree_depth(BST* tree, Node* n, size_t h)
{
	if (n->left != NULL)
	{
		set_tree_depth(tree, n->left, h+1);
	}
	if (n->right != NULL)
	{
		set_tree_depth(tree, n->right, h+1);
	}

	if (tree->depth < h)
	{
		tree->depth = h;
	}
}

Node* BST_find_next_node(BST* tree, Key* k, Node** parent)
{
	Node* n_1 = tree->root;
	Node* n_1_parent;
	Node* n_2 = NULL;
	(*parent) = NULL;

	while (n_1 != NULL)
	{
		if (tree->cmp(n_1->node_key->key_ptr, k->key_ptr))
		{
			n_1_parent = n_1;
			n_1 = n_1->right;
		}
		else
		{	
			if (n_1->node_key->key_size == k->key_size && check_equal(n_1->node_key->key_ptr, k->key_ptr, k->key_size) == 0)
			{
				if (n_1->right == NULL)
				{
					break;
				}
				else
				{
					n_1_parent = n_1;
					n_1 = n_1->right;
					continue;
				}
			}

			(*parent) = n_1_parent;
			n_2 = n_1;

			n_1_parent = n_1;
			n_1 = n_1->left;

		}
	}

	return n_2;
}

Node* BST_search_node(BST* tree, Key* k, Node** parent)
{
	if(tree->root == NULL)
	{
		return NULL;
	}

	Node* n = tree->root;
	(*parent) = NULL;

	while (n != NULL)
	{
		if (n->node_key->key_size == k->key_size && check_equal(n->node_key->key_ptr, k->key_ptr, k->key_size) == 0)
		{
			return n;
		}

		if (tree->cmp(k->key_ptr, n->node_key->key_ptr))
		{
			(*parent) = n;
			n = n->left;
		}
		else
		{
			(*parent) = n;
			n = n->right;
		}
	}

	return NULL;
}

void BST_free(BST* tree)
{
	if (tree == NULL)
	{
		return;
	}

	if (tree->root == NULL)
	{
		free(tree);
		return;
	}

	BST_nodes_free(tree->root);
	free(tree);
}

void BST_nodes_free(Node* n)
{
	if (n->left != NULL)
	{
		BST_nodes_free(n->left);
	}

	if (n->right != NULL)
	{
		BST_nodes_free(n->right);
	}

	free(n->node_key->key_ptr);
	free(n->node_key);
	free(n->node_data->data_ptr);
	free(n->node_data);
	free(n);
}

Node* create_node(Key* k, Data* d)
{	
	Node* n = (Node*) malloc(sizeof(Node));
	if (n == NULL)
	{
		return NULL;
	}
	
	n->node_key = malloc(sizeof(Key));
	if(n->node_key == NULL)
	{
		return NULL;
	}
	n->node_key->key_ptr = malloc(k->key_size);
	if (n->node_key->key_ptr == NULL)
	{
		return NULL;
	}
	memcpy(n->node_key->key_ptr, k->key_ptr, k->key_size);
	n->node_key->key_size = k->key_size;

	n->node_data = malloc(sizeof(Data));
	if(n->node_data == NULL)
	{
		return NULL;
	}
	n->node_data->data_ptr = malloc(d->data_size);
	if (n->node_data->data_ptr == NULL)
	{
		return NULL;
	}
	memcpy(n->node_data->data_ptr, d->data_ptr, d->data_size);
	n->node_data->data_size = d->data_size;

	n->left = NULL;
	n->right = NULL;

	return n;
}

char check_equal(void* a, void* b, size_t size)
{
	if (a == NULL || b == NULL)
	{
		return 1;
	}

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
