#include <stdio.h>
#include <stdlib.h>

typedef int value;

typedef struct TreeNode {
	value data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;

typedef struct StackNode {
	element data;
	struct StackNode* link;
} StackNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

// 초기화 함수
void init(LinkedStackType* s)
{
	s->top = NULL;
}
// 공백 상태 검출 함수
int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}
// 포화 상태 검출 함수
int is_full(LinkedStackType* s)
{
	return 0;
}
// 삽입 함수
void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	temp->data = item;
	temp->link = s->top;
	s->top = temp;
}

element pop(LinkedStackType* s) {
	StackNode* temp = s->top;
	element data = temp->data;
	s->top = temp->link;
	free(temp);
	return data;
}

TreeNode* peek(LinkedStackType* s) {
	if (is_empty(s)) return NULL;
	return s->top->data;
}

void print_stack(LinkedStackType* s)
{
	for (StackNode* p = s->top; p != NULL; p = p->link)
		printf("%d->", p->data->data);  // implementation specific
	printf("NULL \n");
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
	LinkedStackType s;

	init(&s);

	push(&s, root);
	printf("push(%d) ", root->data);
	while (!is_empty(&s)) {
		TreeNode* nptr = pop(&s);
		printf("pop(%d) visit(%d)\n", nptr->data, nptr->data);
		TreeNode* temp = nptr->right;
		if (temp != NULL) {
			push(&s, temp);
			printf("push(%d) ", temp->data);
		}
		temp = nptr->left;
		if (temp != NULL) {
			push(&s, temp);
			printf("push(%d) ", temp->data);
		}
	}
	printf("\n");
}

void LinkInOrder(TreeNode* root) {
	LinkedStackType s;
	TreeNode* nptr = root;

	init(&s);

	while (nptr != NULL || !is_empty(&s)) {
		while (nptr != NULL) {
			push(&s, nptr);
			printf("push(%d) ", nptr->data);
			nptr = nptr->left;
		}

		nptr = pop(&s);
		printf("pop(%d) visit(%d)\n", nptr->data, nptr->data);

		nptr = nptr->right;
	}
	printf("\n");
}

void LinkPostOrder(TreeNode* root) {
	if (!root) return;
	
	LinkedStackType s;
	TreeNode* prev = NULL;
	
	init(&s);
	
	push(&s, root);
	printf("push(%d) ", root->data);
	
	while (!is_empty(&s)) {
		TreeNode* nptr = peek(&s);

		if (!prev || prev->left == nptr || prev->right == nptr) {
			if (nptr->left) {
				push(&s, nptr->left);
				printf("push(%d) ", nptr->left->data);
			}
			else if (nptr->right) {
				push(&s, nptr->right);
				printf("push(%d) ", nptr->right->data);
			}
		}
		else if (nptr->left == prev) {
			if (nptr->right) {
				push(&s, nptr->right);
				printf("push(%d) ", nptr->right->data);
			}
		}
		else {
			TreeNode* temp = pop(&s);
			printf("pop(%d) visit(%d)\n", temp->data, temp->data);
		}
		prev = nptr;
		
	}
	printf("\n");
}

void LinkOrders(TreeNode* root) {
	printf("LinkPreOrder:\n");
	LinkPreOrder(root);
	printf("LinkInOrder:\n");
	LinkInOrder(root);
	printf("LinkPostOrder:\n");
	LinkPostOrder(root);
}

int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);
	LinkOrders(root);

	return 0;
}