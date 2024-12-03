#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int LinearCompareCount, compareCount = 0, BinaryCompareCount;

// 0~999 사이의 임의의 숫자 1000개를 생성하는 함수
// 배열의 각 요소를 무작위로 설정하여 테스트에 사용할 데이터 생성
void generateRandomArray(int list[]) {
	for (int i = 0; i < SIZE; i++) { // 1000번
		list[i] = rand() % 1000; // 0~999 사이의 수
	}
}

// 정렬된 배열의 처음부터 20번째, 뒤에서 20번째~마지막을 출력하는 함수
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%3d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%3d ", array[i]);
	printf("\n");
}

// key값을 계속 달리하며 100번 순차 탐색을 실시 후, 그 과정을 통해 구한 평균 비교 횟수를 반환하는 함수
// 순차 탐색의 성능을 비교 횟수로 측정하기 위한 목적으로 작성
float getAverageLinearSearchCompareCount(int array[]) {
	int index;
	int totalComparisons = 0;
	for (int re = 0; re < 100; re++) { // 100번 반복
		LinearCompareCount = 0; // 비교 횟수 0으로 초기화
		int key = array[rand() % 1000]; // 매번 찾는 키 값 다르게 설정
		for (int i = 0; i <= SIZE; i++) { // 배열 인덱스 하나씩 올림
			LinearCompareCount++; // 배열 값과 키 값 비교할 때마다 비교 횟수 올림
			if (array[i] == key) { // 찾으려는 키 값을 가진 배열 값을 찾으면
				break; // 이번 탐색을 끝냄
			}
		}
		totalComparisons += LinearCompareCount; // 총 비교 횟수
	}
	return totalComparisons / 100.0; // 100회 평균 비교 횟수
}

// 배열의 특정 구간(left ~ right)을 분할하고, 피벗 위치를 반환하는 함수
// 퀵 정렬에서 분할(Partition) 작업을 수행
int partition(int array[], int left, int right) {
	int pivot, temp;
	int low, high;

	low = left;               // low는 배열의 시작 인덱스
	high = right + 1;         // high는 끝 인덱스 + 1 (do-while문에서 하나 빼면서 시작하기 때문)
	pivot = array[left];      // 배열의 첫 번째 요소를 피벗으로 설정함

	// 피벗을 기준으로 배열을 분할할 것임
	do {
		do { // 왼쪽에서 피벗보다 큰 값을 찾음
			low++;
			compareCount++; // 비교 횟수 증가
		} while (low <= right && array[low] < pivot);

		do { // 오른쪽에서 피벗보다 작은 값을 찾음
			high--;
			compareCount++; // 비교 횟수 증가
		} while (high >= left && array[high] > pivot);

		// low와 high 위치의 값을 교환 (low < high일 때만)
		if (low < high) {
			SWAP(array[low], array[high], temp);
		}
	} while (low < high);

	// 피벗을 중앙으로 이동
	SWAP(array[left], array[high], temp);

	return high; // 새로운 피벗의 위치 반환
}

// 재귀적 퀵정렬 함수
void doQuickSort(int array[], int left, int right) {
	if (left < right) {
		int q = partition(array, left, right);
		doQuickSort(array, left, q - 1);
		doQuickSort(array, q + 1, right);
	}
}

// 함수 이름과 매개변수 동일하게 하기 위해 설정한 함수
void getQuickSortCompareCount(int array[]) {
	doQuickSort(array, 0, SIZE - 1);
}

// key값을 계속 달리하며 100번 이진 탐색을 실시 후, 그 과정을 통해 구한 평균 비교 횟수를 반환하는 함수
// 정렬된 배열에서 이진 탐색의 성능을 비교 횟수로 측정
float getAverageBinarySearchCompareCount(int array[]) {
	int totalComparisons = 0; // 모든 탐색에서 비교 횟수의 합계를 저장

	for (int re = 0; re < 100; re++) { // 100번 반복
		int key = array[rand() % 1000]; // 매번 찾는 키 값을 무작위로 설정
		BinaryCompareCount = 0; // 비교 횟수를 0으로 초기화

		int middle;
		int low = 0, high = SIZE - 1; // 배열의 탐색 구간을 처음부터 끝까지 설정
		while (low <= high) { // 탐색 구간이 존재하는 동안 반복
			middle = (low + high) / 2; // 중간 인덱스를 계산
			if (key == array[middle]) { // 중간 값이 찾는 값과 일치하면
				BinaryCompareCount++; // 비교 횟수 증가
				break; // 탐색 종료
			}
			else if (key > array[middle]) { // 찾는 값이 중간 값보다 크다면
				BinaryCompareCount++; // 비교 횟수 증가
				low = middle + 1; // 탐색 구간의 시작을 중간 오른쪽으로 이동
			}
			else { // 찾는 값이 중간 값보다 작다면
				BinaryCompareCount++; // 비교 횟수 증가
				high = middle - 1; // 탐색 구간의 끝을 중간 왼쪽으로 이동
			}
		}
		totalComparisons += BinaryCompareCount; // 이번 탐색의 비교 횟수를 합산
	}
	return totalComparisons / 100.0; // 평균 비교 횟수를 반환
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);
	//평균값을 반환받기 위한 조치
	printf("Average Linear Search Compare Count: %.2f\n",
		getAverageLinearSearchCompareCount(array));
	//compareCount가 global variable이므로, 다음과 같이 구현
	//array에 대해서 직접 정렬하면 된다.
	getQuickSortCompareCount(array);
	printf("Quick Sort Compare Count: %d\n", compareCount);
	//정렬된 Array에 대해서 Binary Search 100회 수행 및 평균 비교횟수 출력
	printf("Average Binary Search Compare Count: %.2f\n\n",
		getAverageBinarySearchCompareCount(array));
	printArray(array);
	return 0;
}
