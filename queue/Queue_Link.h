#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Element;

typedef struct Node {
	Element data[100];
	struct Node* next;
} Node;

typedef struct Queue {
	Node* front;
	Node* rear;
	int count;
} Queue;

Queue* CreareQueue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) {
		printf("error");
		return NULL;
	}

	queue->count = 0;
	queue->front = queue->rear = NULL;

	return queue;
}

void Enqueue(Queue* queue, Element* data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		printf("error");
		return;
	}

	strcpy(node->data, data);

	if (queue->count == 0) {//empty
		queue->front = queue->rear = node;
		queue->count++;
		return;
	}
	queue->rear->next = node;
	queue->rear = node;
	queue->count++;
}

Element* Dequeue(Queue* queue) {
	Element* data = (Element*)malloc(sizeof(Element) * 100);
	Node* crt = queue->front;
	if (queue->count == 0) {//empty
		//printf("empty");
		return NULL;
	}
	
	strcpy(data, queue->front->data);

	if (queue->count == 1) {
		queue->front = queue->rear = NULL;
	}
	else queue->front = crt->next;

	free(crt);
	queue->count--;
	return data;
}

Element* QueueFront(Queue* queue) {
	if (queue->count == 0) {//empty
		return NULL;
	}
	return queue->front->data;
}

Element* QueueRear(Queue* queue) {
	if (queue->count == 0) {//empty
		return NULL;
	}
	return queue->rear->data;
}

void Destoyqueue(Queue* queue) {
	Node* crt=queue->front;
	Node* next;
	while (queue->count != 0) {
		next = crt->next;
		free(crt);
		crt = next;
		queue->count--;
	}
	free(queue);
}

void show(Queue* queue) {
	int count = 1;
	Node* ctr = queue->front;
	while (queue->count >= count) {
		printf("%s%d, ",ctr->data,count);
		ctr = ctr->next;
		if(queue->count == count)printf("\b\b");
		count++;
	}
}