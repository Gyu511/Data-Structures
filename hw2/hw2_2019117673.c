#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

	char arr1[100];
	char arr2[100];
	char arr[200];
	char st1[100], st2[100];
	int i,k;
	int a[10], b[10], c[20];

	printf("input :\n");
	printf("-");
	fgets(arr1,sizeof(arr1),stdin);
	strcpy(st1, arr1);
	a[0] = atoi(strtok(arr1, ", "));
	for (i = 1; i < 10; i++) {
		a[i] = atoi(strtok(NULL, ", "));
		}
	for (i = 0; i < 9; i++) {
		for(k=i+1;k<10;k++){
			if (a[i] > a[k]) {
				printf("\"The input numbers are not in ascemdomg order\"\n");
				exit(1);
			}
		}
	}

	fgets(arr2, sizeof(arr1), stdin);
	strcpy(st2, arr2);
	b[0] = atoi(strtok(arr2, ", "));
	for (i = 1; i < 10; i++) {
		b[i] = atoi(strtok(NULL, ", "));
	}
	for (i = 0; i < 9; i++) {
		for (k = i + 1; k < 10; k++) {
			if (b[i] > b[k]) {
				printf("\"The input numbers are not in ascemdomg order\"\n");
				exit(1);
			}
		}
	}

	for (i = 0; i < 10; i++) {
		if (a[i] == NULL || b[i]==NULL) {
			printf("\"You should input 20 numbers in total\"\n");
			exit(1);
		}
	}
	strcpy(st1, strcat(st1, ", "));
	strcpy(arr, strcat(st1, st2));
	c[0] = atoi(strtok(arr, ", "));
	for (i = 1; i < 20; i++) {
		c[i] = atoi(strtok(NULL, ", "));
	}
	for (i = 0; i < 19; i++) {
		int temp;
		for(k=i+1;k<20;k++){
			if (c[i] > c[k]) {
				temp = c[i];
				c[i] = c[k];
				c[k] = temp;
			}
		}
	}
	printf("output :\n");
	printf("-");
	for (i = 0; i < 19; i++) {
		printf("%d, ", c[i]);
		while (c[i] == c[i + 1]) {
			i++;
		}
	}
	printf("%d",c[19]);

	return 0;
}