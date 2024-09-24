#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
}TreeNode;

typedef TreeNode* element;	
typedef struct QueueNode {	
	element data;
	struct QueueNode* link;
} QueueNode;

typedef struct {		
	QueueNode* front, * rear;
} LinkedQueueType;

void init(LinkedQueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(LinkedQueueType* q) {
	return (q->front == NULL);
}
int is_full(LinkedQueueType* q) {
	return 0;
}

void enqueue(LinkedQueueType* q, element data)
{
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->data = data; 		
	temp->link = NULL; 		
	if (is_empty(q)) { 		
		q->front = temp;
		q->rear = temp;
	}
	else { 		
		q->rear->link = temp; 
		q->rear = temp;
	}
}
element dequeue(LinkedQueueType* q)
{
	QueueNode* temp = q->front;
	element data;
	if (is_empty(q)) {		
		fprintf(stderr, "queue is empty\n");
		exit(1);
	}
	else {
		data = temp->data; 	
		q->front = q->front->link; 
		if (q->front == NULL) 	
			q->rear = NULL;
		free(temp); 		
		return data; 		
	}
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

void GetSumOfNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr = root;
	int sum = 0;
	init(&q);	

	if (root == NULL) return 0;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		sum += ptr->data;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	printf("Sum of nodes: %d\n", sum);
}

void GetNumberOfNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr = root;
	int count = 0;
	init(&q);

	if (root == NULL) return;
	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		count++;
		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}
	printf("Number of nodes: %d\n", count);
}

void GetHeightOfTree(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr;
	int height = 0;
	
	init(&q);
	enqueue(&q, root);

	if (root == NULL) return;
	while (!is_empty(&q)) {
		int level_size = 0;
		QueueNode* current = q.front;

		while (current) {
			level_size++;
			current = current->link;
		}
		for (int i = 0; i < level_size; i++) {
			ptr = dequeue(&q);
			if (ptr->left)
				enqueue(&q, ptr->left);
			if (ptr->right)
				enqueue(&q, ptr->right);
		}
		height++;
	}
	printf("Height of Tree: %d\n", height);
}

void GetNumberOfLeafNodes(TreeNode* root) {
	LinkedQueueType q;
	TreeNode* ptr;
	int leafCount = 0;
	
	init(&q);
	enqueue(&q, root);

	if (root == NULL) return;
	while (!is_empty(&q)) {
		ptr = dequeue(&q);

		if (ptr->left == NULL && ptr->right == NULL) {
			leafCount++;
		}

		if (ptr->left)
			enqueue(&q, ptr->left);
		if (ptr->right)
			enqueue(&q, ptr->right);
	}

	printf("Number of leaf nodes: %d\n", leafCount);
}
int main() {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	root->data = 1;

	GenerateLinkTree(root);

	GetSumOfNodes(root);
	GetNumberOfNodes(root);
	GetHeightOfTree(root);
	GetNumberOfLeafNodes(root);

	return 0;
}