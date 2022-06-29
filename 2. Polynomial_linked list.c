#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)

#define MAX_DEGREE 9

typedef struct {		// 계수 배열
	int degree;
	int coef[MAX_DEGREE + 1];
}CoefPoly;

typedef struct term* ListPoly;		// linked list 배열
typedef struct term {
	int coef;
	int exp;
	ListPoly link;
};

void printCoef(CoefPoly);
void printList(ListPoly);
void pMultiply(CoefPoly, CoefPoly, ListPoly*);
void insert(ListPoly*, ListPoly);

void main() {

	CoefPoly A, B;

	for (int i = 0; i < 3; i++) {

		printf("Degree of A: ");
		scanf("%d", &A.degree);
		for (int i = 0; i <= A.degree; i++)
			A.coef[i] = 0;

		printf("Enter A terms \n");
		for (int i = 0; i < 3; i++) {
			int c, e = 0;
			printf("A term %d: ", i + 1);
			scanf("%d %d", &c, &e);
			A.coef[e] = c;
		}

		printf("\nDegree of B: ");
		scanf("%d", &B.degree);
		for (int i = 0; i <= B.degree; i++)
			B.coef[i] = 0;

		printf("Enter B terms \n");
		for (int i = 0; i < 3; i++) {
			int c, e = 0;
			printf("B term %d: ", i + 1);
			scanf("%d %d", &c, &e);
			B.coef[e] = c;
		}

		printf("\npoly A: ");						// 저장된 다항식 A 출력
		printCoef(A);

		printf("poly B: ");					// 저장된 다항식 B 출력
		printCoef(B);


		ListPoly D = (ListPoly)malloc(sizeof(*D));
		D = NULL;
		pMultiply(A, B, &D);

		printf("poly D: ");					// 다항식 D = A * B 출력
		printList(D);
	}
}

void pMultiply(CoefPoly a, CoefPoly b, ListPoly* d) {

	ListPoly dFirst = *d;

	for (int i = a.degree; i >= 0; i--) {
		for (int j = b.degree; j >= 0; j--) {
			if (a.coef[i] * b.coef[j] == 0)
				continue;

			ListPoly temp = (ListPoly)malloc(sizeof(*temp));
			temp->coef = a.coef[i] * b.coef[j];
			temp->exp = i + j;
			temp->link = NULL;

			if (dFirst != NULL) {
				insert(&dFirst, temp);
			}
			else {		// (1) 없고 list가 empty인 경우 (즉, 항 abxi+j를 표현한 노드가 linked list의 유일한 노드가 되는 경우)
				*d = temp;
				dFirst = temp;
			}
		}
	}
}

void insert(ListPoly* d, ListPoly x) {
	int f = 0;
	ListPoly dd = *d;
	ListPoly prev = (ListPoly)malloc(sizeof(*prev));
	prev = NULL;

	while (dd) {
		if (dd->exp == x->exp) {
			if (dd->coef + x->coef == 0) {	// (4) 이미 있고 항 abxi+j를 반영하였을 때 계수가 0 이 되는 경우
				if (prev)
					prev->link = x->link;
				else
					dd = dd->link;
				free(x);
			}
			else {			// (3) 이미 있고 항 abxi+j를 반영하였을 때 계수가 0 이 아닌 경우,
				dd->coef += x->coef;
			}
			return;
		}
		else if ((*d)->exp < x->exp) {		// (2) 없고 list가 empty가 아닌 경우 (현재 d 앞에 삽입)
			if (prev) {
				x->link = prev->link;
				prev->link = x;
			}
			else
				x->link = dd;
			return;
		}
		prev = dd;
		dd = dd->link;
	}
	prev->link = x;			// (2) 없고 list가 empty가 아닌 경우 (마지막에 삽입)
}

void printCoef(CoefPoly p) {

	for (int i = p.degree; i > 0; i--) {
		printf("%dx%d", p.coef[i], i);
		if (p.coef[i - 1] >= 0)
			printf("+");
	}
	printf("%dx%d", p.coef[0], 0);

	printf("\n");
}

void printList(ListPoly p) {

	while (p != NULL) {
		printf("%dx%d", p->coef, p->exp);
		if (p->link != NULL) {
			if (p->link->coef > 0)
				printf("+");
		}
		p = p->link;
	}

	printf("\n\n");
}