#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)

typedef struct {
	char word[11];
	int count;
}element;
typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
};

void inorder(treePointer);
element* iterSearch(treePointer, char[]);
void insert(treePointer*, char[]);

int main() {

	treePointer root = NULL;
	
	while (1) {
		char str[11];
		printf("next word ? ");
		scanf("%s", str);

		if (strcmp("END", str) == 0)
			break;

		insert(&root, str);
		inorder(root);
		printf("\n\n");

		while (getchar() != '\n');			// 입력 버퍼 비우기
	}

}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%s:%d    ", ptr->data.word, ptr->data.count);
		inorder(ptr->rightChild);
	}
}

treePointer modifiedSearch(treePointer tree, char w[]) {

	treePointer temp = NULL;

	while(tree) {
		temp = tree;
		int cmp = strcmp(w, tree->data.word);

		if (cmp == 0) {
			tree->data.count += 1;
			return NULL;
		}
		else if (cmp < 0) 
			tree = tree->leftChild;	
		else 
			tree = tree->rightChild;		
	}

	return temp;
}

void insert(treePointer* node, char w[]) {
	treePointer ptr, temp = modifiedSearch(*node, w);

	if (temp || !(*node)) {
		ptr = malloc(sizeof(*ptr));
		strcpy(ptr->data.word, w);
		ptr->data.count = 1;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*node) {
			int cmp = strcmp(w, temp->data.word);
			if (cmp < 0)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else
			*node = ptr;
	}
}