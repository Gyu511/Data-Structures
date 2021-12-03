#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

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
	int i, k, w;

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
		fscanf(fp, " %d", &w);
		vertex = graph->first;
		while (vertex) {
			if (vertex->data == v) {//�̹� vertex�� �����ϱ� �߰� �� �ʿ����
				break;
			}
			vertex = vertex->pNextVertex;
		}
		if (!vertex) {//vertex�� ������ �߰�
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
		AddEdge(graph, v, e, w);
		AddEdge(graph, e, v, w);//������*****
	}

	//Show(graph);

	//���ĺ��� ����
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
			if (arr[i]->data > arr[j]->data) {//����ū�� �� �����ʿ� ��ġ��Ŵ
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
			printf("%c (%d) ", arc->destination->data, arc->weight);
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
	printf("\n\n");

	ClearProcessed(graph);
	printf("Minimum spannig tree : \n");
	Prim(graph);
	printf("\n");

	printf("Shortest path from A : \n\n");
	Dijkstra(graph);
	printf("\n");

	DistroyGraph(graph);
	fclose(fp);
	return 0;
}