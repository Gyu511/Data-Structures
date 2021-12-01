#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

typedef struct Tree {
	struct TreeNode* root;
	int (*compare)(void* argu1, void* argu2);
} Tree;

int comp(void* argu1, void* argu2) {
	return (*(int*)argu1 - *(int*)argu2);
}

Tree* CreateTree(int data) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	if (tree == NULL) return NULL;

	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) {
		free(tree);
		return NULL;
	}
	tree->root = node;
	tree->compare = comp;
	node->data = data;
	node->left = node->right = NULL;
	
	return tree;
}

TreeNode* FindSmallestBST(TreeNode* root) {
	if (root != NULL && root->left != NULL) return FindSmallestBST(root->left);
	else return root;
}

TreeNode* FindLargestBST(TreeNode* root) {
	if (root != NULL && root->right != NULL) return FindLargestBST(root->right);
	else return root;
}

TreeNode* SearchBST(TreeNode* root, int key) {
	if (root == NULL) {
		printf("There is no data\n"); 
		return NULL;
	}

	if (comp(&root->data, &key) > 0) return SearchBST(root->left, key);
	else if (comp(&root->data, &key) < 0) return SearchBST(root->right, key);
	else return root;
}

TreeNode* _addBST(TreeNode* root, TreeNode* newNode) {
	if (root == NULL) return newNode;

	if (comp(&root->data, &newNode->data) > 0) {
		root->left = _addBST(root->left, newNode);
	}
	else {
		root->right = _addBST(root->right, newNode);
	}
	return root;
}

TreeNode* _deleteBST(TreeNode* root, int data) {
	if (root == NULL) {
		printf("There is no data\n");
		return NULL;
	}

	if (comp(&root->data, &data) > 0) {
		root->left = _deleteBST(root->left, data);
	}
	else if (comp(&root->data, &data) < 0) {
		root->right = _deleteBST(root->right, data);
	}
	else {//delete
		TreeNode* del = NULL;
		if (!root->right) {
			del = root;
			root = root->left;
			free(del);
		}
		else if (!root->left) {
			del = root;
			root = root->right;
			free(del);
		}
		else {
			for (del = root->left; del->right != NULL; del = del->right);
			root->data = del->data;
			free(del);
		}
	}
	return root;
}

void InsertNode(Tree* tree, int data) {
	if (tree == NULL) return;

	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) return;

	node->data = data;
	node->left = node->right = NULL;
	_addBST(tree->root, node);
}

void DeleteNode(Tree* tree, int data) {
	if (tree == NULL) return;

	_deleteBST(tree->root, data);
}

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