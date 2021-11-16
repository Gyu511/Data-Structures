#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	//±¸ÇöX
}

void AddEdge(Graph* graph, char vertex1, char vertex2) {
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
	graph->graph[a][b] = 1;
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
		if (!check[i] && graph->graph[ver][i] == 1) DepthFirstTraversal(graph, i);
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
			if (graph->graph[k][i] == 1 && !check[i]) {
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