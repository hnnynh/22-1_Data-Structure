#include <stdio.h>
#pragma warning(disable: 4996)

#define MAX_DEGREE 9
#define MAX_TERM 19		//최대 x^18 ~ x^0

typedef struct {		// 항 배열
	int coef;
	int expon;
}TermPoly;

typedef struct {		// 계수 배열
	int degree;
	int coef[MAX_DEGREE + 1];
}CoefPoly;

void pmultiply(CoefPoly, CoefPoly, TermPoly*, int*, int*);
void printCoef(CoefPoly);
void printTerm(TermPoly*, int);

// A, B는 계수배열 - 지수 오름순, 항 3개
// D는 항배열 - 지수 내림순, 항 9개 미만

int main() {		// D = A * B

	int degreeD = 0;
	int avail = 0;

	CoefPoly A, B;
	TermPoly D[MAX_TERM];


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

		pmultiply(A, B, D, &degreeD, &avail);

		printf("poly D: ");					// 다항식 D = A * B 출력
		printTerm(D, avail);
	}
}

void pmultiply(CoefPoly a, CoefPoly b, TermPoly* d, int* dd, int* ava) {
	// D = A * B - 지수 내림순으로 바로 저장

	*dd = a.degree + b.degree;
	for (int i = 0; i <= (*dd); i++) {
		d[i].coef = 0;
	}

	for (int i = a.degree; i >= 0; i--) {
		for (int j = b.degree; j >= 0; j--) {
			if (a.coef[i] * b.coef[j] == 0)
				continue;

			int f = 0;
			for (int k = 0; k < (*ava); k++) {
				if (d[k].expon == i + j) {
					d[k].coef += a.coef[i] * b.coef[j];
					f = 1;
					break;
				}
				else if (d[k].expon < i + j) {
					(*ava)++;
					for (int l = (*ava); l > k; l--) {
						d[l].expon = d[l - 1].expon;
						d[l].coef = d[l - 1].coef;
					}
					d[k].expon = i + j;
					d[k].coef += a.coef[i] * b.coef[j];
					f = 1;
					break;
				}
			}

			if (f)
				continue;
			else {
				d[*ava].expon = i + j;
				d[*ava].coef = a.coef[i] * b.coef[j];
				(*ava)++;
			}
		}
	}
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

void printTerm(TermPoly* t, int a) {

	for (int i = 0; i < a - 1; i++) {
		if (t[i].coef)
			printf("%dx%d", t[i].coef, t[i].expon);
		if (t[i + 1].coef > 0)
			printf("+");
	}
	if (t[a - 1].coef)
		printf("%dx%d", t[a - 1].coef, t[a - 1].expon);

	printf("\n\n");
}