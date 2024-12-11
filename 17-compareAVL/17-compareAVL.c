#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// 전역 변수: 비교 횟수, 탐색 횟수
int compareCount = 0;
int searchCount = 0;

//Binary 트리 관련 함수들

// 이진 탐색 트리 삽입 함수
Node* insertBST(Node* root, int value) {
    if (root == NULL) { // 트리가 없으면 노드 생성해서 루트로 설정
        root = (Node*)malloc(sizeof(Node));
        root->value = value;
        root->left = root->right = NULL;
        return root;
    }
    if (value < root->value) { // 삽입하려는 값이 루트노드 값보다 작으면 왼쪽으로 삽입
        root->left = insertBST(root->left, value);
    }
    else if (value > root->value) { // 삽입하려는 값이 루트노드 값보다 크면 오른쪽으로 삽입
        root->right = insertBST(root->right, value);
    }
    return root;
}

// 이진 탐색 트리 삭제 함수
Node* deleteBST(Node* root, int value) {
    if (root == NULL) { // 삭제할 노드가 없음
        return root;  
    }

    // 값 비교 
    if (value < root->value) { // 삭제하려는 값이 루트 값보다 작을 때
        root->left = deleteBST(root->left, value);
    }
    else if (value > root->value) { // 삭제하려는 값이 루트 값보다 클 때
        root->right = deleteBST(root->right, value);
    }
    else { // 삭제할 노드를 찾음
        if (root->left == NULL) {  // 왼쪽 자식이 없는 경우
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {  // 오른쪽 자식이 없는 경우
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // 자식이 둘인 경우: 중위 순회 후속자 노드로 교체
        Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->value = temp->value;  // 후속자 값 복사
        root->right = deleteBST(root->right, temp->value);  // 후속자 노드 삭제
    }
    return root;
}

// 이진 트리 탐색하는 함수
Node* searchBST(Node* root, int value) {
    compareCount++; // 비교 횟수 증가
    if (root == NULL || root->value == value) {
        return root; // 값을 찾았거나 트리가 비었을 경우 반환
    }
    if (value < root->value) {
        compareCount++; // 비교 횟수 증가
        return searchBST(root->left, value); // 왼쪽 서브트리 탐색
        
    }
    else {
        compareCount++; // 비교 횟수 증가
        return searchBST(root->right, value); // 오른쪽 서브트리 탐색
    }
}

// 이진 탐색 트리 (BST) 배치 작업하는 함수
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int operation = rand() % 3;
        int value = rand() % 1000;

        if (operation == 0) {  // 0이면 삽입
            root = insertBST(root, value);
        }
        else if (operation == 1) {  // 1이면 삭제
            root = deleteBST(root, value);
        }
        else if (operation == 2) {  // 2이면 탐색
            searchBST(root, value);
            searchCount++;
        }
    }
}

// AVL 트리 관련 함수들

// 노드가 NULL이면 0을 반환, 그렇지 않으면 노드의 높이를 반환하는 함수
int height(Node* node) {
    return (node == NULL) ? 0 : node->height;
}

// 노드의 균형 인수를 계산하는 함수 (균형 인수는 왼쪽 서브트리의 높이에서 오른쪽 서브트리의 높이를 뺀 값)
int getBalance(Node* node) {
    return (node == NULL) ? 0 : height(node->left) - height(node->right);
}

// 오른쪽으로 회전 (Right Rotate) 함수 (LL(Left-Left) 불균형을 해결하기 위한 회전)
Node* rightRotate(Node* y) {
    Node* x = y->left; // y의 왼쪽 자식을 x로 설정
    Node* T2 = x->right; // x의 오른쪽 서브트리를 T2로 저장

    x->right = y; // x의 오른쪽 자식으로 y를 설정
    y->left = T2; // y의 왼쪽 자식으로 T2를 설정

    // y와 x의 높이를 업데이트
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x; // 새로운 루트 노드 반환
}

// 왼쪽으로 회전 (Left Rotate) 함수 (RR(Right-Right) 불균형을 해결하기 위한 회전)
Node* leftRotate(Node* x) {
    Node* y = x->right; // x의 오른쪽 자식을 y로 설정
    Node* T2 = y->left; // y의 왼쪽 서브트리를 T2로 저장

    y->left = x; // y의 왼쪽 자식으로 x를 설정
    x->right = T2; // x의 오른쪽 자식으로 T2를 설정

    // x와 y의 높이를 업데이트
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y; // 새로운 루트 노드 반환
}

