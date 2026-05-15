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

static void inserirAVL(BinTree *t, int *v, int n) {
	for (int i = 0; i < n; i++) {
		t->root = insertAVL(t, t->root, v[i]);
	}
}

int main(void) {
	int *v = malloc(sizeof(int) * N);
	if (v == NULL) {
		return 1;
	}

	srand((unsigned)time(NULL));

	preencherOrdenado(v, N);

	BinTree *ordenada = BTcreate();
	if (ordenada == NULL) {
		free(v);
		return 1;
	}

	clock_t inicio = clock();
	inserirAVL(ordenada, v, N);
	clock_t fim = clock();

	printf("Insercao ordenada:\n");
	printf("Tempo: %.2f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
	printf("Altura: %d\n", alturaNo(ordenada->root));
	printf("Rotacoes: %u\n\n", ordenada->rotacoes);

	embaralhar(v, N);

	BinTree *aleatoria = BTcreate();
	if (aleatoria == NULL) {
		free(v);
		return 1;
	}

	inicio = clock();
	inserirAVL(aleatoria, v, N);
	fim = clock();

	printf("Insercao aleatoria:\n");
	printf("Tempo: %.2f s\n", (double)(fim - inicio) / CLOCKS_PER_SEC);
	printf("Altura: %d\n", alturaNo(aleatoria->root));
	printf("Rotacoes: %u\n", aleatoria->rotacoes);

	free(v);
	free(ordenada);
	free(aleatoria);

	return 0;
}

