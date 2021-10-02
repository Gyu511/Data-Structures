#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE -9999

int count, _index, listsize;

int* createList(int size) {
	int* list = (int*)malloc(sizeof(int) * size);

	listsize = size;
	count = 0;

	return list;
}

void insertList() {
	//없어도 무방
}

int searchList(int* list, int data) {
	for (int i = 0; i < count; i++) {
		if (list[i] == data) {
			_index = i;
			return data;
		}
		else if (list[i] > data) {
			_index = i;
			return FALSE;
		}
	}
	_index = count;
	return FALSE;
}

void addList(int* list, int data) {
	searchList(list, data);

	if (count == 0) {
		list[0] = data;
	}
	else {
		if (count >= listsize) {
			printf("List is full\n");
			return;
		}
		else {
			for (int i = count; i >= _index; i--) {
				list[i] = list[i - 1];
			}
			list[_index] = data;
		}
	}
	count++;
}

void deletList() {
	//없어도 무방
}

void removeList(int* list, int data) {
	searchList(list, data);

	if (count == 0) {
		printf("List is empty\n");
		return;
	}
	else {
		if (_index == count - 1) {//last location data
			list[_index] = 0;
			count--;
			return;
		}
		else {
			for (int i = _index; i < count; i++) {
				list[i] = list[i + 1];
			}
		}
	}
	count--;
}

void traverseList(int* list) {
	if (count == 0) {
		return;
	}
	for (int i = 0; i < count - 1; i++) {
		printf("%d, ", list[i]);
	}
	printf("%d\n", list[count - 1]);
}

void destroyList(int* list) {
	free(list);
}