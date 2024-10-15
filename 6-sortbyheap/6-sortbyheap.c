#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

typedef struct HeapType {
	int heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//힙 초기화 함수
void init(HeapType* h) {
	h->heap_size = 0;
}

//최대 힙 형식으로 삽입하는 함수
void InsertMaxHeapTree(HeapType* h, int inputData) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (inputData > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = inputData;
	for (int j = 1; j <= h->heap_size; j++) {
		printf("%d ", h->heap[j]);
	}
	printf("\n");
}

//노드를 추가하는 함수를 반복적으로 사용해 최대히프트리를 만드는 함수
void BuildMaxHeap(HeapType* h, int inputData[], int n) {
	for (int i = 0; i < n; i++) {
		InsertMaxHeapTree(h, inputData[i]);
	}
	h->heap_size = n;
}

//루트와 마지막 요소를 교환해주기 위한 함수
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

//최대 힙을 생성하고 힙을 재정렬하는 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
	HeapType h;
	init(&h);
	// 최대 힙 생성
	BuildMaxHeap(&h, inputData, n);

	// 힙 정렬
	for (int i = n - 1; i > 0; i--) {
		// 루트와 마지막 요소 교환
		swap(&h.heap[1], &h.heap[h.heap_size]);
		h.heap_size--;

		// 힙 재정렬
		int parent = 1;
		int child = 2;
		int temp = h.heap[parent];

		while (child <= h.heap_size) {
			if ((child < h.heap_size) && (h.heap[child] < h.heap[child + 1])) {
				child++;
			}
			if (temp >= h.heap[child]) break;

			h.heap[parent] = h.heap[child];
			parent = child;
			child *= 2;
		}
		h.heap[parent] = temp;

		// 현재 힙 상태 출력
		for (int j = 1; j <= h.heap_size; j++) {
			printf("%d ", h.heap[j]);
		}
		printf("\n");
	}

	// 정렬된 배열을 다시 입력 배열에 복사
	for (int i = 0; i < n; i++) {
		inputData[i] = h.heap[i + 1];
	}
}

int main() {
	int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
	int size = sizeof(inputData) / sizeof(inputData[0]);

	printf("<Sort>\n");
	BuildMaxHeapAndSort(inputData, size);

	printf("\nSorted Array:\n");
	for (int i = 0; i < size; i++) {
		printf("%d ", inputData[i]);
	}
	printf("\n");

	return 0;
}
