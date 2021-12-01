#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SWAP(x,y) {void* temp; temp=x; x=y; y=temp;}

typedef struct Heap {
	void** data;
	int maxsize;
	int size;
	int (*compare)(void* argu1, void* argu2);
} Heap;

int comp(void* argu1, void* argu2) {
	return (*(int*)argu1 - *(int*)argu2);
}

Heap* CreateHeap(int maxsize) {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if (heap == NULL) return NULL;

	heap->size = 0;
	heap->maxsize = maxsize;
	heap->data = (void**)malloc(sizeof(void*) * maxsize);
	heap->compare = comp;
	return heap;
}

void ReHeapUp(Heap* heap, int index) {
	int parent_index = 0;
	if (index <= 0 || index >= heap->size) return;

	parent_index = (index - 1) / 2;
	if (heap->compare(heap->data[index], heap->data[parent_index]) > 0) {
		SWAP(heap->data[index], heap->data[parent_index]);
		ReHeapUp(heap, parent_index);
	}
}

void InsertHeap(Heap* heap, void* data) {
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
		if (maxchild + 1 < heap->size && heap->compare(heap->data[maxchild + 1], heap->data[maxchild]) > 0) maxchild++;

		if (heap->compare(heap->data[maxchild], heap->data[index]) > 0) {
			SWAP(heap->data[index], heap->data[maxchild]);
			ReHeapDown(heap, maxchild);
		}
	}
}

int DeleteHeap(Heap* heap, void** data) {
	if (heap->size <= 0) {
		printf("Heap is empty\n");
		return 0;
	}

	*data = heap->data[0];
	//printf("%d\n", *(int*)(*data));
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

void HeapSort(Heap* heap, void* arr) {
	if (heap == NULL) return;

	void* data = NULL;
	int num = heap->size;
	for (int i = 0; i < num; i++) {
		DeleteHeap(heap, &data);
		((int*)arr)[heap->size] = *(int*)data;
	}
}

void Show(Heap* heap) {
	if (heap == NULL) return;
	for (int i = 0; i < heap->size; i++) {
		printf("%d ", *(int*)heap->data[i]);
	}
	printf("\n");
}