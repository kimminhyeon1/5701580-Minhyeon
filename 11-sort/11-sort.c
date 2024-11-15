#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

// srand함수를 통해 임의의 수를 배열에 삽입
int generateRandomData(int list[], int n) {
	srand(time(NULL) - n); // srand()를 함수 안에 집어넣게 되어 프로그램이 실행된 후에는 호출할 때마다 같은 리스트를 호출하므로 
						   // 시드값을 매개변수를 통해 직접 수정할 수 있게 설정
	for (int i = 0; i < SIZE; i++) {
		list[i] = rand() % 1000;
	}
	return list;
}

// 리스트에 있는 모든 정수 값을 출력하는 함수
void print_list(int list[]) {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", list[i]);
	}
	printf("\n\n");
}

// 리스트를 선택정렬방식으로 정렬하는 함수
void doSelectionSort(int list[]) {
	int i, j, least, temp;
	printf("Selection Sort:\n");
	for (i = 0; i < SIZE - 1; i++) {
		least = i;
		for (j = i + 1; j < SIZE; j++) {
			if (list[j] < list[least]) least = j;
		}
		SWAP(list[i], list[least], temp);
		// 10, 30, 50, 70, 90, 99번째로 정렬된 리스트를 출력
		if (i == 9 || i == 29 || i == 49 || i == 69 || i == 89 || i == 98) { 
			printf("Step %d: ", i + 1);
			print_list(list);
		}
	}
}

// 리스트를 삽입정렬방식으로 정렬하는 함수
void doInsertionSort(int list[]) {
	int i, j, key;
	int re_count = 0, sumCompare = 0;
	// 20번 반복해서 다른 리스트를 불러와 삽입정렬 실시, 마지막엔 선택정렬을 했던 리스트로 삽입정렬 실시
	for (int re = 19; re >= 0; re--, re_count++) {
		int compare = 0;
		generateRandomData(list, re * 2); // 다른 리스트 생성
		for (i = 1; i < SIZE; i++) {
			key = list[i];
			for (j = i - 1; j >= 0 && list[j] > key; j--) {
				list[j + 1] = list[j];
				compare++; // 정렬을 위해 값을 비교했다면 compare(비교횟수)값 증가
			}
			list[j + 1] = key;
		}
		sumCompare += compare;
	}
	printf("Insertion Sort Compare Average: %d\n", sumCompare / re_count);
	printf("Insertion Sort Result:\n");
	print_list(list);
	printf("\n");
}

// 리스트를 버블정렬함수로 정렬하는 함수
void doBubbleSort(int list[]) {
	int i, j, temp, flag;
	int re_count = 0, sumMove = 0;
	// 20번 반복해서 다른 리스트를 불러와 버블정렬 실시, 마지막엔 선택정렬을 했던 리스트로 정렬 실시
	for (int re = 19; re >= 0; re--, re_count++) {
		int move = 0;
		generateRandomData(list, re); // 다른 리스트 생성
		for (i = SIZE - 1; i > 0; i--) {
			flag = 0;
			for (j = 0; j < i; j++) {
				if (list[j] > list[j + 1]) {
					SWAP(list[j], list[j + 1], temp);
					move += 3; //SWAP에서 데이터 이동이 3번 이루어 졌으므로 SWAP을 할 때마다 move(이동횟수)값 3 증가
					flag = 1;
				}
			}
			if (flag == 0) break; // flag가 0이면 정렬이 다 되어 스캔을 더이상 하지않아도 된다고 판단
		}
		sumMove += move;
	}
	printf("Bubble Sort Move Average: %d\n", sumMove / re_count);
	printf("Bubble Sort Result:\n");
	print_list(list);
	printf("\n");
}

int main() {
	int randomData[SIZE];
	generateRandomData(randomData, 0);

	doSelectionSort(randomData);
	doInsertionSort(randomData);
	doBubbleSort(randomData);

	return 0;
}
