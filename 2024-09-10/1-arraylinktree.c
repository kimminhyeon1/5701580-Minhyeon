#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

void GenerateArrayTree(int* tree) {
	int list[] = { 1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d ", tree[i]);
	}
	printf("\n\n");
}

void ArrayPreOrder(int* tree, int i) {
	if (i >= 15) {
		return;
	}
	printf("[%d] ", tree[i]);
	ArrayPreOrder(tree, i * 2 + 1);
	ArrayPreOrder(tree, i * 2 + 2);
}

void ArrayInOrder(int* tree, int i) {
	if (i >= 15) {
		return;
	}
	ArrayInOrder(tree, i * 2 + 1);
	printf("[%d] ", tree[i]);
	ArrayInOrder(tree, i * 2 + 2);
}

void ArrayPostOrder(int* tree, int i) {
	if (i >= 15) {
		return;
	}
	ArrayPostOrder(tree, i * 2 + 1);
	ArrayPostOrder(tree, i * 2 + 2);
	printf("[%d] ", tree[i]);
}

void ArrayOrders(int *tree) {
	ArrayPreOrder(tree, 0);
	printf("\n");
	ArrayInOrder(tree, 0);
	printf("\n");
	ArrayPostOrder(tree, 0);
	printf("\n\n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
	TreeNode* newnode = (TreeNode*)malloc(sizeof(TreeNode));
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	if (direction == 0) {
		node->left = newnode;
	}
	else if (direction == 1) {
		node->right = newnode;
	}
}

void GenerateLinkTree(TreeNode* root) {
	PlaceNode(root, 0, 2);
	PlaceNode(root, 1, 9);
	PlaceNode(root->left, 0, 3);
	PlaceNode(root->left, 1, 5);
	PlaceNode(root->right, 0, 10);
	PlaceNode(root->right, 1, 13);
	PlaceNode(root->left->left, 0, 4);
	PlaceNode(root->left->left, 1, 6);
	PlaceNode(root->left->right, 0, 7);
	PlaceNode(root->left->right, 1, 8);
	PlaceNode(root->right->left, 0, 11);
	PlaceNode(root->right->left, 1, 12);
	PlaceNode(root->right->right, 0, 14);
	PlaceNode(root->right->right, 1, 15);

}

void LinkPreOrder(TreeNode* root) {
	if (root != NULL) {
		printf("[%d] ", root->data);
		LinkPreOrder(root->left);
		LinkPreOrder(root->right);
	}
}

void LinkInOrder(TreeNode* root) {
	if (root != NULL) {
		LinkInOrder(root->left);
		printf("[%d] ", root->data);
		LinkInOrder(root->right);
	}
}

void LinkPostOrder(TreeNode* root) {
	if (root != NULL) {
		LinkPostOrder(root->left);
		LinkPostOrder(root->right);
		printf("[%d] ", root->data);
	}
	
}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	printf("\n");
	LinkInOrder(root);
	printf("\n");
	LinkPostOrder(root);
	printf("\n");
}

int main() {
	int arr[15];
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;
	

	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	ArrayOrders(arr);
	LinkOrders(root);

	return 0;
}