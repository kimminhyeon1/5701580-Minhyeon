#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0
#define MAX_VERTICES 1000
#define INF 10000L

struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n;
    int nvertex;
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];

//그래프를 초기화하는 함수
void graph_init(GraphType* g) {
    g->n = g->nvertex = 0;
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

//그래프에 간선(가중치 포함)을 추가하는 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = weight;
    g->n++;
}

//insert_edge함수를 이용하여 그래프를 생성하는 함수
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

//프림 알고리즘으로 최소신장트리를 찾는 함수
void FindPrimMST(GraphType* g) {
    int minWeight, u = 1; //시작 정점 u = 1
    printf("Prim MST Algorithm\n");

    //모든 정점을 MST에 포함되지 않은 상태로 초기화
    for (int i = 1; i <= g->nvertex; i++) {
        selected[i] = False;
    }

    selected[u] = True; //시작 정점을 최소신장트리에 포함시키기
    printf("정점 %d 추가\n", u);

    //여기서부터 반복하여 최소신장트리 생성하기
    for (int i = 1; i < g->nvertex; i++) {
        minWeight = INF; //최소 가중치를 INF로 초기화
        int v = -1;

        //간선 배열을 순회하여 최소신장트리에 포함된 정점과 연결된 최소 가중치 간선을 찾기
        for (int j = 0; j < g->n; j++) {
            int start = g->edges[j].start;
            int end = g->edges[j].end;
            int weight = g->edges[j].weight;

            if (selected[start] && !selected[end] && weight < minWeight) {
                minWeight = weight;
                u = start;
                v = end;
            }
            else if (selected[end] && !selected[start] && weight < minWeight) {
                minWeight = weight;
                u = end;
                v = start;
            }
        }

        //최소 가중치 간선이 발견되면,
        if (v != -1) {
            selected[v] = True; //새로 선택된 정점을 최소신장트리에 포함시키기
            printf("정점 %d 추가\n", v);
        }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);
    FindPrimMST(g);

    free(g);
    return 0;
}