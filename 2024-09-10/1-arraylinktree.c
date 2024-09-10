#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

void GenerateArrayTree(int* tree) {
	int list[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };

	for (int i = 0; i < 15; i++) {
		tree[i] = list[i];
	}

	for (int i = 0; i < 15; i++) {
		printf("%d", tree[i]);
	}
	printf("\n");
}

void ArrayPreOrder(int* tree) {
	if (tree[i] != NULL) {
		printf("[%d] ", tree[i]);
		ArrayPreOrder(tree[i * 2]);
		ArrayPreOrder(tree[i * 2 + 1]);
	}
}

void ArrayInOrder() {

}

void ArrayPostOrder() {

}

void ArrayOrders() {
	ArrayPreOrder(tree);
	ArrayInOrder(tree);
	ArrayPostOrder(tree);
}

void PlaceNode(TreeNode* node, int direction, int data) {
	
}

void GenerateLinkTree() {
	PlaceNode(root, 0, 2);

}

void LinkPreOrder() {

}

void LinkInOrder() {
	
}

void LinkPostOrder() {

}

void LinkOrders(TreeNode* root) {
	LinkPreOrder(root);
	LinkInOrder(root);
	LinkPostOrder(root);
}

int main() {
	int arr[];
	TreeNode* root = ;
	n1->data = 1;

	GenerateArrayTree(arr);
	GenerateLinkTree(root);

	ArrayOrders(arr);
	LinkOrders(root);

	return 0;
}