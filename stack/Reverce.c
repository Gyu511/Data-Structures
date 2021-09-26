#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Stack_Link.h"
#include "Stack_Array.h"
/*
//link version
int main(void) {
	Stack* stack = CreateStack();
	int num;
	int check;
	while (1) {
		printf("Enter a number: <Ctrl+d> to stop: ");
		check = scanf("%d", &num);
		if (check != 1) {
			break;
		}
		Push(&stack, num);
	}
	printf("\n");
	printf("The List of number reversed:\n");
	Show(&stack);
	DestroyStack(&stack);
}
*/

//array version
int main(void) {
	int* stack = (int*)CreateStack(100);
	int num;
	int check;
	while (1) {
		printf("Enter a number: <Ctrl+d> to stop: ");
		check = scanf("%d", &num);
		if (check != 1) {
			break;
		}
		Push(stack, num);
	}
	printf("\n");
	printf("The List of number reversed:\n");
	show(stack);
	DestroyStack(stack);
}
