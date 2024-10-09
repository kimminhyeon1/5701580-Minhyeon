#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct tree_node {
	int data;
	struct tree_node* left, * right;
} TreeNode;

typedef struct thread_node {
	int data;
	struct thread_node* left, * right;
	int is_thread;
}ThreadNode;

TreeNode* new_node(int key) {
	TreeNode* temp;
	temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) {
		exit(1); 
	}
	temp->data = key;
	temp->right = temp->left = NULL;
	return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
	if (root == NULL)
		return new_node(key);

	if (root->data == key) return root;
	else if (root->data > key) root->left = insert_node(root->left, key);
	else root->right = insert_node(root->right, key);

	return root;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
	TreeNode* root = new_node(inputData[0]);
	
	for (int i = 1; i < 15; i++) {
		insert_node(root, inputData[i]);
	}
	return root;
}

void BinaryTreeInOrder(TreeNode* root) {
	if (root != NULL) {
		BinaryTreeInOrder(root->left);
		printf("%d ", root->data);
		BinaryTreeInOrder(root->right);
	}
}

ThreadNode* new_tnode(int key) {
	ThreadNode* temp;
	temp = (ThreadNode*)malloc(sizeof(ThreadNode));
	if (temp == NULL) {
		exit(1); 
	}
	temp->data = key;
	temp->right = temp->left = NULL;
	temp->is_thread = TRUE;
	return temp;
}
ThreadNode* insert_tnode(ThreadNode* troot, int key) {
	ThreadNode* temp = troot;
	ThreadNode* parent = NULL;

	while (temp != NULL) {
		parent = temp;
		if (key == temp->data) {
			return troot; 
		}

		if (key < temp->data) {
			if (temp->left != NULL) {
				temp = temp->left;
			}
			else {
				break;
			}
		}
		else {
			if (temp->is_thread == FALSE) {
				temp = temp->right;
			}
			else {
				break;
			}
		}
	}

	ThreadNode* node = new_tnode(key);

	if (parent == NULL) {
		troot = node; 
	}
	else if (key < parent->data) {
		parent->left = node;
		node->right = parent; 
	}
	else {
		node->right = parent->right;
		parent->is_thread = FALSE; 
		parent->right = node;
	}

	return troot;
}

TreeNode* GenerateThreadTree(int inputData[]) {
	ThreadNode* troot = NULL;

	for (int i = 0; i < 15; i++) {
		troot = insert_tnode(troot, inputData[i]);
	}

	return troot;
}

ThreadNode* find_successor(ThreadNode* tnode) {
	ThreadNode* right_tnode = tnode->right;
	if (right_tnode == NULL || tnode->is_thread == TRUE) {
		return right_tnode;
	}
	while (right_tnode->left != NULL) {
		right_tnode = right_tnode->left;
	}
	return right_tnode;
}
void ThreadTreeInOrder(ThreadNode* troot) {
	ThreadNode* temp;

	temp = troot;
	while (temp->left) {
		temp = temp->left;
	}
	do {
		printf("%d ", temp->data);
		temp = find_successor(temp);
	} while (temp);
}

int main() {
	int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
	TreeNode* root = GenerateBinaryTree(inputData);
	printf("Binary tree inorder: ");
	BinaryTreeInOrder(root);

	ThreadNode* troot = GenerateThreadTree(inputData);
	printf("\nThread tree inorder: ");
	ThreadTreeInOrder(troot);

	free(root);
	free(troot);
	return 0;
}