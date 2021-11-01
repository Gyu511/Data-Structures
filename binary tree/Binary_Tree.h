#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tree_Queue.h"

typedef char Element;

typedef struct TreeNode {
	Element data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode* CreateTree(TreeNode* left, Element data, TreeNode* right) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) return NULL;

	node->data = data;
	node->left = left;
	node->right = right;

	return node;
}

TreeNode* LeftTree(TreeNode* root) {
	if (root == NULL) return NULL;
	return root->left;
}

Element TreeData(TreeNode* root) {
	if (root == NULL) return 'X';
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

void DestroyTree(TreeNode* root) {
	if (root == NULL) return;

	if (root->left != NULL) DestroyTree(root->left);
	if (root->right != NULL) DestroyTree(root->right);
	free(root);
}

void Preorder(TreeNode* root) {
	if (root == NULL) return;

	printf("%c", root->data);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder(TreeNode* root) {
	if (root == NULL) return;

	Inorder(root->left);
	printf("%c", root->data);
	Inorder(root->right);
}

void Postorder(TreeNode* root) {
	if (root == NULL) return;

	Postorder(root->left);
	Postorder(root->right);
	printf("%c", root->data);
}