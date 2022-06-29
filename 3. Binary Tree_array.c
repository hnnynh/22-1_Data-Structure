#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996)
#define MAX 16

typedef struct {
	int index;
}element;

typedef struct stack* stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
};
stackPointer top[MAX];

typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
};
queuePointer front[MAX], rear[MAX];

typedef struct {
	char name[10];
}Person;
Person pedigree[16] = { "", "Dusty", "Honey", "Brandy", "Brunhilde", 
						"Terry", "Coyote", "Nugget", "Gill", "Tansey", 
						"Tweed", "Zoe", "Crocus", "Primrose", "Nous", "Belk" };
// full binary tree 형식으로 15명

void Ax(char[]);
void Dx(char[]);
void Rxy(char[], char[]);
void push(int, element);
element pop(int);
void addq(int, element);
element deleteq(int);


int main() {

	while (1) {			// ? 출력하고 A(x), D(x), R(x, y) 대로 입력받기
		char com[30], cname[11], pname[11];
		int cal = 0, cal1 = 0;

		printf("? ");
		scanf("%[^\n]s", com);
		char adr = com[0];

		if (adr == '?') {
			printf("\n------------- END -------------");
			break;
		}

		switch (adr) {
		case 'A':
			for (int i = 2; com[i] != ')'; i++) {
				cname[i - 2] = com[i];
				cal = i;
			}
			cname[cal - 1] = '\0';
			Ax(cname);
			break;
		case 'D':
			for (int i = 2; com[i] != ')'; i++) {
				pname[i - 2] = com[i];
				cal = i;
			}
			pname[cal - 1] = '\0';
			Dx(pname);
			break;
		case 'R':

			for (int i = 2; com[i] != ','; i++) {
				cname[i - 2] = com[i];
				cal = i;
			}
			cname[cal - 1] = '\0';

			for (int i = 3; com[cal + i] != ')'; i++) {
				pname[i - 3] = com[cal + i];
				cal1 = i;
			}
			pname[cal1 - 2] = '\0';

			Rxy(cname, pname);
			break;
		}

		printf("\n\n");
		while (getchar() != '\n');			// 입력 버퍼 비우기
	}

}

void Ax(char cname[]) {		// 내려가기		A(x) 계산 -> queue

	int idx = 0;

	for (int i = 1; i < 16; i++) {
		if (strcmp(cname, pedigree[i].name) == 0) {
			idx = i;
			break;
		}
	}
	printf("A(%s) = ", cname);
	if (idx * 2 > MAX - 1) {
		printf("Unknown");
		return;
	}

	element item1, item2;
	item1.index = idx * 2;
	item2.index = idx * 2 + 1;
	addq(0, item1);
	addq(1, item2);
	int printIdx, f = -1, r = 1;

	while (1) {

		printIdx = deleteq(++f).index;
		if (printIdx == NULL)
			break;
		printf("%s", pedigree[printIdx].name);

		if (f != r)
			printf(", ");
		if (printIdx * 2 > MAX - 1)
			continue;

		item1.index = printIdx * 2;
		item2.index = printIdx * 2 + 1;
		addq(++r, item1);
		addq(++r, item2);
	}
}

void Dx(char pname[]) {		// 올라가기

	int idx = 0;

	for (int i = 1; i < 16; i++) {
		if (strcmp(pname, pedigree[i].name) == 0) {
			idx = i;
			break;
		}
	}
	printf("D(%s) = ", pname);

	if (idx <= 1) {
		printf("Unknown");
		return;
	}

	while (idx > 0) {
		idx /= 2;
		printf("%s", pedigree[idx].name);
		if (idx > 1)
			printf(", ");
	}
}

void Rxy(char nameX[], char nameY[]) {		
	// stack		x 노드는 y 노드의 조상 노드라고 가정

	int idxX = 0, idxY = 0;

	for (int i = 1; i < 16; i++) {
		if (strcmp(nameX, pedigree[i].name) == 0) {
			idxX = i;
			break;
		}
	}
	for (int i = 1; i < 16; i++) {
		if (strcmp(nameY, pedigree[i].name) == 0) {
			idxY = i;
			break;
		}
	}

	int top = -1;
	element item;
	item.index = idxY;
	push(++top, item);

	while (idxX <= idxY) {				// M - 17, F - 18

		if (idxX <= idxY / 2) {
			if (idxY % 2 == 1) {	// F
				item.index = 18;
				push(++top, item);
			}
			else {					// M
				item.index = 17;
				push(++top, item);
			}
		}

		idxY /= 2;
		item.index = idxY;
		push(++top, item);
	}

	printf("R(%s, %s) = ", nameX, nameY);

	while (top-- > 0) {
		int idx = pop(top).index;

		if (1 <= idx && idx <= 15)
			printf("%s", pedigree[idx].name);
		else if (idx == 17)
			printf("M");
		else if (idx == 18)
			printf("F");

		if (top > 0)
			printf("->");
	}
}

void push(int i, element item) {
	stackPointer temp = (stackPointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = top[i];
	top[i] = temp;
}

element pop(int i) {
	stackPointer temp = top[i];
	element item;
	if (!temp)
		return;		// stack empty
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;
}

void addq(int i, element item) {
	queuePointer temp = (queuePointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (front[i])
		rear[i]->link = temp;
	else
		front[i] = temp;
	rear[i] = temp;
}

element deleteq(int i) {
	queuePointer temp = front[i];
	element item;
	if (!temp)
		return;			// queue empty
	item = temp->data;
	front[i] = temp->link;
	free(temp);
	return item;
}