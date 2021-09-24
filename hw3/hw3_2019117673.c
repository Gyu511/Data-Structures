#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	int num;
	char name[256];
	int age;
	int math;
	int english;
	int history;
	struct Student* next;
}Student;

typedef struct {
	Student* front;
	Student* rear;
	int count;
}Queue;

Queue queue;

void insert(char* file_name) {
	FILE* fp = NULL;
	int i = 0;
	fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("NO FILE");
		exit(1);
	}
	while (1) {
		Student* node = (Student*)malloc(sizeof(Student));
		node->next = NULL;
		if (fscanf(fp, "%s", node->name) == EOF)break;
		fscanf(fp, "%d", &(node->age));
		if (node->age < 0) {
			printf("Result : The age cannot be a negative number. Program terminates.\n");
			printf("====================\n");
			exit(1);
		}
		fscanf(fp, "%d", &(node->math));
		if (node->math < 0 || node->math>100) {
			printf("Result : The scores are in [0, 100]. Program terminates.\n");
			printf("====================\n");
			exit(1);
		}
		fscanf(fp, "%d", &(node->english));
		if (node->english < 0 || node->english>100) {
			printf("Result : The scores are in [0, 100]. Program terminates.\n");
			printf("====================\n");
			exit(1);
		}
		fscanf(fp, "%d", &(node->history));
		if (node->history < 0 || node->history>100) {
			printf("Result : The scores are in [0, 100]. Program terminates.\n");
			printf("====================\n");
			exit(1);
		}
		if (queue.count == 0) {
			queue.front = node;
		}
		else {
			queue.rear->next = node;
		}
		queue.rear = node;
		queue.count++;
		node->num = ++i;
	}
	fclose(fp);
}

void swap(Student** node1, Student** node2) {
	Student temp;
	strcpy(temp.name,(**node1).name);
	temp.age = (**node1).age;
	temp.math = (**node1).math;
	temp.english = (**node1).english;
	temp.history = (**node1).history;
	strcpy((**node1).name, (**node2).name);
	(**node1).age = (**node2).age;
	(**node1).math = (**node2).math;
	(**node1).english = (**node2).english;
	(**node1).history = (**node2).history;
	strcpy((**node2).name, temp.name);
	(**node2).age = temp.age;
	(**node2).math = temp.math;
	(**node2).english = temp.english;
	(**node2).history = temp.history;
}

void sort(int choose) {
	Student* crt = queue.front;
	Student* ne = queue.front->next;
	if (choose == 1) {
		for (int i = 0; i < queue.count - 1; i++) {
			crt = queue.front;
			ne = queue.front->next;
			for (int j = 0; j < queue.count - i - 1; j++) {
				if (strcmp(crt->name, ne->name) > 0) {
					swap(&crt, &ne);
				}
				crt = crt->next;
				ne = crt->next;
			}
		}
	}
	else if (choose == 2) {
		for (int i = 0; i < queue.count - 1; i++) {
			crt = queue.front;
			ne = queue.front->next;
			for (int j = 0; j < queue.count -i - 1; j++) {
				if (crt->age > ne->age) {
					swap(&crt, &ne);
				}
				crt = crt->next;
				ne = crt->next;
			}		
		}
	}
	else if (choose == 3) {
		for (int i = 0; i < queue.count - 1; i++) {
			crt = queue.front;
			ne = queue.front->next;
			for (int j = 0; j < queue.count - i - 1; j++) {
				if (crt->math > ne->math) {
					swap(&crt, &ne);
				}
				crt = crt->next;
				ne = crt->next;
			}
		}
	}
	else if (choose == 4) {
		for (int i = 0; i < queue.count - 1; i++) {
			crt = queue.front;
			ne = queue.front->next;
			for (int j = 0; j < queue.count - i - 1; j++) {
				if (crt->english > ne->english) {
					swap(&crt, &ne);
				}
				crt = crt->next;
				ne = crt->next;
			}
		}
	}
	else if (choose == 5) {
		for (int i = 0; i < queue.count - 1; i++) {
			crt = queue.front;
			ne = queue.front->next;
			for (int j = 0; j < queue.count - i - 1; j++) {
				if (crt->history > ne->history) {
					swap(&crt, &ne);
				}
				crt = crt->next;
				ne = crt->next;
			}
		}
	}
}

void print(int choose) {
	Student* crt = queue.front;
	int count = 1;
	if (choose == 1) {
		while (crt != NULL) {
			printf("%d %s %d %d %d %d\n", count++, crt->name, crt->age, crt->math, crt->english, crt->history);
			crt = crt->next;
		}
	}
	else if (choose == 2) {
		while (crt != NULL) {
			printf("%d %d %s %d %d %d\n", count++, crt->age, crt->name, crt->math, crt->english, crt->history);
			crt = crt->next;
		}
	}
	else if (choose == 3) {
		while (crt != NULL) {
			printf("%d %d %s %d %d %d\n", count++, crt->math, crt->name, crt->age, crt->english, crt->history);
			crt = crt->next;
		}
	}
	else if (choose == 4) {
		while (crt != NULL) {
			printf("%d %d %s %d %d %d\n", count++, crt->english, crt->name, crt->age, crt->math, crt->history);
			crt = crt->next;
		}
	}
	else if (choose == 5) {
		while (crt != NULL) {
			printf("%d %d %s %d %d %d\n", count++, crt->history, crt->name, crt->age, crt->math, crt->english);
			crt = crt->next;
		}
	}
	printf("\n\n");
}

void finish() {
	Student* crt = (Student*)malloc(sizeof(Student));
	Student* ne = (Student*)malloc(sizeof(Student));
	crt = queue.front;
	ne = queue.front->next;
	while (crt != NULL && ne != NULL) {
		free(crt);
		crt = ne;
		ne = ne->next;
	}
	free(ne);
}

int main(void) {
	int menu = 0;
	char file_name[256];
	queue.front = queue.rear = NULL;

	printf("====================\n");
	while (1) {		
		printf("1)Insert\n2)Sort\n3)Quit\nSelect a menu : ");
		scanf("%d", &menu);
		if (menu == 1) {
			printf("File name : ");
			scanf("%s", file_name);
			insert(file_name);
			printf("Result : \n");
			printf("No Name Age Math English History\n");
			print(1);
		}
		else if (menu == 2) {
			if (queue.count == 0) {
				printf("Result : There is no data to be sorted. Program terminates.\n");
				printf("====================\n");
				exit(1);
			}
			int choose = 0;
			printf("1)Name\n2)Age\n3)Math\n4)English\n5)History\nChoose the file to sort by : ");
			scanf("%d", &choose);
			if (choose == 1) printf("No Name Age Math English History\n");
			else if (choose == 2) printf("No Age Name Math English History\n");
			else if (choose == 3) printf("No Math Name Age English History\n");
			else if (choose == 4) printf("No English Name Age Math History\n");
			else if (choose == 5) printf("No History Name Age Math English\n");
			sort(choose);
			print(choose);
		}
		else if (menu == 3) {
			printf("\n\n====================\n");
			finish();
			break;
		}
	}
	return 0;
}