#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t))

int compareCount = 0, BinaryCompareCount, InterpolationCompareCount;

// 0~9999 사이의 임의의 숫자 1000개를 생성하는 함수
// 배열의 각 요소를 무작위로 설정하여 테스트에 사용할 데이터 생성
void generateRandomArray(int list[]) {
	for (int i = 0; i < SIZE; i++) {
		list[i] = rand() % 10000;
	}
}

// 배열의 특정 구간(left ~ right)을 분할하고, 피벗 위치를 반환하는 함수
// 퀵 정렬에서 분할 작업을 수행
int partition(int array[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = array[left];
	do {
		do {
			low++;
			compareCount++;
		} while (low <= right && array[low] < pivot);
		do {
			high--;
			compareCount++;
		} while (high >= left && array[high] > pivot);
		if (low < high) {
			SWAP(array[low], array[high], temp);
		}
	} while (low < high);

	SWAP(array[left], array[high], temp);
	return high;
}

// 재귀적 퀵정렬 함수
void QuickSort(int array[], int left, int right) {
	if (left < right) {
		int q = partition(array, left, right);
		QuickSort(array, left, q - 1);
		QuickSort(array, q + 1, right);
	}
}

// 정렬된 배열의 처음부터 20번째, 뒤에서 20번째~마지막을 출력하는 함수
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++)
		printf("%4d ", array[i]);
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++)
		printf("%4d ", array[i]);
	printf("\n\n");
}

// key값을 계속 달리하며 1000번 이진 탐색을 실시 후, 그 과정을 통해 구한 평균 비교 횟수를 반환하는 함수
// 정렬된 배열에서 이진 탐색의 성능을 비교 횟수로 측정
double getAverageBinarySearchCompareCount(int array[]) {
	int totalComparisons = 0; // 모든 탐색에서 비교 횟수의 합계를 저장

	for (int re = 0; re < 1000; re++) { // 1000번 반복
		int key = array[rand() % SIZE]; // 매번 찾는 키 값 다르게 설정
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
	return totalComparisons / 1000.0; // 평균 비교 횟수를 반환
}

// key값을 계속 달리하며 1000번 보간 탐색을 실시 후, 그 과정을 통해 구한 평균 비교 횟수를 반환하는 함수
// 정렬된 배열에서 보간 탐색의 성능을 비교 횟수로 측정
double getAverageInterpolationSearchComparecount(int array[]) {
	int low, high, j;
	int totalComparisons = 0; // 모든 탐색에서 비교 횟수의 합계를 저장

	for (int re = 0; re < 1000; re++) { // 1000번 반복
		int key = array[rand() % SIZE]; // 배열 내 존재하는 임의의 값을 키 값으로 설정
		InterpolationCompareCount = 0; // 비교 횟수 초기화

		low = 0, high = SIZE - 1; // 배열의 탐색 구간 설정
		while ((array[high] >= key) && (key > array[low])) { // 탐색 구간 안에 키 값이 존재하면 반복
			// 키 값과 현재의 low, high 위치의 값을 고려하여 탐색위치 결정
			j = ((double)(key - array[low]) / (array[high] - array[low]) * (high - low)) + low;
			if (key > array[j]) { // 키 값이 탐색위치의 값보다 크면 
				low = j + 1; // low값을 늘려 탐색 위치 조정
				InterpolationCompareCount++; // 값 비교가 있었으므로 비교 횟수 증가
			}
			else if (key < array[j]) { // 키 값이 탐색위치의 값보다 작으면 
				high = j - 1; // high 위치를 줄여 탐색 위치 조정
				InterpolationCompareCount++; // 값 비교가 있었으므로 비교 횟수 증가
			}
			else { // 키 값과 탐색위치의 값이 같다면
				low = j; // low에 탐색위치 저장
				InterpolationCompareCount++; // 값 비교가 있었으므로 비교 횟수 증가
			}
		}
		
		// 원래 탐색 성공했는지 비교하고 low를 리턴하는 부분이지만 여기서는 탐색이 성공한지만 확인
		if (array[low] == key) InterpolationCompareCount++;
		else InterpolationCompareCount++;

		totalComparisons += InterpolationCompareCount; // 이번 탐색의 비교 횟수를 합산
	}
	return totalComparisons / 1000.0; // 평균 비교 횟수를 반환
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);

	QuickSort(array, 0, SIZE - 1);
	printArray(array);

	printf("Average Compare Count of Binary Search: %.2f\n",
		getAverageBinarySearchCompareCount(array));

	printf("Average Compare Count of Interpolation Search: %.2f\n",
		getAverageInterpolationSearchComparecount(array));

	return 0;
}