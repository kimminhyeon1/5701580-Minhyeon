#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 1000
#define INF 10000

int parent[MAX_VERTICES];


void set_init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)
		parent[root1] = root2;
}

struct Edge {
	int start, end, weight;
};

typedef struct GraphType {
	int n; //간선의 개수
	int nvertex;
	struct Edge edges[2 * MAX_VERTICES];
}GraphType;

typedef struct HeapType {
	int heap_size;
	struct Edge heapEdges[MAX_VERTICES];
}HeapType;

//그래프 초기화 함수
void graph_init(GraphType* g) {
	g->n = g->nvertex = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

//간선 삽입 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = weight;
	g->n++;
}

//qsort함수(정렬)에 사용할 compare함수
int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

//그래프 생성 함수
void GenerateGraph(GraphType* g) {
	g->nvertex = 10;
	insert_edge(g, 1, 2, 3);
	insert_edge(g, 1, 6, 11);
	insert_edge(g, 1, 7, 12);
	insert_edge(g, 2, 3, 5);
	insert_edge(g, 2, 4, 4);
	insert_edge(g, 2, 5, 1);
	insert_edge(g, 2, 6, 7);
	insert_edge(g, 2, 7, 8);
	insert_edge(g, 3, 4, 2);
	insert_edge(g, 3, 7, 6);
	insert_edge(g, 3, 8, 5);
	insert_edge(g, 4, 5, 13);
	insert_edge(g, 4, 8, 14);
	insert_edge(g, 4, 10, 16);
	insert_edge(g, 5, 6, 9);
	insert_edge(g, 5, 9, 18);
	insert_edge(g, 5, 10, 17);
	insert_edge(g, 7, 8, 13);
	insert_edge(g, 8, 10, 15);
	insert_edge(g, 9, 10, 10);
}

//qsort함수(정렬)를 이용한 Kruskal함수
void QuickKruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->nvertex);
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Quick Based Kruskal\n");
	int i = 0;
	while (edge_accepted < (g->nvertex - 1)) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

//최소히프트리 삽입함수
void insert_min_heap(HeapType* h, struct Edge edge) {
	h->heapEdges[h->heap_size] = edge;
	int i = h->heap_size++;
	//부모노드보다 자식노드가 값이 더 클 때까지 추가한 노드를 이동시키기
	while (i != 0 && h->heapEdges[(i - 1) / 2].weight > h->heapEdges[i].weight) { 
		struct Edge temp = h->heapEdges[i];
		h->heapEdges[i] = h->heapEdges[(i - 1) / 2]; //부모노드 값을 자식으로 이동
		h->heapEdges[(i - 1) / 2] = temp; //자식노드 값을 부모로 이동
		i = (i - 1) / 2;
	}
}

//삭제함수에서 히프트리에서 루트노드를 삭제하고 난 후에 
//나머지 노드들을 최소히프트리의 속성에 맞게 재설정해주는 함수
void min_heapify(HeapType* h, int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	//왼쪽 자식이 존재하고, 현재 노드보다 작으면 가장 작은값을 왼쪽 자식으로 설정
	if (left < h->heap_size && h->heapEdges[left].weight < h->heapEdges[smallest].weight)
		smallest = left;
	//오른쪽 자식이 존재하고, 현재 가장 작은 값보다 작으면 가장 작은 값을 오른쪽 자식으로 설정
	if (right < h->heap_size && h->heapEdges[right].weight < h->heapEdges[smallest].weight)
		smallest = right;
	// 현재 노드가 가장 작은 값이 아니라면, 가장 작은 값과 위치를 바꾸고 재귀적으로 하위 노드에 대해 min_heapify함수 호출
	if (smallest != i) {
		struct Edge temp = h->heapEdges[i];
		h->heapEdges[i] = h->heapEdges[smallest];
		h->heapEdges[smallest] = temp;
		min_heapify(h, smallest);  // 하위 트리에 대해 재귀적으로 실행
	}
}
//최소히프트리 삭제함수
struct Edge delete_min_heap(HeapType* h) {
	struct Edge min_edge = h->heapEdges[0];
	h->heapEdges[0] = h->heapEdges[--(h->heap_size)];
	min_heapify(h, 0);
	return min_edge;
}

//그래프의 모든 간선으로 최소히프트리를 만드는 함수
void build_min_heap(HeapType* h, GraphType* g) {
	h->heap_size = 0;
	for (int i = 0; i < g->n; i++) {
		insert_min_heap(h, g->edges[i]);
	}
}

//최소히프트리를 활용한 Kruskal함수
void MinHeapKruskal(GraphType* g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	HeapType* heap = (HeapType*)malloc(sizeof(HeapType));
	build_min_heap(heap, g); //그래프의 간선으로 히프
	set_init(g->nvertex);

	printf("\nMinHeap Based Kruskal\n");

	while (edge_accepted < (g->nvertex - 1) && heap->heap_size > 0) {
		e = delete_min_heap(heap); //
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("Edge (%d, %d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
	}

	free(heap);
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	GenerateGraph(g);

	QuickKruskal(g);
	MinHeapKruskal(g);

	free(g);
	return 0;
}