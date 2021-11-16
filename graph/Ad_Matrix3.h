#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 1000;

typedef struct Graph {
	int size;
	int graph[100][100];
	char vertex[100];
} Graph;

int check[100] = { 0 };

Graph* CreateGraph() {
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (graph == NULL) return NULL;
	graph->size = 0;
	for (int i = 0; i < 100; i++) {
		graph->vertex[i] = ' ';
		for (int j = 0; j < 100; j++) {
			graph->graph[i][j] = 0;
		}
	}
	return graph;
}

void InsertVertex(Graph* graph, char vertex) {
	graph->vertex[graph->size++] = vertex;
}

void DeleteVertex() {
	//구현X
}

void AddEdge(Graph* graph, char vertex1, char vertex2, int weight) {
	int a = 0, b = 0;
	for (int i = 0; i < graph->size; i++) {
		if (graph->vertex[i] == vertex1) {
			a = i;
			break;
		}
	}
	for (int i = 0; i < graph->size; i++) {
		if (graph->vertex[i] == vertex2) {
			b = i;
			break;
		}
	}
	graph->graph[a][b] = weight;
}

void DeleteEdge(Graph* graph, char vertex1, char vertex2) {
	int a = 0, b = 0;
	for (int i = 0; i < graph->size; i++) {
		if (graph->vertex[i] == vertex1) {
			a = i;
			break;
		}
	}
	for (int i = 0; i < graph->size; i++) {
		if (graph->vertex[i] == vertex2) {
			b = i;
			break;
		}
	}
	graph->graph[a][b] = 0;
}

void ClearCheck() {
	for (int i = 0; i < 100; i++) {
		check[i] = 0;
	}
}

void DepthFirstTraversal(Graph* graph, int ver) {
	check[ver] = 1;
	printf("%c ", graph->vertex[ver]);
	for (int i = 0; i < graph->size; i++) {
		if (!check[i] && graph->graph[ver][i] >= 1) DepthFirstTraversal(graph, i);
	}

}

void BreadthFirstTraversal(Graph* graph, int ver) {
	char queue[100];
	int front = 0, rear = 0;
	char vertex;
	int arc;
	int k;

	queue[rear++] = graph->vertex[0];//enqueue
	while (front != rear) {
		vertex = queue[front++];//dequeue
		printf("%c ", vertex);
		for (k = 0; k < graph->size; k++) if (graph->vertex[k] == vertex) break;
		for (int i = 0; i < graph->size; i++) {
			if (graph->graph[k][i] >= 1 && !check[i]) {
				check[i] = 1;
				queue[rear++] = graph->vertex[i];//enqueue
			}
		}
	}
}

void ShowVertex(Graph* graph) {
	for (int i = 0; i < graph->size; i++) printf("%c ", graph->vertex[i]);
}

void Show(Graph* graph) {
	for (int i = 0; i < graph->size; i++) {
		for (int j = 0; j < graph->size; j++)
			printf("%d ", graph->graph[i][j]);
		printf("\n");
	}
}

void Prim(Graph* graph) {
	int check[100] = { 0 };//check 했으면 1
	int num = graph->size - 1;
	int min = 0, index = 0, index1 = 0;

	check[0] = 1;
	while(num--) {
		min = INFINITY;
		for (int k = 0; k < graph->size; k++) {
			if (check[k] == 0) continue;
			for (int j = 0; j < graph->size; j++) {
				if (graph->graph[k][j] != 0 && check[j] && graph->graph[k][j] < min) {
					continue;
				}
				else if (graph->graph[k][j] != 0 && !check[j] && graph->graph[k][j] < min) {
					min = graph->graph[k][j];
					index = j;
					index1 = k;
				}
			}
		}
		check[index] = 1;
		printf("%c %c (%d)\n", graph->vertex[index1], graph->vertex[index], min);
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
	int i, u, w;
	int found[100] = { 0 };
	int distance[100];
	int cost[100][100];

	for (int j = 0; j < graph->size; j++) {
		for (int k = 0; k < graph->size; k++) {
			if (graph->graph[j][k] == 0) {
				cost[j][k] = INFINITY;
				if (j == k) cost[j][k] = 0;
			}
			else {
				cost[j][k] = graph->graph[j][k];
			}
		}
	}

	for (i = 0; i < graph->size; i++) {
			distance[i] = cost[0][i];
	}

	for (int j = 1; j < graph->size; j++) {
		printf("%c %c : %d\n", graph->vertex[0], graph->vertex[j], distance[j]);
	}
	printf("\n");

	found[0] = 1;
	distance[0] = 0;
	for (i = 0; i < graph->size - 1; i++) {
		u = choose(distance, graph->size, found);
		found[u] = 1;
		for (w = 0; w < graph->size; w++) {
			if (!found[w] && (distance[u] + cost[u][w]) < distance[w]) {
				distance[w] = distance[u] + cost[u][w];
			}
		}
		for (int j = 1; j < graph->size; j++) {
			printf("%c %c : %d\n", graph->vertex[0], graph->vertex[j], distance[j]);
		}
		printf("\n");
	}
}