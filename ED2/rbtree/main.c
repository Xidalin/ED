#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

static void embaralhar(int *v, int n) {
	for (int i = n - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
	}
}

static void preencherOrdenado(int *v, int n) {
	for (int i = 0; i < n; i++) {
		v[i] = i + 1;
	}
}

static void inserirRB(RBtree *t, int *v, int n) {
	for (int i = 0; i < n; i++) {
		RBinsert(t, v[i]);
	}
}

int main(void) {
	int *v = malloc(sizeof(int) * N);
	if (v == NULL) {
		return 1;
	}

	srand((unsigned)time(NULL));

	preencherOrdenado(v, N);

	RBtree *ordenada = RBcreate();
	if (ordenada == NULL) {
		free(v);
		return 1;
	}

	clock_t inicio = clock();
	inserirRB(ordenada, v, N);
	clock_t fim = clock();

	printf("RB - insercao ordenada:\n");
	printf("Tempo: %.2f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
	printf("Rotacoes: %u\n", ordenada->rotacoes);
	printf("coloracoes: %u\n\n", ordenada->coloracoes);

	embaralhar(v, N);

	RBtree *aleatoria = RBcreate();
	if (aleatoria == NULL) {
		free(v);
		return 1;
	}

	inicio = clock();
	inserirRB(aleatoria, v, N);
	fim = clock();

	printf("RB - insercao aleatoria:\n");
	printf("Tempo: %.2f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
	printf("Rotacoes: %u\n", aleatoria->rotacoes);
	printf("coloracoes: %u\n", aleatoria->coloracoes);

	free(v);
	free(ordenada);
	free(aleatoria);

	return 0;
}
