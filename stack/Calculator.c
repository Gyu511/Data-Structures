#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack_Link2.h"

int main(void) {
	char original[256] = "";
	char space[256] = "";
	char post[256] = "";
	char* temp;
	int check = 0;
	int index = 1;
	int op1, op2, result;
	printf("Arithmetic Expression : ");
	fgets(original, 256, stdin);
	original[strlen(original) - 1] = '\0';//\n문자 삭제를 위해
	//checking error
	for (int i = 0; i < strlen(original); i++) {
		if (original[i] == '(') {
			check++;
		}
		else if (original[i] == ')') {
			check--;
		}
		else if (original[i] == ' ') {
			if (strchr("(+-*/%) ", original[i - 1]) == NULL && strchr("(+-*/%) ", original[i + 1]) == NULL) {
				printf("Error : Check the binary expression!\n");
				exit(1);
			}
		}
	}
	if (check != 0) {
		printf("Error : check the pairs of Parenthesis!\n");
		exit(1);
	}
	printf("Input : %s\n", original);
	//insert spaec at between operator
	space[0] = original[0]; //index 0에는 무조건 숫자
	for (int i = 1; i < strlen(original); i++) {
		if (strchr("(+-*/%)", original[i]) != NULL) {
			if (original[i - 1] != ' ') {
				space[index++] = ' ';
			}
			space[index++] = original[i];
			if (original[i + 1] != ' ') {
				space[index++] = ' ';
			}
		}
		else space[index++] = original[i];
	}
	//printf("insert space : %s\n", space);
	//infix -> postfix
	Stack* stack = CreateStack();
	temp = strtok(space, " ");
	strcpy(post, temp);
	strcat(post, " ");
	while (temp) {
		temp = strtok(NULL, " ");
		if (temp == NULL) break;
		//printf("temp: %s\n", temp);
		if (strchr("(+-*/%", temp[0]) != NULL) {
			if (stack->top == NULL || temp[0] == '(' || Top(stack) == '(') {
				Push(stack, temp[0]);
			}
			else {
				while (stack->top != NULL && Priority(*temp) < Priority(Top(stack))) {
					if (Top(stack) == '(') {
						Pop(stack);
						break;
					}
					strcat2(post, Pop(stack));
					strcat(post, " ");
				}
				Push(stack, temp[0]);
			}
		}
		else if (temp[0] == ')') {
			while (stack->top != NULL) {
				if (Top(stack) == '(') {
					Pop(stack);
					break;
				}
				strcat2(post, Pop(stack));
				strcat(post, " ");
			}
		}
		else {
			strcat(post, temp);
			strcat(post, " ");
		}
		//printf("Post : %s\n", post);
	}
	while (1) {
		if (stack->top == NULL) break;
		strcat2(post, Pop(stack));
		strcat(post, " ");
	}
	printf("Post : %s\n", post);
	DestroyStack(stack);
	//calculate
	typedef int Element;
	Stack* stackc = CreateStack();
	temp = NULL;
	temp = strtok(post, " ");
	Push(stackc, atoi(temp));
	while (temp) {
		temp = strtok(NULL, " ");
		if (temp == NULL) break;
		if (strchr("+-*/%", temp[0]) != NULL) {
			op1 = Pop(stackc);
			op2 = Pop(stackc);
			switch (temp[0]) {
			case '+':
				Push(stackc, op2 + op1);
				break;
			case '-':
				Push(stackc, op2 - op1);
				break;
			case '*':
				Push(stackc, op2 * op1);
				break;
			case '/':
				Push(stackc, op2 / op1);
				break;
			case '%':
				Push(stackc, op2 % op1);
				break;
			}
		}
		else Push(stackc, atoi(temp));
	}
	result = Pop(stackc);
	DestroyStack(stackc);
	printf("Result : %d\n", result);
}
//3 * (4- 3) % 3
//3 * ( ( 67 - 60)*4 - 20 )
//2*(54-50)+8*(9%4)
//34 56 - 7 *8
//3 - ( ( 5 + 61 ) * 7
//  3   * ((67 - 60) *4 -20 )