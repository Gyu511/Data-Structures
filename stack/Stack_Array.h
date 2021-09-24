#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int Element;
int top = -1;
int size;

void* CreateStack(int stsize) {
	Element* stack = (Element*)malloc(sizeof(Element) * stsize);
	size = stsize;
	top = -1;
	return stack;
}

void Push(Element* stack, Element data) {
	if (top > size) {
		printf("error\n");
		return;
	}
	stack[++top] = data;
}

Element Pop(Element* stack) {
	Element data;
	data = stack[top--];
	return data;
}

Element Top(Element* stack) {
	return stack[top];
}

void DestroyStack(Element* stack) {
	free(stack);
}

int IsFullStack() {
	if (top == size - 1) {
		return 1;
	}
	else return 0;
}

int IsEmptyStack() {
	if (top == -1) {
		return 1;
	}
	else return 0;
}

int CountStack(Element* stack) {
	return (top + 1);
}

void ClearStack(Element* stack) {
	for (int i = 0; i < size; i++) {
		stack[i] = 0;
	}
}

void show(Element* stack) {
	for (int i = top; i >= 0; i--) {
		printf("%d\n", stack[i]);
	}
}

void ShowLine(Element* stack) {
	for (int i = top; i >= 0; i--) {
		printf("%d", stack[i]);
	}
}