#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Queue.h"
#include "BST.h"

void Breadth_First_Traversal(TreeNode* root) {
	if (root == NULL) return;

	Queue* queue = CreateQueue();
	while (root) {
		printf("%d", root->data);
		if (root->left) Enqueue(queue, root->left);
		if (root->right) Enqueue(queue, root->right);
		if (!IsEmptyQueue(queue)) root = Dequeue(queue);
		else root = NULL;
	}
	DestroyQueue(queue);
}

int main(void) {
	char ch[256];
	int num[256];
	int* pnum = NULL;
	int len;
	int i = 0;

	printf("Input a string : ");
	scanf("%s", ch);
	printf("\n");
	//create tree
	len = strlen(ch) - 1;
	for (int k = 0; k <= len; k++) {
		num[k] = (int)ch[k] - '0';
	}
	pnum = num;
	TreeNode* root = CreateTree(NULL, *pnum++, NULL);
	while (len--) {
		TreeNode* newnode = CreateTree(NULL, *pnum++, NULL);
		TreeNode* cur = root;
		while (1) {
			if (cur->data > newnode->data) {
				if (cur->left == NULL) {
					i = -1;
					break;
				}
				cur = cur->left;
			}
			else if (cur->data <= newnode->data) {
				if (cur->right == NULL) {
					i = 1;
					break;
				}
				cur = cur->right;
			}
		}
		if (i == -1) cur->left = newnode;
		else if (i == 1) cur->right = newnode;
		i = 0;
	}

	printf("Pre-order : ");
	Preorder(root);
	printf("\n\n");

	printf("In-order : ");
	Inorder(root);
	printf("\n\n");

	printf("Post-order : ");
	Postorder(root);
	printf("\n\n");

	printf("Breadth First : ");
	Breadth_First_Traversal(root);
	printf("\n");

	DestroyTree(root);

	return 0;
}