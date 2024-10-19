#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct StackType{
	int data[MAX_VERTICES];
	int top;
} StackType;

typedef struct QueueType {
	int queue[MAX_VERTICES];
	int front, rear;
} QueueType;

typedef struct GraphType {
	int n; //정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

//방문한 정점 기억하는 배열, 방문한 노드의 수, 원하는 정점 탐색 완료 여부
int visited[MAX_VERTICES], visit_count, target_found;

//스택을 초기화하는 함수입니다.
void init_stack(StackType* s) {
	s->top = -1;
}

//스택이 공백 상태인지 확인하는 함수입니다.
int is_empty_stack(StackType* s) {
	return (s->top == -1);
}

//스택이 포화 상태인지 확인하는 함수입니다.
int is_full_stack(StackType* s) {
	return (s->top == (MAX_VERTICES - 1));
}

//스택에 값을 삽입하는 함수입니다.
void push(StackType* s, int item) {
	if (is_full_stack(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}

//스택에서 값을 삭제하고 반환하는 함수입니다.
int pop(StackType* s) {
	if (is_empty_stack(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}

//큐를 초기화하는 함수입니다.
void init_queue(QueueType* q) {
	q->front = -1;
	q->rear = -1;
}

//큐 공백 확인 함수입니다.
int is_empty_queue(QueueType* q) {
	return (q->front == q->rear);
}

//큐 포화 확인 함수입니다.
int is_full_queue(QueueType* q) {
	return (q->rear == MAX_VERTICES - 1);
}

//큐에 값을 삽입하는 함수입니다.
void enqueue(QueueType* q, int item) {
	if (is_full_queue(q)) {
		fprintf(stderr, "큐가 가득 찼습니다.\n");
		return;
	}
	q->queue[++(q->rear)] = item;
}

//큐에서 값을 빼내고 반환하는 함수입니다.
int dequeue(QueueType* q) {
	if (is_empty_queue(q)) {
		fprintf(stderr, "큐가 비었습니다.\n");
		exit(1);
	}
	return q->queue[++(q->front)];
}

//그래프를 초기화하는 함수입니다.
void init_graph(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0; c < MAX_VERTICES; c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

//그래프에 정점을 추가하는 함수입니다.
void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과\n");
		return;
	}
	g->n++;
}

//그래프에 간선을 추가하는 함수입니다.
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류\n");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

//방문 기억 배열, 방문 노드 수, 탐색 완료 여부를 초기화하는 함수입니다.
void reset_visited_visitCount_targetFound() {
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = FALSE;
	}
	visit_count = -1; //시작 정점을 저장할 때 1을 올리기 때문에 결과적으로 0으로 시작합니다.
	target_found = FALSE;
}

//그래프를 생성하는 함수입니다. 초기화, 정점 생성, 간선 생성 함수로 
//과제에서 제시하는 그래프를 생성하였습니다.
void generateGraph(GraphType* g) {
	init_graph(g);
	for (int i = 0; i < 11; i++) {
		insert_vertex(g, i);
	}
	insert_edge(g, 0, 2);
	insert_edge(g, 0, 4);
	insert_edge(g, 0, 5);
	insert_edge(g, 0, 6);
	insert_edge(g, 0, 9);
	insert_edge(g, 1, 4);
	insert_edge(g, 1, 5);
	insert_edge(g, 1, 7);
	insert_edge(g, 1, 10);
	insert_edge(g, 2, 3);
	insert_edge(g, 2, 4);
	insert_edge(g, 3, 4);
	insert_edge(g, 3, 5);
	insert_edge(g, 4, 5);
	insert_edge(g, 4, 6);
	insert_edge(g, 4, 7);
	insert_edge(g, 6, 7);
	insert_edge(g, 6, 8);
	insert_edge(g, 7, 10);
	insert_edge(g, 8, 9);
	insert_edge(g, 8, 10);
}

//깊이 우선 탐색을 스택과 인접행렬로 구현한 함수입니다.
void dfs_mat_iterative(GraphType* g, int v, int target) {
	if (target >= g->n || v >= g->n) {
		fprintf(stderr, "탐색 실패! 존재하지 않는 정점입니다.\n\n");
		return;
	}
	StackType s;
	init_stack(&s);
	reset_visited_visitCount_targetFound(); //방문 정보 및 카운터 초기화

	push(&s, v); //시작 정점을 스택에 푸시
	visited[v] = TRUE; // 시작 정점을 방문한 것으로 표시함
	visit_count++; // -1을 0으로 만들어주면서 시작

	while (!is_empty_stack(&s)) {
		int current = pop(&s); //스택에서 현재 정점 꺼내기
		printf("%d ", current); //현재 정점 출력

		if (current == target) { //현재 방문한 정점이 원하는 값과 같다면 탐색 성공
			printf("\n탐색 성공: %d\n", target);
			printf("방문한 노드의 수: %d\n\n", visit_count);
			return;
		}

		int found_unvisited = FALSE;

		//인접 정점 탐색
		for (int w = 0; w < g->n; w++) {
			if (g->adj_mat[current][w] && !visited[w]) {
				push(&s, current); // 백트래킹을 위해서 현재 정점을 스택에 다시 푸시
				push(&s, w); // 인접 정점 푸시
				visited[w] = TRUE; // 인접 정점을 방문한 것으로 표시
				visit_count++; // 방문 카운트 증가
				found_unvisited = TRUE; // 방문하지 않은 정점 발견
				break;
			}
		}
		// 만약 인접 정점이 없다면, 다시 돌아가야 하므로 방문 카운트를 증가시킴
		if (!found_unvisited) {
			visit_count++; // 백트래킹으로 돌아갈 때 카운트 증가
		}
	}
}

//너비 우선 탐색을 큐와 인접행렬로 구현한 함수입니다.
void bfs_mat(GraphType* g, int v, int target) {
	if (target >= g->n || v >= g->n) {
		fprintf(stderr, "탐색 실패! 존재하지 않는 정점입니다.\n\n");
		return;
	}
	reset_visited_visitCount_targetFound(); //방문 정보 및 카운터 초기화
	QueueType q;
	init_queue(&q);
	visited[v] = TRUE; //시작 정점을 방문 표시
	visit_count++; //-1을 0으로 만들어주면서 시작
	printf("%d ", v);
	enqueue(&q, v); //시작 정점을 큐에 저장
	while (!is_empty_queue(&q)) {
		int current = dequeue(&q); //정점 추출

		for (int w = 0; w < g->n; w++) { //인접 정점 탐색
			if (g->adj_mat[current][w] && !visited[w]) {
				visited[w] = TRUE; //방문한 정점 표시
				visit_count++; //방문 배열에 추가할 때 노드 수 추가
				printf("%d ", w);
				enqueue(&q, w); //방문한 정점을 큐에 저장
				if (w == target) { //현재 방문한 정점이 원하는 값과 같다면 탐색 성공
					printf("\n탐색 성공: %d\n", target);
					printf("방문한 노드의 수: %d\n\n", visit_count);
					return; //성공 시 종료
				}
			}
		}
	}
}

int main(void) {
	GraphType* g = (GraphType*)malloc(sizeof(GraphType));
	generateGraph(g);
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("1	: 깊이 우선 탐색	\n");
	printf("2	: 너비 우선 탐색	\n");
	printf("3	: 종료			\n");
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n\n");
	while (1) {
		int menuNumber = 0, startV = 0, endV = 0;
		printf("메뉴 입력: ");
		scanf("%d", &menuNumber);
		getchar();

		switch (menuNumber) {
		case 1:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf("%d %d", &startV, &endV);
			getchar();
			dfs_mat_iterative(g, startV, endV);
			break;
		case 2:
			printf("시작 번호와 탐색할 값 입력: ");
			scanf("%d %d", &startV, &endV);
			getchar();
			bfs_mat(g, startV, endV);
			break;
		case 3:
			free(g);
			exit(1);
		default:
			printf("잘못된 입력입니다. 메뉴에 맞는 숫자를 입력해주십시오.\n\n");
			break;
		}
	}
	return 0;
}