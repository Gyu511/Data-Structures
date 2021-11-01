#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Tree_Queue.h"
#include "Binary_Tree.h"

void Breadth_First_Traversal(TreeNode* root) {
	if (root == NULL) return;

	Queue* queue = CreateQueue();
	while (root) {
		printf("%c", root->data);
		if (root->left) Enqueue(queue, root->left);
		if (root->right) Enqueue(queue, root->right);
		if (!IsEmptyQueue(queue)) root = Dequeue(queue);
		else root = NULL;
	}
	DestroyQueue(queue);
}

int main(void) {
	char ch[256];
	char* pch = NULL;
	int len, num;
	int i = 2;
	Queue* queue = CreateQueue();
	
	printf("Input a string : ");
	scanf("%s", ch);
	printf("\n");
	//create tree
	len = strlen(ch) - 1;
	pch = ch;
	TreeNode* root = CreateTree(NULL, (char)*pch++, NULL);
	Enqueue(queue, root);
	while (len--) {
		TreeNode* newnode = CreateTree(NULL, (char)*pch++, NULL);
		while (1) {
			TreeNode* cur = QueueFront(queue);
			if (cur->left == NULL) {
				cur->left = newnode;
				Enqueue(queue, newnode);
				break;
			}
			else if (cur->right == NULL) {
				cur->right = newnode;
				Enqueue(queue, newnode);
				break;
			}
			else {
				Dequeue(queue);
			}
		}
	}
	DestroyQueue(queue);

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