#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
	struct node *left, *right;
	int data;
} node_t;

/* Assumptions: 
 * values in the left subtree are <= the root,
 * values in the right subtree are greater, and
 * values in the tree are unique.
 */
/* @brief Insert a value into a tree.
 *
 * insert() inserts a value into the binary search tree pointed to by root.
 * 
 * @return 0 if the value was inserted or already present in the tree
 * @return -1 if the tree is empty or memory allocation failed
 */
int insert(node_t **root, int value) {
	int retval = 0;

	if (NULL == *root) {
		*root = malloc(sizeof(node_t));
		if (NULL != *root) {
			(*root)->data = value;
			(*root)->left = NULL;
			(*root)->right = NULL;
			retval = 0;
		}
		else {
			retval = -1;
		}
	}
	else if (value == (*root)->data) {
		retval = 0;
	}
	else if (value <= (*root)->data) {
		retval = insert(&((*root)->left), value);
	}
	else {
		retval = insert(&((*root)->right), value);
	}
	return retval;
}

void print_inorder(node_t * root, unsigned int level) {
	if (NULL == root) { return; }

	puts("in print_inorder");
	print_inorder(root->left, level+1);
	printf("[%u] %d\n", level, root->data);
	print_inorder(root->right, level+1);
	return;
}


node_t * find_max(node_t *root) {
	if (NULL == root) {
		return NULL;
	}
	if (NULL != root->right) {
		return find_max(root->right);
	}
	return root;
}

node_t * find_min(node_t *root) {
	if (NULL == root) {
		return NULL;
	}
	if (NULL != root->left) {
		return find_min(root->left);
	}
	return root;
}

bool isBST(node_t *root) {
	if (NULL == root) {
		return true;
	}
	if (NULL != root->left && find_max(root->left)->data > root->data) {
		return false;
	}
	if (NULL != root->right && find_min(root->right)->data <= root->data) {
		return false;
	}
	
	return isBST(root->left) && isBST(root->right);
}

node_t * delete(node_t * root, int x) {
	if (NULL == root) {
		return NULL;
	}

	if (x > root->data) {
		root->right = delete(root->right, x);
	}
	else if (x < root->data) {
		root->left = delete(root->left, x);
	}
	else {
		// no children
		if (NULL == root->left && NULL == root->right) {
			free(root);
			return NULL;
		}
		// one child
		else if (NULL == root->left || NULL == root->right) {
			node_t * temp;
			if (NULL == root->left) {
				temp = root->right;
			}
			else {
				temp = root->left;
			}
			free(root);
			return temp;
		}
		// two children
		else {
			node_t * temp = find_min(root->right);
			root->data = temp->data;
			root->right = delete(root->right, temp->data);
		}
	}
	return root;
}

int test_insert(void) {
	node_t *root = NULL;
	int value = 5, retval = 0;

	retval = insert(&root, value);
	//printf("test_insert insert retval: %d\n", retval);
	if (0 == retval) {
		if ((root != NULL) && (root->data == value) && (root->left == NULL) && (root->right == NULL)) {
			//print_inorder(root, 0);
			return 0;
		}
	}
	return -1;
}

int test_insert_right(void) {
	node_t *root = NULL;
	int value1 = 4, value2 = 9, retval = 0;

	retval = insert(&root, value1);
	if (0 != retval) {
		puts("test_insert_right: error inserting value1");
	}
	else {
		retval = insert(&root, value2);
		if (0 != retval) {
			puts("test_insert_right: error inserting value2");
		}
		else {
			if((value1 == root->data) && (value2 == root->right->data)) {
				retval = 0;
			}
		}
	}
	return retval;
}

int test_insert_left(void) {
	node_t *root = NULL;
	int value1 = 4, value2 = 3, retval = 0;

	retval = insert(&root, value1);
	if (0 != retval) {
		puts("test_insert_left: error inserting value1");
	}
	else {
		retval = insert(&root, value2);
		if (0 != retval) {
			puts("test_insert_left: error inserting value2");
		}
		else {
			if((value1 == root->data) && (value2 == root->left->data)) {
				retval = 0;
			}
		}
	}
	return retval;
}

int test_delete(void) {
	node_t *root = NULL;
	int value1 = 3, value2 = 2, value3 = 4;

	insert(&root, value1);
	insert(&root, value2);
	insert(&root, value3);

	root = delete(root, value2);
	// delete() should delete the left child and leave value3 in the right child.
	return ((value1 == root->data) && (NULL == root->left) && (NULL != root->right) && (value3 == root->right->data));
}
/*
test_delete_root(void) {
	node_t *root = NULL;
	int value1 = 3, value2 = 2, value3 = 4;

	insert(&root, value1);
	insert(&root, value2);
	insert(&root, value3);

	root = delete(root, value1);
	// delete() should delete the root value and arrange the tree to preserve invariants.
	return ((NULL == find(root, value1)) && isBST(root) == true);
}
*/

struct test {
	char * name;
	int (*function)(void);
};

struct test tests[] = {
	{"test_insert", &test_insert},
	{"test_insert_right", &test_insert_right},
	{"test_insert_left", &test_insert_left},
	{"test_delete", &test_delete}
};

int main(void) {
	int i = 0, retval = 0;
	int num_tests = sizeof(tests)/sizeof(struct test);

	for (i = 0; i < num_tests; i++) {
		retval = (*(tests[i].function))();
		if (retval == 0) {
			printf("Passed %s\n", tests[i].name);
		}
		else {
			printf("Failed %s\n", tests[i].name);
		}
	}

	return 0;
}
