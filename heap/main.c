#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"

int main(void) {
	int arr[10] = { 8,88,28,34,81,83,15,12,79, 35 };
	Heap* heap = CreateHeap(100);
	int list[100];
	int num = 0;

	for (int i = 0; i < 10; i++) {
		heap->data[i] = arr[i];
	}
	heap->size = 10;
	BuildHeap(heap);
	Show(heap);

	InsertHeap(heap, 97);
	InsertHeap(heap, 44);
	InsertHeap(heap, 76);
	InsertHeap(heap, 5);
	InsertHeap(heap, 90);
	Show(heap);
	DeleteHeap(heap, &num);
	DeleteHeap(heap, &num);
	Show(heap);

	num = heap->size;
	HeapSort(heap, list);
	
	for (int i = 0; i < num; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");

	DistroyHeap(heap);

	return 0;
}