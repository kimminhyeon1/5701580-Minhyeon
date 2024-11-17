#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_SIZE 100

// 배열에 임의의 수를 삽입하는 함수, srand를 이용해 랜덤하게 생성된 수를 배열에 저장
void generateRandomNumbers(int list[], int n) {
    srand(time(NULL) - n); // n에 따라 seed를 다르게 설정하여 다양한 랜덤 배열 생성
    for (int i = 0; i < ARRAY_SIZE; i++) {
        list[i] = rand() % 1000; 
    }
}

// 배열의 일부(앞부분 20개)만 출력하는 함수
void semi_print_list(int list[]) {
    for (int i = 0; i < 20; i++) // 배열의 첫 20개 요소 출력
        printf("%d ", list[i]);
    printf("...\n\n");
}

// 배열 전체를 출력하는 함수, 정렬 결과나 최종 배열 상태를 확인하기 위해 사용
void print_list(int list[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) // 배열 전체 출력
        printf("%d ", list[i]);
    printf("\n\n");
}

// 간격(gap)을 활용한 삽입 정렬, Shell Sort의 일부 단계로 사용
void gap_insertion_sort(int list[], int first, int last, int gap, int* comparisonCount, int* moveCount) {
    int i, j, key;

    for (i = first + gap; i <= last; i += gap) { // gap 간격으로 요소 순회
        key = list[i]; // 현재 요소를 key로 설정
        (*moveCount)++; // key(temp)에 list의 아직 정렬되지 않은 값 하나를 넣었으므로 이동 횟수 증가
        for (j = i - gap; j >= first; j -= gap) {
            (*comparisonCount)++; // 이전 요소들과 비교할 때마다 비교 횟수 증가
            if (list[j] > key) { 
                list[j + gap] = list[j]; 
                (*moveCount)++; // key보다 크면 이동하므로 이동 횟수 증가
            }
            else break; // key보다 작거나 같으면 종료
        }
        list[j + gap] = key; 
        (*moveCount)++; // 적절한 위치에 key 삽입하므로 이동 횟수 증가
    }
}

// Shell Sort 실행 함수, 다양한 간격(gap) 규칙을 적용해 정렬 수행
void doShellSort(int list[], int gap_rule, int* comparisonCount, int* moveCount) {
    int i, re, gap, control = 1; // control은 첫 실행에만 배열 출력 여부 결정
    *comparisonCount = 0;
    *moveCount = 0;

    for (re = 0; re < 20; re++) { // 20번 랜덤 배열 생성 및 정렬
        generateRandomNumbers(list, re); // 새로운 배열 생성
        for (gap = (int)ARRAY_SIZE / gap_rule; gap > 0; gap = (int)gap / gap_rule) { // gap 규칙 적용
            if (control == 1) {
                printf("Sorting with gap = %d:\n", gap);
            }
            if ((gap % gap_rule) == 0) gap = gap + 1; // gap 규칙 보정
            for (i = 0; i < gap; i++) { // gap 별로 삽입 정렬 수행
                gap_insertion_sort(list, i, ARRAY_SIZE - 1, gap, comparisonCount, moveCount);
            }
            if (control == 1) {
                semi_print_list(list); // 정렬 중간 상태 출력
            }
        }
        if (control == 1) { // 첫 실행 시 정렬 결과 출력
            printf("Sorted shellArray (gap = %d):\n", gap_rule);
            print_list(list);
            control = 0;
        }
    }
    *comparisonCount /= re; // 평균 비교 횟수 계산
    *moveCount /= re; // 평균 이동 횟수 계산
}

// 삽입 정렬 실행 함수, 비교와 이동 횟수를 계산하며 정렬 수행
void doInsertionSort(int list[], int* comparisonCount, int* moveCount) {
    int i, j, re, key, control = 1;
    *comparisonCount = 0;
    *moveCount = 0;

    for (re = 0; re < 20; re++) { // 20번 랜덤 배열 생성 및 정렬
        generateRandomNumbers(list, re); // 다른 리스트 생성
        for (i = 1; i < ARRAY_SIZE; i++) { // 정렬 시작
            key = list[i];
            (*moveCount)++; // key(temp)에 list의 아직 정렬되지 않은 값 하나를 넣었으므로 이동 횟수 증가
            for (j = i - 1; j >= 0 && list[j] > key; j--) { // 삽입 위치 탐색
                (*comparisonCount)++; // list에 특정값과 key값을 비교하므로 비교 횟수 증가
                list[j + 1] = list[j];
                (*moveCount)++; // 조건이 충족되면 값 교환을 위해 이동하므로 이동 횟수 증가
            }
            list[j + 1] = key;
            (*moveCount)++; // key(temp)에 넣어놓은 값을 list의 적절한 위치에 삽입하므로 이동 횟수 증가
        }
        if (control == 1) { // 첫 실행 시 정렬 결과 출력
            printf("Sorted insertionArray:\n");
            print_list(list);
            control = 0;
        }
    }
    *moveCount /= re; // 평균 이동 횟수 계산
    *comparisonCount /= re; // 평균 비교 횟수 계산
}

int main() {
    int array[ARRAY_SIZE];
    int comparisonCount, moveCount;
    generateRandomNumbers(array, 0);

    // Shell Sort
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &comparisonCount, &moveCount);
    printf("Shell Sort (n/2) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &comparisonCount, &moveCount);
    printf("Shell Sort (n/3) - Comparisons: %d, Moves: %d\n\n", comparisonCount, moveCount);

    // Insertion Sort
    printf("Insertion Sort:\n");
    doInsertionSort(array, &comparisonCount, &moveCount);
    printf("Insertion Sort - Comparisons: %d, Moves: %d\n", comparisonCount, moveCount);

    return 0;
}
