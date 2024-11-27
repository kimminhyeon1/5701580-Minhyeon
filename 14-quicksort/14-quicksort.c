#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // 값 교환을 위한 식


int comparisonCount, moveCount, rounds = 0, totalComparisons = 0, totalMoveCount = 0, isFirst = 0;

// 배열에 랜덤 값을 채워넣는 함수
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0부터 999까지의 랜덤 숫자 생성함
    }
}

// 배열의 내용을 n개 출력하는 함수
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n\n");
}

// 배열의 특정 구간(left ~ right)을 분할하고, 피벗 위치를 반환하는 함수
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
            comparisonCount++; // 비교 횟수 증가
        } while (low <= right && array[low] < pivot);

        do { // 오른쪽에서 피벗보다 작은 값을 찾음
            high--;
            comparisonCount++; // 비교 횟수 증가
        } while (high >= left && array[high] > pivot);

        // low와 high 위치의 값을 교환 (low < high일 때만)
        if (low < high) {
            SWAP(array[low], array[high], temp);
            moveCount += 3; // 3번의 이동 발생 (스왑)
        }
    } while (low < high);

    // 피벗을 중앙으로 이동
    SWAP(array[left], array[high], temp);
    moveCount += 3; // 3번의 이동 발생 (스왑)

    return high; // 새로운 피벗의 위치 반환
}

// 반복적 방식의 퀵 정렬 함수 (배열로 구현한 스택 구조를 이용)
void doQuickSort(int array[], int left, int right) {
    int stack[SIZE]; // 스택을 이용해 분할 작업 관리
    int top = -1;    // 스택의 최상위 인덱스

    // 초기 분할 구간을 스택에 삽입함
    stack[++top] = left;
    stack[++top] = right;

    // 스택이 비어있지 않은 동안 반복함
    while (top >= 0) {
        right = stack[top--]; // 오른쪽 경계값 꺼내기
        left = stack[top--];  // 왼쪽 경계값 꺼내기

        int q = partition(array, left, right); // 현재 구간을 분할함

        // 분할된 왼쪽 구간을 스택에 삽입함
        if (q - 1 > left) {
            stack[++top] = left;
            stack[++top] = q - 1;
        }

        // 분할된 오른쪽 구간을 스택에 삽입함
        if (q + 1 < right) {
            stack[++top] = q + 1;
            stack[++top] = right;
        }

        // 10번에 한 번씩 특정 구간(40 ~ 60)의 정렬 과정을 출력함
        // 처음 한 번만 과정을 출력하는 아래 코드를 실행함
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", array[i]); 
            printf("\n\n");
        }
        rounds++;
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL)); // 랜덤 숫자 생성 시드 설정
    int array[SIZE];   // 정렬할 배열

    // 평균을 구하기 위해 20번의 정렬 시도
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // 배열 초기화
        comparisonCount = 0;        // 비교 횟수 초기화
        moveCount = 0;              // 이동 횟수 초기화

        if (i == 0) { // 첫 번째 시도일 경우, 퀵 정렬 후 추가로 출력함
            printf("Iterative Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); 

            printf("Result\n");
            printArray(array, SIZE); // 정렬된 배열 출력
            isFirst++; // 첫 번째 실행이 끝났음을 표시
        }
        else { // 첫 번째가 아닐 경우, 퀵 정렬만 실행함
            doQuickSort(array, 0, SIZE - 1);
        }

        // 총 비교 횟수 및 이동 횟수 누적 후
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // 평균 비교 횟수와 이동 횟수 출력함
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}
