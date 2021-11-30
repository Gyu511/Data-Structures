#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
	//int processed;
} TreeNode;

TreeNode* CreateTree(TreeNode* left, int data, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) return NULL;

	node->data = data;
	node->left = left;
	node->right = right;
	//node->processed = 0;

	return node;
}

TreeNode* LeftTree(TreeNode* root) {
	if (root == NULL) return NULL;
	return root->left;
}

int TreeData(TreeNode* root) {
	if (root == NULL) return 0;
	return root->data;
}

TreeNode* RightTree(TreeNode* root) {
	if (root == NULL) return NULL;
	return root->right;
}

int IsEmpty(TreeNode* root) {
	if (root == NULL) return 1;
	return 0;
}
/*
void ClearProcessed(TreeNode* root) {
	if (!root) return;

	root->processed = 0;
	ClearProcessed(root->left);
	ClearProcessed(root->right);
}
*/
void DestroyTree(TreeNode* root) {
	if (root == NULL) return;

	if (root->left != NULL) DestroyTree(root->left);
	if (root->right != NULL) DestroyTree(root->right);
	free(root);
}

void Preorder(TreeNode* root) {
	if (root == NULL) return;

	printf("%d", root->data);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder(TreeNode* root) {
	if (root == NULL) return;

	Inorder(root->left);
	printf("%d", root->data);
	Inorder(root->right);
}

void Postorder(TreeNode* root) {
	if (root == NULL) return;

	Postorder(root->left);
	Postorder(root->right);
	printf("%d", root->data);
}