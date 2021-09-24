#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Stack_Link.h"
#include "Stack_Array.h"
/*
//link version
int main(void) {
	int num, original;

	printf("Enter a number: ");
	scanf("%d", &original);
	num = original;
	printf("\n\n");

	Stack* stack = CreateStack();

	while (num != 0) {
		Push(&stack, num % 2);
		num = num / 2;
	}

	printf("The binary number of %d: ", original);
	ShowLine(&stack);

	DestroyStack(&stack);
}
*/
//Array version
int main(void) {
	int num, original;

	printf("Enter a number: ");
	scanf("%d", &original);
	num = original;
	printf("\n\n");

	int* stack = (int*)CreateStack(100);

	while (num != 0) {
		Push(stack, num % 2);
		num = num / 2;
	}

	printf("The binary number of %d: ", original);
	ShowLine(stack);

	DestroyStack(stack);
}
