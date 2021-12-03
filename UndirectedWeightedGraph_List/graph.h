#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 1000;
#define TRUE 1
#define FALSE 0

typedef enum { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z } index;

typedef struct Graph {
	int count;
	struct Vertex* first;
} Graph;

typedef struct Vertex {
	struct Vertex* pNextVertex;
	char data;
	int processed;
	struct Arc* pArc;
} Vertex;

typedef struct Arc {
	struct Vertex* destination;
	struct Arc* pNextArc;
	int weight;
} Arc;

typedef struct Node {
	Vertex* root;
	struct Node* next;
} Node;

typedef struct Queue {
	Node* front, * rear;
	int count;
} Queue;

Queue* CreateQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) return NULL;

	queue->front = NULL;
	queue->rear = NULL;
	queue->count = 0;

	return queue;
}

void Enqueue(Queue* queue, Vertex* root) {
	if (queue == NULL) return;

	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) return;
	node->root = root;
	node->next = NULL;

	if (queue->count == 0) {
		queue->front = queue->rear = node;
	}
	else {
		queue->rear->next = node;
		queue->rear = node;
	}
	queue->count++;
	return;
}

Vertex* Dequeue(Queue* queue) {
	if (queue == NULL) return NULL;

	Vertex* root = queue->front->root;
	Node* cur = queue->front;

	if (queue->count == 1) {
		free(cur);
		queue->front = queue->rear = NULL;
	}
	else {
		queue->front = cur->next;
		free(cur);
	}
	queue->count--;

	return root;
}

int IsEmptyQueue(Queue* queue) {
	if (queue->count == 0) return 1;
	return 0;
}

Vertex* QueueFront(Queue* queue) {
	return queue->front->root;
}

void DestroyQueue(Queue* queue) {
	if (queue == NULL) return;

	Node* cur = queue->front;
	Node* ne = NULL;
	while (cur != NULL) {
		ne = cur->next;
		free(cur);
		cur = ne;
	}
}

Graph* CreateGraph() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (graph == NULL) return NULL;

	graph->count = 0;
	graph->first = NULL;

	return graph;
}

void AddEdge(Graph* graph, char ver, char data, int weight) {
	Arc* arc = (Arc*)malloc(sizeof(Arc));
	if (arc == NULL)return;

	Vertex* cur_vertex = NULL;
	Arc* cur_arc = NULL;
	arc->pNextArc = NULL;
	arc->weight = weight;

	for (cur_vertex = graph->first; cur_vertex->data != data; cur_vertex = cur_vertex->pNextVertex);
	arc->destination = cur_vertex; //arc 생성

	for (cur_vertex = graph->first; cur_vertex->data != ver; cur_vertex = cur_vertex->pNextVertex);
	if (cur_vertex->data == ver) {
		cur_arc = cur_vertex->pArc;
		if (!cur_arc) cur_vertex->pArc = arc;//arc가 없으면 첫번째에 연결
		else {
			while (cur_arc->pNextArc) cur_arc = cur_arc->pNextArc;//마지막 arc까지 
			cur_arc->pNextArc = arc;//마지막 arc에 연결
		}
	}
}

void DeleteEdge(Graph* graph, char ver, char data) {
	Vertex* cur_vertex = graph->first;
	Arc* cur_arc = NULL;
	Arc* del_arc = NULL;
	Arc* pre_arc = NULL;

	for (cur_vertex = graph->first; cur_vertex->data != ver; cur_vertex->pNextVertex);

	if (ver == cur_vertex->pArc->destination->data) {//첫번째 arc가 지우려는 거면
		del_arc = cur_vertex->pArc;
		cur_vertex->pArc = cur_vertex->pArc->pNextArc;
		free(del_arc);
	}
	else {
		pre_arc = cur_vertex->pArc;
		cur_arc = pre_arc->pNextArc;
		while (cur_arc) {
			if (ver == cur_arc->destination->data) {
				del_arc = cur_arc;
				pre_arc->pNextArc = cur_arc->pNextArc;
				free(del_arc);
				return;
			}
			pre_arc = pre_arc->pNextArc;
			cur_arc = cur_arc->pNextArc;
		}
	}
}

void InsertVertex(Graph* graph, char data) {
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	if (vertex == NULL) return;

	vertex->pNextVertex = NULL;
	vertex->data = data;
	vertex->processed = 0;
	vertex->pArc = NULL;
	if (graph->count == 0) graph->first = vertex;
	else {
		Vertex* cur = graph->first;
		while (cur->pNextVertex) {
			cur = cur->pNextVertex;
		}
		cur->pNextVertex = vertex;
	}
	graph->count++;
}

void DeleteVertex(Graph* graph, char data) {
	Vertex* cur_vertex = graph->first;
	Vertex* del_vertex = NULL;
	Vertex* pre_vertex = NULL;
	Arc* cur_arc = NULL;

	//delete edge
	for (cur_vertex = graph->first; cur_vertex->data != data; cur_vertex = cur_vertex->pNextVertex);
	for (cur_arc = cur_vertex->pArc; cur_arc; cur_arc = cur_arc->pNextArc) {
		DeleteEdge(graph, data, cur_arc->destination->data);//지우려는 vertex와 연결된 arc모두 연결끊어주기
	}
	//delete vertex
	if (graph->first->data == data) {//첫 vartex가 지우려는거면
		del_vertex = graph->first;
		graph->first = graph->first->pNextVertex;
		free(del_vertex);
	}
	else {
		for (pre_vertex = graph->first, cur_vertex = cur_vertex->pNextVertex; cur_vertex->data != data; pre_vertex = cur_vertex, cur_vertex = cur_vertex->pNextVertex);
		del_vertex = cur_vertex;
		pre_vertex->pNextVertex = cur_vertex->pNextVertex;
		free(del_vertex);
	}
	graph->count--;
}

