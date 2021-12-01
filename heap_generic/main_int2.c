#define _CRT_SECURE_NO_WARNINGS
#include "Heap.h"

int main(void) {
	int arr[10] = { 2,235,784,84,23,42,64,28,81,91 };
	int st[2] = { 5,994 };
	Heap* heap = CreateHeap(100);
	int list[100];
	int* num = NULL;

	for (int i = 0; i < 10; i++) {
		heap->data[i] = &arr[i];
	}
	heap->size = 10;
	BuildHeap(heap);
	Show(heap);
	InsertHeap(heap, &st[0]);
	InsertHeap(heap, &st[1]);
	Show(heap);
	num = DeleteHeap(heap);
	//printf("%d\n", *num);
	num = DeleteHeap(heap);
	//printf("%d\n", *num);
	Show(heap);

	*num = heap->size;
	HeapSort(heap, list);

	for (int i = 0; i < *num; i++) {
		printf("%d ", list[i]);
	}
	printf("\n");

	DistroyHeap(heap);

	return 0;
}