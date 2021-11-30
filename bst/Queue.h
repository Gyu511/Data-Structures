#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BST.h"


typedef struct Node {
	TreeNode* root;
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

void Enqueue(Queue* queue, TreeNode* root) {
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

TreeNode* Dequeue(Queue* queue) {
	if (queue == NULL) return NULL;

	TreeNode* root = queue->front->root;
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

TreeNode* QueueFront(Queue* queue) {
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
	free(queue);
}