void DistroyGraph(Graph* graph) {
	Vertex* vertex = graph->first;
	while (vertex) {
		DeleteVertex(graph, vertex->data);
		vertex = graph->first;
	}
	free(graph);
}

void ClearProcessed(Graph* graph) {
	Vertex* cur = graph->first;
	while (cur) {
		cur->processed = 0;
		cur = cur->pNextVertex;
	}
}

void DepthFirstTraversal(Vertex* root) {
	Arc* arc = NULL;

	if (root->processed) return;

	printf("%c ", root->data);
	root->processed = TRUE;

	for (arc = root->pArc; arc != NULL; arc = arc->pNextArc) {
		if (!arc->destination->processed) DepthFirstTraversal(arc->destination);
	}
}

void BreadthFirstTraversal(Graph* graph) {
	Queue* queue = CreateQueue();
	Vertex* vertex = graph->first;
	Arc* arc = NULL;

	Enqueue(queue, vertex);
	vertex->processed = 1;
	while (!IsEmptyQueue(queue)) {
		vertex = Dequeue(queue);
		arc = vertex->pArc;
		printf("%c ", vertex->data);
		while (arc) {
			if (arc->destination->processed == 0) {
				Enqueue(queue, arc->destination);
				arc->destination->processed = 1;
			}
			arc = arc->pNextArc;
		}
	}
	DestroyQueue(queue);
}

void Show(Graph* graph) {
	Vertex* vertex = graph->first;
	while (vertex) {
		printf("%c ", vertex->data);
		vertex = vertex->pNextVertex;
	}
	printf("\n");
}

void Prim(Graph* graph) {
	ClearProcessed(graph);
	int num = graph->count - 1;
	int min;
	char start, destination;
	Vertex* vertex = graph->first;
	Arc* arc = NULL;
	Vertex* cur_ver = NULL;
	Arc* cur_arc = NULL;
	
	vertex->processed = TRUE;
	while (num--) {
		vertex = graph->first;
		min = INFINITY;
		while (vertex) {
			if (vertex->processed == 0) {
				vertex = vertex->pNextVertex;
				continue;
			}
			arc = vertex->pArc;
			while (arc) {
				if (arc->destination->processed == 0 && arc->weight < min) {
					min = arc->weight;
					start = vertex->data;
					destination = arc->destination->data;
				}
				arc = arc->pNextArc;
			}
			vertex = vertex->pNextVertex;
		}
		for (cur_ver = graph->first; cur_ver->data != start; cur_ver = cur_ver->pNextVertex);
		for (cur_arc = cur_ver->pArc; cur_arc->destination->data != destination; cur_arc = cur_arc->pNextArc);
		printf("%c %c (%d)\n", cur_ver->data, cur_arc->destination->data, min);
		cur_arc->destination->processed = TRUE;
	}
}

int choose(int arr[], int n, int found[]) {
	int index = 99;
	int min = INFINITY;

	for (int i = 0; i < n; i++) {
		if (!found[i] && arr[i] < min) {
			index = i;
			min = arr[i];
		}
	}
	return index;
}

void Dijkstra(Graph* graph) {
	int i = 0, u, w;
	int found[100] = { 0 };
	int distance[100];
	int cost[100][100];
	int weight[100][100] = { 0 };
	char ver[100];
	int a, b;
	Vertex* vertex = graph->first;
	Arc* arc = vertex->pArc;

	while (vertex) {
		ver[i] = vertex->data;
		vertex = vertex->pNextVertex;
		i++;
	}

	vertex = graph->first;
	while (vertex) {
		arc = vertex->pArc;
		while (arc) {
			a = (int)(vertex->data - 'A');
			b = (int)(arc->destination->data - 'A');
			weight[a][b] = arc->weight;
			arc = arc->pNextArc;
		}
		vertex = vertex->pNextVertex;
	}
	/*
	for (int j = 0; j < graph->count; j++) {
		for (int k = 0; k < graph->count; k++) {
			printf("%d ", weight[j][k]);
		}
		printf("\n");
	}
	printf("\n");
	*/
	for (int j = 0; j < graph->count; j++) {
		for (int k = 0; k < graph->count; k++) {
			if (weight[j][k] == 0) {
				cost[j][k] = INFINITY;
				if (j == k) cost[j][k] = 0;
			}
			else {
				cost[j][k] = weight[j][k];
			}
		}
	}

	for (i = 0; i < graph->count; i++) {
		distance[i] = cost[0][i];
	}

	for (int j = 1; j < graph->count; j++) {
		printf("%c %c : %d\n", graph->first->data, ver[j], distance[j]);
	}
	printf("\n");

	found[0] = 1;
	distance[0] = 0;
	for (i = 0; i < graph->count - 1; i++) {
		u = choose(distance, graph->count, found);
		found[u] = 1;
		for (w = 0; w < graph->count; w++) {
			if (!found[w] && (distance[u] + cost[u][w]) < distance[w]) {
				distance[w] = distance[u] + cost[u][w];
			}
		}
		for (int j = 1; j < graph->count; j++) {
			printf("%c %c : %d\n", graph->first->data, ver[j], distance[j]);
		}
		printf("\n");
	}
}