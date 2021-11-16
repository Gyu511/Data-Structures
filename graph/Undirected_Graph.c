#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ad_Matrix3.h"

int main(void) {
	FILE* fp;
	char fname[100];
	char root;
	char v, e;
	int w, i, j;
	char temp[100];
	char temp1;

	printf("File name of a graph : ");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("ERROR");
		exit(1);
	}

	Graph* graph = CreateGraph();
	fscanf(fp, " %c", &root);
	InsertVertex(graph, root);
	while (fscanf(fp, " %c", &v) != EOF) {
		fscanf(fp, " %c", &e);
		fscanf(fp, " %d", &w);
		for (i = 0; i < graph->size; i++) {
			if (graph->vertex[i] == e) break;
		}
		if (graph->vertex[i] != e) InsertVertex(graph, e);
		for (i = 0; i < graph->size; i++) {
			if (graph->vertex[i] == v) break;
		}
		if (graph->vertex[i] != v) InsertVertex(graph, v);

		AddEdge(graph, v, e, w);
		AddEdge(graph, e, v, w);
	}

	for (int i = 0; i < graph->size; i++) temp[i] = graph->vertex[i];

	for (int i = 0; i < graph->size; i++) {
		for (int j = i + 1; j < graph->size; j++) {
			if (temp[i] > temp[j]) {
				temp1 = temp[i];
				temp[i] = temp[j];
				temp[j] = temp1;
			}
		}
	}

	printf("\nThe graph is : \n");
	for (i = 0; i < graph->size; i++) {
		for (j = 0; j < graph->size; j++) {
			if (temp[i] == graph->vertex[j]) break;
		}
		printf("%c : ", graph->vertex[j]);
		for (int k = 0; k < graph->size; k++) {
			if (graph->graph[j][k] >= 1) printf("%c (%d) ", graph->vertex[k], graph->graph[j][k]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Minimum spannig tree : \n");
	Prim(graph);
	printf("\n");
	printf("Shortest path from A : \n\n");
	Dijkstra(graph);
	printf("\n");

	fclose(fp);
	return 0;
}