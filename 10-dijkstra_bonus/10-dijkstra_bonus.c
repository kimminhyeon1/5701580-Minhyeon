#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 1000
#define INF 100000

// 인접 리스트의 노드 구조체
typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

// 그래프 구조체 정의
typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 최소 히프 트리의 노드 구조체
typedef struct HeapNode {
    int vertex;
    int distance;
} HeapNode;

// 최소 히프 트리 구조체 정의
typedef struct HeapType {
    int size;
    HeapNode heap[MAX_VERTICES];
} HeapType;

int distance[MAX_VERTICES]; // 각 정점까지의 거리를 저장할 배열
int found[MAX_VERTICES]; // 정점마다 방문 여부를 저장할 배열
int found_order[MAX_VERTICES];  // 방문한 순서를 저장할 배열

//distance배열, found배열 초기화 함수
void init_distance_found_foundOrder() {
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF; // 모든 거리를 무한대로 설정
        found[i] = FALSE;  // 모든 정점을 방문하지 않음으로 설정
        found_order[i] = 0;
    }
}

//그래프 초기화 함수
void init_graph(GraphType* g) {
    g->n = 0;
    for (int v = 0; v < MAX_VERTICES; v++) {
        g->adj_list[v] = NULL;
    }
}

// 인접 리스트에 간선 추가(그래프 생성을 위해 사용)
void insert_edge(GraphType* g, int start, int end, int weight) {
    if (start < 0 || start >= MAX_VERTICES || end < 0 || end >= MAX_VERTICES) {
        printf("정점의 범위를 벗어났습니다!\n");
        return;
    }
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    if (newNode == NULL) {
        printf("메모리 할당을 실패하였습니다!\n");
        exit(1);
    }
    newNode->vertex = end; 
    newNode->weight = weight;
    newNode->next = g->adj_list[start];
    g->adj_list[start] = newNode;
}

// 최소 히프 트리 생성
HeapType* create_min_heap() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    h->size = 0;  // 히프 크기 초기화
    return h;
}

// 최소 히프 트리 삽입 함수
void insert_min_heap(HeapType* h, int vertex, int distance) {
    int i;
    i = ++(h->size);

    HeapNode new_node;
    new_node.vertex = vertex;
    new_node.distance = distance;

    while ((i != 1) && (new_node.distance < h->heap[i / 2].distance)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = new_node;
}

// 최소 히프 트리 삭제 함수
HeapNode delete_min_heap(HeapType* h) {
    if (h->size == 0) {
        printf("히프 트리에 삭제할 노드가 없습니다!\n");
        exit(1);
    }

    int parent, child;
    HeapNode item, temp;

    item = h->heap[1];
    temp = h->heap[(h->size)--];
    parent = 1;
    child = 2;

    while (child <= h->size) {
        // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.
        if ((child < h->size) && (h->heap[child].distance) > (h->heap[child + 1].distance))
            child++;
        if (temp.distance <= h->heap[child].distance) break;
        // 한 단계 아래로 이동
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

// 최단 거리 출력 함수
void print_status(GraphType* g) {
    printf("Distance: ");
    for (int i = 0; i < g->n; i++) {
        if (distance[i] == INF) {
            printf("* ");
        }
        else {
            printf("%d ", distance[i]);
        }
    }
    printf("\n");
    printf("Found: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found[i]);
    }
    printf("\n\n");
}

// 다익스트라 최단 경로 함수
void dijkstra(GraphType* g, int start) {
    HeapType* min_heap = create_min_heap();
    int i = 0; // 방문한 순서를 저장하는 배열의 인덱스
    distance[start] = 0;  // 시작 정점의 거리를 0으로 설정

    // 최소 히프 트리에 시작 정점 삽입
    insert_min_heap(min_heap, start, distance[start]);

    while (min_heap->size > 0) { // 최소 히프 트리가 존재하면 반복
        HeapNode min_node = delete_min_heap(min_heap); // 최소 히프 트리에서 최소 거리의 노드를 가져온다
        int current_vertex = min_node.vertex; // 최소 거리의 정점을 현재 정점으로 설정
        found_order[i] = min_node.vertex + 1; // 방문 순서를 저장하는 배열에 방문한 정점을 저장

        // 이미 방문한 정점이면 건너뛰기
        if (found[current_vertex]) {
            continue;
        }

        // 현재 정점을 방문한 것으로 표시
        found[current_vertex] = TRUE;
        print_status(g);

        // 인접 정점들에 대해 반복
        for (GraphNode* node = g->adj_list[current_vertex]; node != NULL; node = node->next) {
            int neighbor = node->vertex;
            int new_distance = distance[current_vertex] + node->weight;

            // 더 짧은 경로를 찾았다면
            if (new_distance < distance[neighbor]) {
                distance[neighbor] = new_distance; // 거리 업데이트
                // 이웃 정점이 아직 방문되지 않았다면, 최소 히프 트리에 삽입
                if (!found[neighbor]) {
                    insert_min_heap(min_heap, neighbor, new_distance);
                }
            }
        }
        i++; // 다음 방문하는 정점을 저장하기 위해 인덱스 증가
    }

    // 방문한 정점을 순서대로 출력
    printf("Found Order: ");
    for (int i = 0; i < g->n; i++) {
        printf("%d ", found_order[i]);
    }
    free(min_heap); // 사용 후 최소 힙 메모리 해제
}

// 제시된 그래프 생성 함수
void GenerateGraph(GraphType* g) {
    g->n = 10;
    insert_edge(g, 0, 1, 3);
    insert_edge(g, 0, 5, 11);
    insert_edge(g, 0, 6, 12);
    insert_edge(g, 1, 2, 5);
    insert_edge(g, 1, 3, 4);
    insert_edge(g, 1, 4, 1);
    insert_edge(g, 1, 5, 7);
    insert_edge(g, 1, 6, 8);
    insert_edge(g, 2, 3, 2);
    insert_edge(g, 2, 6, 6);
    insert_edge(g, 2, 7, 5);
    insert_edge(g, 3, 4, 13);
    insert_edge(g, 3, 7, 14);
    insert_edge(g, 3, 9, 16);
    insert_edge(g, 4, 5, 9);
    insert_edge(g, 4, 8, 18);
    insert_edge(g, 4, 9, 17);
    insert_edge(g, 6, 7, 13);
    insert_edge(g, 7, 9, 15);
    insert_edge(g, 8, 9, 10);
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    init_graph(g); // 그래프 초기화
    init_distance_found_foundOrder(); // distance 배열, found 배열 초기화
    GenerateGraph(g); // 그래프 생성
    dijkstra(g, 0); // 그래프 g를 통해 정점 0에서부터 다익스트라 알고리즘 실행
    free(g); // 할당한 메모리 해제

    return 0;
}
