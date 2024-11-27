#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
#define SWAP(x, y, t) ((t)=(x), (x)=(y), (y)=(t)) // �� ��ȯ�� ���� ��


int comparisonCount, moveCount, rounds = 0, totalComparisons = 0, totalMoveCount = 0, isFirst = 0;

// �迭�� ���� ���� ä���ִ� �Լ�
void generateRandomArray(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0���� 999������ ���� ���� ������
    }
}

// �迭�� ������ n�� ����ϴ� �Լ�
void printArray(int list[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", list[i]);
    printf("\n\n");
}

// �迭�� Ư�� ����(left ~ right)�� �����ϰ�, �ǹ� ��ġ�� ��ȯ�ϴ� �Լ�
int partition(int array[], int left, int right) {
    int pivot, temp;
    int low, high;

    low = left;               // low�� �迭�� ���� �ε���
    high = right + 1;         // high�� �� �ε��� + 1 (do-while������ �ϳ� ���鼭 �����ϱ� ����)
    pivot = array[left];      // �迭�� ù ��° ��Ҹ� �ǹ����� ������

    // �ǹ��� �������� �迭�� ������ ����
    do {
        do { // ���ʿ��� �ǹ����� ū ���� ã��
            low++;
            comparisonCount++; // �� Ƚ�� ����
        } while (low <= right && array[low] < pivot);

        do { // �����ʿ��� �ǹ����� ���� ���� ã��
            high--;
            comparisonCount++; // �� Ƚ�� ����
        } while (high >= left && array[high] > pivot);

        // low�� high ��ġ�� ���� ��ȯ (low < high�� ����)
        if (low < high) {
            SWAP(array[low], array[high], temp);
            moveCount += 3; // 3���� �̵� �߻� (����)
        }
    } while (low < high);

    // �ǹ��� �߾����� �̵�
    SWAP(array[left], array[high], temp);
    moveCount += 3; // 3���� �̵� �߻� (����)

    return high; // ���ο� �ǹ��� ��ġ ��ȯ
}

// �ݺ��� ����� �� ���� �Լ� (�迭�� ������ ���� ������ �̿�)
void doQuickSort(int array[], int left, int right) {
    int stack[SIZE]; // ������ �̿��� ���� �۾� ����
    int top = -1;    // ������ �ֻ��� �ε���

    // �ʱ� ���� ������ ���ÿ� ������
    stack[++top] = left;
    stack[++top] = right;

    // ������ ������� ���� ���� �ݺ���
    while (top >= 0) {
        right = stack[top--]; // ������ ��谪 ������
        left = stack[top--];  // ���� ��谪 ������

        int q = partition(array, left, right); // ���� ������ ������

        // ���ҵ� ���� ������ ���ÿ� ������
        if (q - 1 > left) {
            stack[++top] = left;
            stack[++top] = q - 1;
        }

        // ���ҵ� ������ ������ ���ÿ� ������
        if (q + 1 < right) {
            stack[++top] = q + 1;
            stack[++top] = right;
        }

        // 10���� �� ���� Ư�� ����(40 ~ 60)�� ���� ������ �����
        // ó�� �� ���� ������ ����ϴ� �Ʒ� �ڵ带 ������
        if (rounds % 10 == 0 && isFirst == 0) {
            for (int i = 40; i < 60; i++)
                printf("%d ", array[i]); 
            printf("\n\n");
        }
        rounds++;
    }
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    srand(time(NULL)); // ���� ���� ���� �õ� ����
    int array[SIZE];   // ������ �迭

    // ����� ���ϱ� ���� 20���� ���� �õ�
    for (int i = 0; i < 20; i++) {
        generateRandomArray(array); // �迭 �ʱ�ȭ
        comparisonCount = 0;        // �� Ƚ�� �ʱ�ȭ
        moveCount = 0;              // �̵� Ƚ�� �ʱ�ȭ

        if (i == 0) { // ù ��° �õ��� ���, �� ���� �� �߰��� �����
            printf("Iterative Quick Sort Run\n");
            doQuickSort(array, 0, SIZE - 1); 

            printf("Result\n");
            printArray(array, SIZE); // ���ĵ� �迭 ���
            isFirst++; // ù ��° ������ �������� ǥ��
        }
        else { // ù ��°�� �ƴ� ���, �� ���ĸ� ������
            doQuickSort(array, 0, SIZE - 1);
        }

        // �� �� Ƚ�� �� �̵� Ƚ�� ���� ��
        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    // ��� �� Ƚ���� �̵� Ƚ�� �����
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);
    return 0;
}
