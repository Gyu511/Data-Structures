#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Element;

typedef struct Queue {
	Element** queue;
	int size;
	int front, rear;
} Queue;

Queue* CreareQueue(int size) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) {
		printf("error");
		return NULL;
	}

	queue->queue = (Element**)malloc(sizeof(Element*) * size);
	for (int i = 0; i < size; i++) {
		queue->queue[i] = (Element*)malloc(sizeof(Element) * size);
	}
	if (queue->queue == NULL) {
		printf("error");
		return NULL;
	}
	queue->size = size;
	queue->front = queue->rear = 0;

	return queue;
}

void Enqueue(Queue* queue, Element* data) {
	if (queue->front == (queue->rear + 1) % queue->size) {//full
		printf("FULL");
		return;
	}
	else {//general
		strcpy(queue->queue[(queue->rear++) % queue->size], data);
	}
}

Element* Dequeue(Queue* queue) {
	Element* data = (Element*)malloc(sizeof(Element) * 100);
	if (queue->front == queue->rear) {//empty
		return NULL;
	}
	else {//general
		strcpy(data, queue->queue[(queue->front++) % queue->size]);
	}
	return data;
}

Element* QueueFront(Queue* queue) {
	if (queue->front == queue->rear) {//empty
		return NULL;
	}
	return queue->queue[queue->front];
}

Element* QueueRear(Queue* queue) {
	if (queue->front == queue->rear) {//empty
		return NULL;
	}
	return queue->queue[queue->rear];
}

void Destoyqueue(Queue* queue, int size) {
	for (int i = 0; i < size; i++) {
		free(queue->queue[i]);
	}
	free(queue->queue);
	free(queue);
}

void show(Queue* queue, int size) {
	if (queue->front == queue->rear) return;
	else if (queue->front > queue->rear) {
		int num = 1;
		for (int i = queue->front; i < queue->rear; i++) {
			printf("%s%d, ", queue->queue[i], num);
			num++;
		}
		printf("\b\b");
	}
	else if (queue->front < queue->rear) {
		int num = 1;
		for (int i = queue->front; i < queue->rear; i++) {
			printf("%s%d, ", queue->queue[i], num);
			num++;
		}
		for (int i = queue->rear; i < queue->front; i++) {
			printf("%s%d, ", queue->queue[i], num);
			num++;
		}
		printf("\b\b");
	}
}