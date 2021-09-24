#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Element;

typedef struct Node {
	Element data;
	struct Node* next;
} Node;

typedef struct Stack {
	int count;
	Node* top;
} Stack;

Stack* CreateStack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	if (stack == NULL) {
		return NULL;
	}
	stack->top = NULL;
	stack->count = 0;
	return stack;
}

void Push(Stack** stack, Element data) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) {
		return;
	}
	node->data = data;
	node->next = (*stack)->top;
	(*stack)->top = node;
	(*stack)->count++;
}

Element Pop(Stack** stack) {
	if ((*stack)->top == NULL) {
		printf("error\n");
		return -1;
	}
	else {
		Element data = (*stack)->top->data;
		Node* old = (*stack)->top;
		(*stack)->top = old->next;
		free(old);
		(*stack)->count--;
		return data;
	}
}

Element Top(Stack** stack) {
	return (*stack)->top->data;
}

void DestroyStack(Stack** stack) {
	Node* ctr = (*stack)->top;
	Node* del;
	while (ctr->next != NULL) {
		del = ctr->next;
		free(ctr);
		ctr = del;
	}
	free(*stack);
}

int IsFullStack(Stack** stack, int size) {
	if ((*stack)->count == size) {
		return 1;
	}
	else return 0;
}

int IsEmptyStack(Stack** stack) {
	if ((*stack)->count == 0) {
		return 1;
	}
	else return 0;
}

int CountStack(Stack** stack) {
	return (*stack)->count;
}

void ClearStack(Stack** stack) {
	Node* ctr = (*stack)->top;
	int num = (*stack)->count;
	while (num--) {
		ctr->data = 0;
		ctr = ctr->next;
	}
}

void Show(Stack** stack) {
	Node* ctr = (*stack)->top;
	while (ctr != NULL) {
		printf("%d\n", ctr->data);
		ctr = ctr->next;
	}
}

void ShowLine(Stack** stack) {
	Node* ctr = (*stack)->top;
	while (ctr != NULL) {
		printf("%d", ctr->data);
		ctr = ctr->next;
	}
}