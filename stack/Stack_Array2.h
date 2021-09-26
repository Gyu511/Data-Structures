#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char Element;
int top = -1;
int size;

void* CreateStack(int stsize) {
	Element* stack = (Element*)malloc(sizeof(Element) * stsize);
	size = stsize;
	top = -1;
	for (int i = 0; i < size; i++) {
		stack[i] = NULL;
	}
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
	if (top < 0) {
		return NULL;
	}
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

void ShowLine_ch(Element* stack) {
	for (int i = top; i >= 0; i--) {
		printf("%c", stack[i]);
	}
}

int Priority(char _operator) {
	if (_operator == '+' || _operator == '-') {
		return 1;
	}
	else if (_operator == '*' || _operator == '/' || _operator == '%') {
		return 2;
	}
	else if (_operator == '(') {
		return 3;
	}
	return 0;
}

char* strcat2(char str[], char ch) {
	int len = strlen(str);
	str[len] = ch;
	str[len + 1] = 0;
	return str;
}