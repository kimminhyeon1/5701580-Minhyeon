#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100 

// 전역 변수
int sorted[SIZE]; // 병합 과정에서 임시로 사용할 배열
int comparisonCount, moveCount, rounds = 0, totalComparisons = 0, totalMoves = 0, isFirst = 0;

// 배열의 각 요소를 0~999 사이의 난수로 초기화하는 함수
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000;
    }
}

// 전달받은 배열의 모든 요소를 출력하는 함수
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n\n");
}

// left ~ mid, mid+1 ~ right 구간의 두 배열을 정렬하며 병합하는 함수
void merge(int array[], int left, int mid, int right) {
    int i, j, k, l;
    i = left; j = mid + 1; k = left;

    // 두 부분 배열의 요소를 비교하며 병합함
    while (i <= mid && j <= right) {
        comparisonCount++;
        if (array[i] <= array[j]) {
            sorted[k++] = array[i++]; // 왼쪽 배열에서 선택
            moveCount++;
        }
        else {
            sorted[k++] = array[j++]; // 오른쪽 배열에서 선택
            moveCount++;
        }
    }
    // 오른쪽 배열에 남은 요소 병합함
    if (i > mid) {
        for (l = j; l <= right; l++) {
            sorted[k++] = array[l];
            moveCount++;
        }
    }
    // 왼쪽 배열에 남은 요소 병합함
    else {
        for (l = i; l <= mid; l++) {
            sorted[k++] = array[l];
            moveCount++;
        }
    }
    // 병합 결과를 원본 배열에 복사함
    for (l = left; l <= right; l++) {
        array[l] = sorted[l];
        moveCount++;
    }

    // 병합하는 과정을 출력하는 코드
    rounds++;
    if (rounds % 10 == 0 && isFirst == 0) { // 10번에 한 번만 출력함
        for (int i = 0; i < 10; i++) // 첫 10개 값
            printf("%3d ", array[i]);
        printf("| ");
        for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) // 중앙-1 ~ 중앙+10
            printf("%3d ", array[i]);
        printf("\n\n");
    }
}


// 반복적 Merge Sort 구현 함수, 배열을 일정 크기로 나누고, 점차 병합하며 정렬함
void iterativeMergeSort(int array[]) {
    int width, left, mid, right;

    // 병합할 구간의 크기를 1, 2, 4, ...로 증가시키며 반복함
    for (width = 1; width < SIZE; width *= 2) {
        // 배열의 각 구간에 대해 병합 수행함
        for (left = 0; left < SIZE - width; left += 2 * width) {
            mid = left + width - 1;
            right = (left + 2 * width - 1 < SIZE) ? (left + 2 * width - 1) : (SIZE - 1);
            merge(array, left, mid, right);
        }
    }
}

int main() {
    int array[SIZE];
    srand(time(NULL)); 

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Merge Sort Run\n");
            iterativeMergeSort(array);

            printf("Result\n");
            printArray(array, SIZE);
            isFirst++;
        }
        else {
            iterativeMergeSort(array);
        }
        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }
    printf("Average Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
