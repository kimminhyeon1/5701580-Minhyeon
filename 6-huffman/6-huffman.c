#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
typedef struct Node {
	int weight;
	char ch;
	struct Node* left;
	struct Node* right;
}Node;

typedef struct {
	Node* ptree;
	char ch;
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//히프트리를 생성하는 함수입니다.
HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

//히프트리 초기화 함수입니다.
void init(HeapType* h) {
	h->heap_size = 0;
}

// 히프트리를 출력해주는 함수입니다.
void print_heap(HeapType* h) {
	for (int i = 1; i <= h->heap_size; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");
}

//최소히프트리에서 노드를 추가하는 함수입니다.
void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
	print_heap(h);  // 힙 삽입 후 상태 출력
}

//최소히프트리에서 노드를 삭제하는 함수입니다.
element delete_min_heap(HeapType* h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key < h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//이진트리를 생성하는 함수입니다.
Node* make_tree(Node* left, Node* right) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = left;
	node->right = right;
	return node;
}

//이진트리를 삭제하는 함수입니다.
void destroy_tree(Node* root) {
	if (root == NULL) return;
	destroy_tree(root->left);
	destroy_tree(root->right);
	free(root);
}

//단말노드를 확인하는 함수입니다.
int is_leaf(Node* root) {
	return !(root->left) && !(root->right);
}

//배열에 있는 값을 출력하는 함수입니다.
void print_array(int codes[], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d", codes[i]);
	}
	printf("\n");
}

//허프만 코드를 출력하는 함수입니다.
void print_codes(Node* root, int codes[], int top) {
	if (root->left) {
		codes[top] = 1;
		print_codes(root->left, codes, top + 1);
	}
	if (root->right) {
		codes[top] = 0;
		print_codes(root->right, codes, top + 1);
	}

	if (is_leaf(root)) {
		printf("%c: ", root->ch);
		print_array(codes, top);
	}
}

//허프만 코드 생성 함수입니다.
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
	int i;
	Node* node, * x;
	HeapType* heap;
	element e, e1, e2;
	int codes[100];
	int top = 0;

	heap = create();
	init(heap);
	for (i = 0; i < size; i++) {
		node = make_tree(NULL, NULL);
		e.ch = node->ch = characters[i];
		e.key = node->weight = frequencies[i];
		e.ptree = node;
		insert_min_heap(heap, e);
	}
	for (i = 1; i < size; i++) {
		//최소값 가지는 두 개의 노드를 삭제합니다.
		e1 = delete_min_heap(heap);
		e2 = delete_min_heap(heap);
		//두 개의 노드를 합칩니다.
		x = make_tree(e1.ptree, e2.ptree);
		e.key = x->weight = e1.key + e2.key;
		e.ptree = x;
		printf("///%d + %d -> %d \n", e1.key, e2.key, e.key);
		insert_min_heap(heap, e);
	}
	e = delete_min_heap(heap); //최종 트리
	print_codes(e.ptree, codes, top);
	destroy_tree(e.ptree);
	free(heap);
}
int main() {
	char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
	int frequencies[] = { 10, 15, 12, 3 ,4 ,13, 1 };
	int size = sizeof(characters) / sizeof(characters[0]);

	GenerateHuffmanCodes(characters, frequencies, size);

	return 0;
}
