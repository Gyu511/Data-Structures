#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List_Array.h"

#define FALSE -9999
#define PRINT printf("The current status of List : ")

int main(void) {
	int* list = createList(100);
	int input, data;

	while (1) {
		printf("In(0), Search(1), Out(2), Exit(3) : ");
		scanf("%d", &input);
		switch (input){
		case 0:
			printf("\nIn : ");
			scanf("%d", &data);
			addList(list, data);
			printf("\n");
			PRINT;
			traverseList(list);
			break;
		case 1:
			printf("\nSearch : ");
			scanf("%d", &data);
			if (searchList(list, data) == FALSE) {
				printf("\nMy List does not have %d\n\n", data);
			}
			else {
				printf("\nMy List has %d\n\n", data);
			}
			PRINT;
			traverseList(list);
			break;
		case 2:
			printf("\nOut : ");
			scanf("%d", &data);
			if (searchList(list, data) == FALSE) {
				printf("\nThere is no %d\n", data);
				break;
			}
			removeList(list, data);
			printf("\n%d was removed.\n\n", data);
			PRINT;
			traverseList(list);
			break;
		case 3:
			destroyList(list);
			exit(1);
			break;
		default:
			printf("\nInput error\n");
			break;
		}
		printf("\n\n");
	}
}