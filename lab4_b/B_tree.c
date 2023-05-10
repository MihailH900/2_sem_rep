#include "B_tree.h"

B_tree* B_tree_init(int (*cmp)(const void*, const void*) )
{
	B_tree* tree = (B_tree*) malloc(sizeof(B_tree));
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

void B_tree_free(B_tree* tree)
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

	B_tree_nodes_free(tree->root);
	free(tree);
}

void B_tree_nodes_free(Node* n)
{
	if (n->left != NULL)
	{
		B_tree_nodes_free(n->left);
	}
	
	if (n->mid != NULL)
	{
		B_tree_nodes_free(n->mid);
	}

	if (n->right != NULL)
	{
		B_tree_nodes_free(n->right);
	}

	free(n->node_key_1->key_ptr);
	free(n->node_key_1);
	free(n->node_key_2->key_ptr);
	free(n->node_key_2);
	free(n->node_data->data_ptr);
	free(n->node_data);
	free(n);
}

Node* create_node(Key* key_1, Key* key_2, Data* data, Node* parent)
{
	Node* n = (Node*) malloc(sizeof(Node));
	if (n == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}

	if (malloc_memory_for_node_key(&n->node_key_1, key_1) != B_TREE_OK)
	{
		return B_TREE_MEMORY_ERROR;
	}

	if (malloc_memory_for_node_key(&n->node_key_2, key_2) != B_TREE_OK)
	{
		return B_TREE_MEMORY_ERROR;
	}

	
	if (malloc_memory_for_node_data(&n->node_data, data) != B_TREE_OK)
	{
		return B_TREE_MEMORY_ERROR;
	}

	n->numb_of_sons = 0;
	n->left = NULL;
	n->mid = NULL;
	n->right = NULL;
	n->parent = parent;

	return n;
}

char malloc_memory_for_node_key(Key** node_key, Key* key)
{
	(*node_key) = (Key*) malloc(sizeof(Key));
	if ( (*node_key) == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}
	(*node_key)->key_ptr = malloc(key->key_size);
	if ( (*node_key)->key_ptr == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}
	(*node_key)->key_size = key->key_size;

	return B_TREE_OK;
}

char malloc_memory_for_node_data(Data** node_data, Data* data)
{
	(*node_data) = (Data*) malloc(sizeof(Data));
	if ( (*node_data) == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}
	(*node_data)->data_ptr = malloc(data->data_size);
	if ( (*node_data)->data_ptr == NULL)
	{
		return B_TREE_MEMORY_ERROR;
	}
	(*node_data)->data_size = data->data_size;

	return B_TREE_OK;
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
