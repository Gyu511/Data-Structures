#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE -9999

typedef struct Node {
	int data;
	struct Node* next;
} Node;

typedef struct List {
	int count;
	Node* head;
} List;

Node* pre = NULL;
Node* cur = NULL;

List* createList() {
	List* list = (List*)malloc(sizeof(List));
	if (list == NULL) {
		printf("Fail allocation\n");
		return NULL;
	}
	list->head = NULL;
	list->count = 0;

	return list;
}

void insertList(List* list, int data) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;

	if (pre == NULL) {
		node->next = list->head;
		list->head = node;
	}
	else {
		node->next = pre->next;
		pre->next = node;
	}
	list->count++;
}

int searchList(List* list, int data) {
	for (pre = NULL, cur = list->head; cur != NULL; pre = cur, cur = cur->next) {
		if (cur->data == data) {
			return data;
		}
		else if (cur->data > data) {
			break;
		}
	}
	return FALSE;
}

void addNode(List* list, int data) {
	searchList(list, data);
	insertList(list, data);
}

void deletList(List* list) {
	if (pre == NULL) {
		list->head = list->head->next;
	}
	else {
		pre->next = cur->next;
	}
	free(cur);
	list->count--;
}

void removeList(List* list, int data) {
	int result = searchList(list, data);
	if (result != FALSE) {
		deletList(list);
	}
}

void traverseList(List* list) {
	Node* cur = list->head;
	
	while (cur->next) {
		printf("%d, ", cur->data);
		cur = cur->next;
	}
	printf("%d\n", cur->data);
}

void destroyList(List* list) {
	Node* del = list->head;
	Node* ne = NULL;

	while (del) {
		ne = del->next;
		free(del);
		del = ne;
	}
	free(list);
}