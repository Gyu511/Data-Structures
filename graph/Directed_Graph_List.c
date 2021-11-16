#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ad_List.h"

void swap(Vertex** vertex1, Vertex** vertex2) {
	Vertex* temp = *vertex1;
	*vertex1 = *vertex2;
	*vertex2 = temp;
}

int main(void) {
	FILE* fp;
	char fname[100];
	char root;
	char v, e;
	Vertex* arr[100] = { NULL };
	int i, k;

	printf("File name of a graph : ");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("ERROR");
		exit(1);
	}

	Graph* graph = CreateGraph();
	Vertex* vertex = NULL;
	fscanf(fp, " %c", &root);
	InsertVertex(graph, root);
	while (fscanf(fp, " %c", &v) != EOF) {
		fscanf(fp, " %c", &e);
		vertex = graph->first;
		while (vertex) {
			if (vertex->data == v) {//이미 vertex가 있으니까 추가 할 필요없음
				break;
			}
			vertex = vertex->pNextVertex;
		}
		if (!vertex) {//vertex가 없을시 추가
			InsertVertex(graph, v);
		}
		vertex = graph->first;
		while (vertex) {
			if (vertex->data == e) {
				break;
			}
			vertex = vertex->pNextVertex;
		}
		if (!vertex) {
			InsertVertex(graph, e);
		}
		AddEdge(graph, v, e);
	}

	//Show(graph);

	//알파벳순 정렬
	vertex = graph->first;
	i = 0;
	while (vertex) {
		arr[i] = vertex;
		vertex = vertex->pNextVertex;
		i++;
	}
	k = i;
	for (i = 0; i < k; i++) {
		for (int j = i + 1; j < k; j++) {
			if (arr[i]->data > arr[j]->data) {
				swap(&arr[i], &arr[j]);
			}
		}
	}
	//for (int j = 0; j < k; j++) printf("%c ", arr[j]->data); printf("\n");

	printf("\nThe graph is : \n");
	i = 0;
	while (arr[i]) {
		printf("%c : ", arr[i]->data);
		Arc* arc = arr[i]->pArc;
		while (arc) {
			printf("%c ", arc->destination->data);
			arc = arc->pNextArc;
		}
		printf("\n");
		i++;
	}
	printf("\n");

	//Show(graph);

	printf("Depth First Traversal : ");
	DepthFirstTraversal(graph->first);
	printf("\n");
	ClearProcessed(graph);
	printf("Breadth First Traversal : ");
	BreadthFirstTraversal(graph);
	printf("\n");
	DistroyGraph(graph);

	fclose(fp);
	return 0;
}