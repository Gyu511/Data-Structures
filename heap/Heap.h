#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y) {int temp; temp=x; x=y; y=temp;}

typedef struct Heap {
	int* data;
	int maxsize;
	int size;
} Heap;

Heap* CreateHeap(int maxsize) {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if (heap == NULL) return;

	heap->size = 0;
	heap->maxsize = maxsize;
	heap->data = (int*)malloc(sizeof(int) * maxsize);
	return heap;
}

void ReHeapUp(Heap* heap, int index) {
	int parent_index = 0;
	if (index <= 0 || index >= heap->size) return;

	parent_index = (index - 1) / 2;
	if (heap->data[index] > heap->data[parent_index]) {
		SWAP(heap->data[index], heap->data[parent_index]);
		ReHeapUp(heap, parent_index);
	}
}

void InsertHeap(Heap* heap, int data) {
	if (heap->size >= heap->maxsize) {
		printf("Heap is full\n");
		return;
	}
	heap->data[heap->size++] = data;
	ReHeapUp(heap, heap->size - 1);
}

void ReHeapDown(Heap* heap, int index) {
	if (index < 0 || index >= heap->size) return;

	if (index * 2 + 1 < heap->size) {
		int maxchild = index * 2 + 1;
		if (maxchild + 1 < heap->size && heap->data[maxchild + 1] > heap->data[maxchild]) maxchild++;

		if (heap->data[maxchild] > heap->data[index]) {
			SWAP(heap->data[index], heap->data[maxchild]);
			ReHeapDown(heap, maxchild);
		}
	}
}

int DeleteHeap(Heap* heap, int* data) {
	if (heap->size <= 0) {
		printf("\Heap is empty\n");
		return 0;
	}

	*data = heap->data[0];
	heap->data[0] = heap->data[--heap->size];
	ReHeapDown(heap, 0);

	return 1;
}

void BuildHeap(Heap* heap) {//배열을 heap->data에 담아서 돌리면 자동으로 힙생성, heap->size 맞춰줘야함
	int i = 0;
	for (i = 1; i < heap->size; i++) {
		ReHeapUp(heap, i);
	}
}

void DistroyHeap(Heap* heap) {
	if (heap == NULL) return;
	free(heap->data);
	free(heap);
}

void HeapSort(Heap* heap, int* arr) {
	if (heap == NULL) return;

	int data = 0;
	int num = heap->size;
	for (int i = 0; i < num; i++) {
		DeleteHeap(heap, &data);
		arr[heap->size] = data;
	}
}

void Show(Heap* heap) {
	if (heap == NULL) return;
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", heap->data[i]);
	}
	printf("\n");
}