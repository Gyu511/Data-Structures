#define _CRT_SECURE_NO_WARNINGS
#include "bst.h"

int main(void) {
	int num, sel;
	int i = 0;
	Tree* tree = NULL;
	TreeNode* node = NULL;

	while (1) {
		printf("Insert(0), Delete(1), Search(2), Smallest(3), Largest(4), Inorder(5), Stop(6) : ");
		scanf("%d", &sel);
		switch (sel)
		{
		case 0: printf("inset number : ");
			scanf("%d", &num);
			if (i == 0) tree = CreateTree(num);
			else InsertNode(tree, num);
			i++;
			break;
		case 1: if (i == 0) {
			printf("empty\n");
			break;
		}
			printf("delete number : ");
			scanf("%d", &num);
			DeleteNode(tree, num);
			i--;
			break;
		case 2:if (i == 0) {
			printf("empty\n");
			break;
		}
			  printf("Search number : ");
			  scanf("%d", &num);
			  if (SearchBST(tree->root, num)) printf("there it is");
			  break;
		case 3:if (i == 0) {
			printf("empty\n");
			break;
		}
			  node = FindSmallestBST(tree->root);
			  printf("%d\n", node->data);
			  break;
		case 4:if (i == 0) {
			printf("empty\n");
			break;
		}
			  node = FindLargestBST(tree->root);
			  printf("%d\n", node->data);
			  break;
		case 5: Inorder(tree->root);
			printf("\n");
			break;
		case 6: exit(1);
		default:
			break;
		}
	}

	return 0;
}