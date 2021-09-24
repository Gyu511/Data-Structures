#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue_Link.h"

int main(void) {
	Queue* queue = CreareQueue();
	int n;
	char name[100];
	char* st;

	while (1) {
		printf("In(0), Out(1), Exit(2) : ");
		scanf("%d", &n);
		getchar();
		if (n == 2)break;
		else if (n == 0) {
			printf("\nCustomer : ");
			fgets(name, 100, stdin);
			name[strlen(name) - 1] = '\0';//\nªË¡¶
			Enqueue(queue, name);
		}
		else if (n == 1) {
			if (QueueFront(queue) == NULL) {
				printf("\nQueue is empty!\n");
			}
			else {
				printf("\nCustomer dequeued : ");
				st = Dequeue(queue);
				printf("%s\n", st);
				free(st);
			}
		}
		printf("\nThe current status of Queue : ");
		printf("(");
		show(queue);
		printf(")\n\n\n");
	}
	Destoyqueue(queue);
}