#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SWAP(a,b) {int temp; temp=a; a=b; b=temp;}

int hash[100][10];//Bucket Hashing을 위한 저장공간 할당

void StoreHash(int* arr, int n) {
	/*
	mod100 함수를 이용하여 정수를 100이하로 맵핑시키고
	Bucket Hashing를 이용하여 10개를 저장할 수 있는 공간을 만들어서 저장해주었습니다.(collision 처리);
	*/
	int r;

	for (int i = 0; i < 100; i++) for (int j = 0; j < 10; j++) hash[i][j] = -999;//hash memory 초기화

	for (int i = 0; i < n; i++) {
		r = arr[i] % 100;//mod function
		for (int j = 0; j < 10; j++) {
			if (hash[r][j] != -999) continue;
			hash[r][j] = arr[i];//mapping hash
			break;
		}
	}
	/* hash 확인용
	for (int i = 0; i < 100; i++) {
		printf("%2d :", i);
		for (int j = 0; j < 10; j++) {
			printf("%4d ", hash[i][j]);
		}
		printf("\n");
	}
	*/
}

int FindHash(int target) {
	int r = target % 100;
	for (int i = 0; i < 10; i++) {
		if (hash[r][i] == target) return 1;
	}
	return 0;
}

int Binary(int* arr, int n, int target) {
	int begin = 0, mid = 0, end = n - 1;

	while (begin <= end) {
		mid = (begin + end) / 2;
		if (target > arr[mid]) {
			begin = mid + 1;
		}
		else if (target < arr[mid]) {
			end = mid - 1;
		}
		else begin = end + 1;
	}
	return (target == arr[mid]);
}

void Quick(int* arr, int left, int right) {
	if (left >= right) return;

	int pivot = left;
	int i = left + 1;
	int j = right;

	while (i <= j) {
		while (arr[i] <= arr[pivot] && i <= right) i++;
		while (arr[j] >= arr[pivot] && j > left) j--;
		if (i > j) {
			SWAP(arr[j], arr[pivot]);
		}
		else {
			SWAP(arr[i], arr[j]);
		}
	}

	Quick(arr, left, j - 1);
	Quick(arr, j + 1, right);
}

void CreateFile(void) {
	FILE* fp = fopen("test.txt", "w");
	int overlap[1000] = { 0 };
	int count = 100;
	int num;
	srand(time(NULL));

	while (1) {
		num = rand() % 998 + 1;
		if (overlap[num] == 0) {
			overlap[num] = 1;
			fprintf(fp, "%d\n", num);
			count--;
		}
		if (count == 0) break;
	}
	fclose(fp);
}

int main(void) {
	int num, sel, target, i = 0;
	int check;
	int arr[1000];
	char name[100];
	FILE* fp;

	CreateFile();//test.txt에 난수 100개 생성

	printf("Input file name : ");
	scanf("%s", name);
	fp = fopen(name, "r");
	while (fscanf(fp, " %d", &num) != EOF) {
		arr[i] = num;
		i++;//들어있는 크기 에서 탈출
	}

	StoreHash(arr, i);

	printf("\n\nTarget integer : ");
	scanf("%d", &target);

	printf("\n\nChoose a searching method (Binary : 1, Hash : 2) : ");
	scanf("%d", &sel);

	switch (sel)
	{
	case 1: Quick(arr, 0, i - 1); check = Binary(arr, i, target); break;
	case 2: check = FindHash(target); break;
	default: printf("\nInput Error\n"); exit(1);
		break;
	}

	if (check) {
		printf("\n\n%d is found !\n\n",target);
	}
	else {
		printf("\n\n%d is not found !\n\n", target);
	}

	fclose(fp);
	return 0;
}