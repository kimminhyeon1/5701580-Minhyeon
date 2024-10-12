#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200

int moveCount; //노드가 이동한 횟수를 세기 위한 변수입니다.
typedef struct HeapType {
	int heap[MAX_ELEMENT];
	int heap_size;
}TreeNode;

//히프트리를 초기화하는 함수입니다.
void init(TreeNode* root) {
	root->heap_size = 0;
}

//최대히프트리에 원하는 값을 노드로 삽입하는 함수입니다.
void InsertMaxHeapTree(TreeNode* root, int inputData) {
	int i;
	i = ++(root->heap_size);

	//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정입니다.
	while ((i != 1) && (inputData > root->heap[i / 2])) {
		root->heap[i] = root->heap[i / 2];
		i /= 2; 
	}
	root->heap[i] = inputData;
}

//위와 같은 역할을 하지만 삽입되는 과정과 노드가 이동된 횟수를 출력하는 함수입니다.
void InsertMaxHeapTreePrintVersion(TreeNode* root, int inputData) {
	int i;
	i = ++(root->heap_size);
	moveCount = 0;

	while ((i != 1) && (inputData > root->heap[i / 2])) {
		root->heap[i] = inputData;
		for (int j = 1; j <= root->heap_size; j++) { //히프트리에서 값이 교환되는 과정을 출력합니다.
			printf("%d ", root->heap[j]);
		}
		printf("\n");
		root->heap[i] = root->heap[i / 2];
		i /= 2; //거슬러 올라갈 때
		moveCount++;  //노드 이동횟수 올립니다.
	}
	root->heap[i] = inputData; //새로운 노드를 삽입합니다.
	for (int j = 1; j <= root->heap_size; j++) { //히프트리에서 값이 교환되는 과정을 출력합니다.
		printf("%d ", root->heap[j]);
	}
	printf("\n");
}

//최대히프트리에서 루트노드를 삭제하고 재배열하는 함수입니다.
int DeleteMaxHeapTree(TreeNode* root) {
	int parent, child;
	int item, temp;
	moveCount = 0;

	item = root->heap[1];
	temp = root->heap[(root->heap_size)--]; // 마지막 노드를 저장합니다.
	parent = 1;
	child = 2;

	//히프트리의 모든 노드를 출력할 때까지 반복합니다.
	while (child <= root->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 찾습니다.
		if ((child < root->heap_size) && (root->heap[child] < root->heap[child + 1])) { 
			child++; // 오른쪽 자식으로 이동
			moveCount++; // 노드 이동횟수 올립니다.
		}
		if (temp >= root->heap[child]) break;

		root->heap[parent] = temp; //마지막 노드를 현위치에 저장합니다.
		
		//마지막 노드가 어디에 위치하는지 출력합니다.
		for (int j = 1; j <= root->heap_size; j++) { 
			printf("%d ", root->heap[j]);
		}
		printf("\n");

		root->heap[parent] = root->heap[child];
		parent = child;
		child *= 2; // 한 단계 아래로 이동할 때
		moveCount++; // 노드 이동횟수 올립니다.
	}
	root->heap[parent] = temp;

	//마지막 노드가 올바른 위치에 도달한 히프트리를 출력합니다.
	for (int j = 1; j <= root->heap_size; j++) { 
		printf("%d ", root->heap[j]);
	}
	printf("\n");

	return item;
}

//히프트리를 레벨별로 출력하는 함수입니다.
void display_heap_by_level(TreeNode* root){
	int level = 1, index = 1;

	printf("트리 레벨별 출력\n");
	//히프트리의 모든 노드를 출력할 때까지 반복합니다.
	while (index <= root->heap_size) {
		printf("[%d] ", level);

		// 현재 레벨의 노드 수를 계산합니다.
		int nodesAtLevel = (1 << (level - 1)); 

		//현재 레벨의 모든 노드를 출력합니다.
		for (int i = 0; i < nodesAtLevel && index <= root->heap_size; i++) {
			printf("%d ", root->heap[index++]);
		}
		printf("\n");

		level++;
	}
}

//최대히프트리를 인수로 받은 배열에 맞게 생성하는 함수입니다.
TreeNode* generateMaxHeapTree(int inputData[], int size) {
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
	init(root);

	for (int i = 0; i < size; i++) {
		InsertMaxHeapTree(root, inputData[i]);
	}
	root->heap_size = size;
	
	return root;
}

//노드 추가, 노드 삭제, 레벨별 출력 중에 하나의 메뉴를 입력받으면 
// 메뉴에 맞는 일을 수행하도록 하는 함수입니다.
void runUserInterface(TreeNode* root) {
	
	while (1) {
		int data = 0;
		char menuNumber;
		printf("\n");
		printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
		printf("| i	: 노드 추가      |\n");
		printf("| d	: 노드 삭제      |\n");
		printf("| p	: 레벨별 출력    |\n");
		printf("| c	: 종료           |\n");
		printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n");
		printf("메뉴 입력: ");
		scanf("%c", &menuNumber);
		getchar();

		switch (menuNumber) {
		case 'i':
			printf("추가할 값 입력: ");
			scanf("%d", &data);
			getchar();
			InsertMaxHeapTreePrintVersion(root, data);
			printf("노드가 이동한 횟수: %d\n", moveCount);
			break;
		case 'd':
			DeleteMaxHeapTree(root);
			printf("노드가 이동한 횟수: %d\n", moveCount);
			break;
		case 'p':
			display_heap_by_level(root);
			break;
		case 'c':
			exit(1);
		default:
			printf("잘못된 입력입니다.\n");
			getchar();
			break;
		}
	}
}
int main() {
	int inputData[] = { 90, 89, 70, 36, 75, 63, 13, 21, 18, 15};
	int size = 10;

	TreeNode* root = generateMaxHeapTree(inputData, size);

	runUserInterface(root);

	free(root);

	return 0;
}