// AVL 트리에 값을 삽입 후 트리를 균형 상태로 유지하는 함수
Node* insertAVL(Node* node, int value) {
    // 기저 사례: 비어 있는 위치에 새 노드를 생성
    if (node == NULL) {
        node = (Node*)malloc(sizeof(Node));
        node->value = value;
        node->left = node->right = NULL;
        node->height = 1; // 새 노드의 높이는 1
        return node;
    }

    // 삽입 위치를 찾기 위해 값 비교
    if (value < node->value) {
        node->left = insertAVL(node->left, value); // 왼쪽 서브트리에 삽입
    }
    else if (value > node->value) {
        node->right = insertAVL(node->right, value); // 오른쪽 서브트리에 삽입
    }
    else {
        return node; // 중복된 값은 삽입하지 않음
    }

    // 노드의 높이를 업데이트
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // 삽입 후 노드의 균형 인수를 계산
    int balance = getBalance(node);

    // 불균형이 발생한 경우 회전을 통해 균형 유지
    if (balance > 1 && value < node->left->value) {
        return rightRotate(node); // LL 불균형 -> 오른쪽 회전
    }
    if (balance < -1 && value > node->right->value) {
        return leftRotate(node); // RR 불균형 -> 왼쪽 회전
    }
    if (balance > 1 && value > node->left->value) {
        node->left = leftRotate(node->left); // LR 불균형 -> 왼쪽 회전 후 오른쪽 회전
        return rightRotate(node);
    }
    if (balance < -1 && value < node->right->value) {
        node->right = rightRotate(node->right); // RL 불균형 -> 오른쪽 회전 후 왼쪽 회전
        return leftRotate(node);
    }

    return node; // 균형 잡힌 노드 반환
}

// AVL 트리에서 값을 삭제하는 함수
// 삭제 후 트리를 균형 상태로 유지
Node* deleteAVL(Node* root, int value) {
    if (root == NULL) {
        return root; // 삭제할 노드가 없음
    }

    // 삭제할 값을 찾기 위해 값 비교
    if (value < root->value) {
        root->left = deleteAVL(root->left, value); // 왼쪽 서브트리에서 삭제
    }
    else if (value > root->value) {
        root->right = deleteAVL(root->right, value); // 오른쪽 서브트리에서 삭제
    }
    else {
        // 삭제할 노드를 찾음
        if (root->left == NULL) { // 왼쪽 자식이 없는 경우
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) { // 오른쪽 자식이 없는 경우
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // 양쪽 자식이 있는 경우, 중위 순회의 후속자로 대체
        Node* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }

        root->value = temp->value; // 값 복사
        root->right = deleteAVL(root->right, temp->value); // 후속자 삭제
    }

    // 노드의 높이를 업데이트
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    // 삭제 후 균형 인수를 계산
    int balance = getBalance(root);

    // 불균형이 발생한 경우 회전을 통해 균형 유지
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root); // LL 불균형
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left); // LR 불균형
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root); // RR 불균형
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right); // RL 불균형
        return leftRotate(root);
    }

    return root; // 균형 잡힌 노드 반환
}

// AVL 트리에서 값을 탐색하는 함수, 탐색 시 비교 횟수를 기록
Node* searchAVL(Node* root, int value) {
    compareCount++; // 비교 횟수 증가
    if (root == NULL || root->value == value) {
        return root; // 값을 찾았거나 트리가 비었을 경우 반환
    }
    if (value < root->value) {
        compareCount++; // 비교 횟수 증가
        return searchAVL(root->left, value); // 왼쪽 서브트리 탐색
    }
    else {
        compareCount++; // 비교 횟수 증가
        return searchAVL(root->right, value); // 오른쪽 서브트리 탐색
    }
}

// AVL 트리 배치 작업하는 함수
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int operation = rand() % 3;
        int value = rand() % 1000;

        if (operation == 0) {  // 0이면 삽입
            root = insertAVL(root, value);
        }
        else if (operation == 1) {  // 1이면 삭제
            root = deleteAVL(root, value); 
        }
        else if (operation == 2) {  // 2이면 탐색
            searchCount++;
            searchAVL(root, value);
        }
    }
}

// 후위순회하면서 트리 메모리 해제 함수
void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;
    searchCount = 0;

    // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);

    return 0;
}
