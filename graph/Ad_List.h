#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef struct Graph {
	int count;
	struct Vertex* first;
} Graph;

typedef struct Vertex {
	struct Vertex* pNextVertex;
	char data;
	int processed;
	int degree;
	struct Arc* pArc;
} Vertex;

typedef struct Arc {
	struct Vertex* destination;
	struct Arc* pNextArc;
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

Graph* CreateGraph(){
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	if (graph == NULL) return NULL;

	graph->count = 0;
	graph->first = NULL;

	return graph;
}

void AddEdge(Graph* graph, char ver, char data) {
	Arc* arc = (Arc*)malloc(sizeof(Arc));
	if (arc == NULL)return;

	Vertex* cur_vertex = NULL;
	Arc* cur_arc = NULL;
	arc->pNextArc = NULL;

	for (cur_vertex = graph->first; cur_vertex->data != data; cur_vertex = cur_vertex->pNextVertex);
	arc->destination = cur_vertex; //arc »ý¼º

	for (cur_vertex = graph->first; cur_vertex->data != ver; cur_vertex = cur_vertex->pNextVertex);
	if (cur_vertex->data == ver) {
		cur_arc = cur_vertex->pArc;
		if (!cur_arc) cur_vertex->pArc = arc;
		else {
			while (cur_arc->pNextArc) cur_arc = cur_arc->pNextArc;
			cur_arc->pNextArc = arc;
		}
		cur_vertex->degree++;
	}
}

void DeleteEdge(Graph* graph, char ver, char data) {
	Vertex* cur_vertex = graph->first;
	Arc* cur_arc = NULL;
	Arc* del_arc = NULL;
	Arc* pre_arc = NULL;

	for (cur_vertex = graph->first; cur_vertex->data != ver; cur_vertex->pNextVertex);

	if (ver == cur_vertex->pArc->destination->data) {
		del_arc = cur_vertex->pArc;
		cur_vertex->pArc = cur_vertex->pArc->pNextArc;
		free(del_arc);
		cur_vertex->degree--;
	}
	else {
		pre_arc = cur_vertex->pArc;
		cur_arc = pre_arc->pNextArc;
		while (cur_arc) {
			if (ver == cur_arc->destination->data) {
				del_arc = cur_arc;
				pre_arc->pNextArc = cur_arc->pNextArc;
				free(del_arc);
				cur_vertex->degree--;
				return;
			}
			pre_arc = pre_arc->pNextArc;
			cur_arc = cur_arc->pNextArc;
		}
	}
}

void InsertVertex(Graph* graph, char data){
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex));
	if (vertex == NULL) return;

	vertex->pNextVertex = NULL;
	vertex->data = data;
	vertex->processed = 0;
	vertex->degree = 0;
	vertex->pArc = NULL;
	if (graph->count == 0) graph->first = vertex;
	else {
		Vertex* cur = graph->first;
		while(cur->pNextVertex) {
			cur = cur->pNextVertex;
		}
		cur->pNextVertex = vertex;
	}
	graph->count++;
}

void DeleteVertex(Graph* graph, char data){
	Vertex* cur_vertex = graph->first;
	Vertex* del_vertex = NULL;
	Vertex* pre_vertex = NULL;
	Arc* cur_arc = NULL;
	
	//delete edge
	for (cur_vertex = graph->first; cur_vertex->data != data; cur_vertex = cur_vertex->pNextVertex);
	for (cur_arc = cur_vertex->pArc; !cur_arc; cur_arc = cur_arc->pNextArc) {
		if (cur_arc == NULL) break;
		DeleteEdge(graph, data, cur_arc->destination->data);
	}
	//delete vertex
	if (graph->first->data == data) {
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
		if (graph->first->data == vertex->data) {
			DeleteVertex(graph, vertex->data);
			vertex = graph->first;
		}
		else {
			DeleteVertex(graph, vertex->data);
			vertex = vertex->pNextVertex;
		}
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

void DepthFirstTraversal(Vertex* root){
	Arc* arc = NULL;

	if (root->processed) return;

	printf("%c ", root->data);
	root->processed = TRUE;

	for (arc = root->pArc; arc != NULL; arc = arc->pNextArc) {
		if (!arc->destination->processed) DepthFirstTraversal(arc->destination);
	}
}

void BreadthFirstTraversal(Graph* graph){
	Queue* queue = CreateQueue();
	Vertex* vertex = graph->first;
	Arc* arc = NULL;

	Enqueue(queue, vertex);
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