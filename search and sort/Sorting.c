#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SWAP(a,b) {int temp; temp=a; a=b; b=temp;}

int sorted[1000];

void Selection(int* arr, int n) {
	int small, temp;

	for (int i = 0; i < n - 1; i++) {
		small = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[small]) small = j;
		}
		SWAP(arr[i], arr[small]);
	}
}

void Insertion(int* arr, int n) {
	int hold, j;

	for (int i = 1; i < n; i++) {
		hold = arr[i];
		for (j = i; j > 0 && hold < arr[j - 1]; j--) {
			arr[j] = arr[j - 1];
		}
		arr[j] = hold;
	}
}

void Bubble(int* arr, int n) {
	int temp;
	int sorted = 0;
	int j;

	for (int i = 0; i < n && !sorted; i++) {
		for (j = n - 1, sorted = 1; j > i; j--) {
			if (arr[j] < arr[j - 1]) {
				sorted=0;
				SWAP(arr[j], arr[j - 1]);
				}
		}
	}
}

void Quick(int* arr, int left, int right) {
	if (left >= right) return;

	int pivot = left;
	int i = left + 1;
	int j = right;

	while (i < j) {
		while (arr[i] <= arr[pivot] && i <= right) i++;
		while (arr[j] >= arr[pivot] && j > left) j--;
		if (i >= j) {
			SWAP(arr[j], arr[pivot]);
		}
		else {
			SWAP(arr[i], arr[j]);
		}
	}

	Quick(arr, left, j - 1);
	Quick(arr, j + 1, right);
}

void Merge(int* arr, int start, int mid, int end) {
	int i = start;
	int j = mid + 1;
	int k = start;
	
	while (i <= mid && j <= end) {
		if (arr[i] <= arr[j]) {
			sorted[k++] = arr[i++];
		}
		else {
			sorted[k++] = arr[j++];
		}
	}
	if (i > mid) {
		for (int t = j; t <= end; t++) sorted[k++] = arr[t];
	}
	else {
		for (int t = i; t <= mid; t++) sorted[k++] = arr[t];
	}

	for (int t = start; t <= end; t++) arr[t] = sorted[t];
}

void MergeSort(int* arr, int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;
		MergeSort(arr, start, mid);
		MergeSort(arr, mid + 1, end);
		Merge(arr, start, mid, end);
	}
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
	int num, sel, i = 0;
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
	printf("\n\nChoose a sorting method to use (Selection : 0, Insertion : 1, Bubble : 2, Quick : 3, Merge : 4 ) : ");
	scanf("%d", &sel);
	switch (sel)
	{
	case 0: Selection(arr, i); break;
	case 1: Insertion(arr, i); break;
	case 2: Bubble(arr, i); break;
	case 3: Quick(arr, 0, i - 1); break;
	case 4: MergeSort(arr, 0, i - 1); break;
	default: printf("\nInput Error\n"); exit(1);
		break;
	}

	printf("\n\nThe numbers sorted : ");
	for (int k = 0; k < i ; k++) {
		if (k < i - 1) {
			printf("%d, ", arr[k]);
		}
		else {
			printf("%d\n\n", arr[k]);
		}
	}

	fclose(fp);
	return 0;
}