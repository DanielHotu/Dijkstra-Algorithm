#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <limits.h>

#define inf 1000000

void citire_graf(char* numefis, int*** a, int* noduri) {

	FILE* f = fopen(numefis, "r");
	if (f != 0) {

		int n, m, vi, vf, k;
		fscanf(f, "%d", &n);
		fscanf(f, "%d", &m);

		*a = (int**)malloc(n * sizeof(int*));
		for (int i = 0; i < n; i++)
			(*a)[i] = (int*)malloc(n * sizeof(int));

		*noduri = n;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				(*a)[i][j] = inf;

		for (int i = 0; i < m; i++) {
			fscanf(f, "%d %d %d", &vi, &vf, &k);
			(*a)[vi - 1][vf - 1] = k;
			(*a)[vf - 1][vi - 1] = k;

		}
		fclose(f);
	}
	else
		printf("Fisierul nu s a deschis.");

}

void afisare_matrice(int** a, int n) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (a[i][j] == inf)
				printf("INF  ");
			else
				printf("%d  ", a[i][j]);
		printf("\n");
	}

}

typedef struct {
	int cost;
	int parinte;
}Nod;

Nod* Djisktra(int** a, int n, int start) {

	int* vizitat = (int*)malloc(n * sizeof(int));
	Nod* rezultat = (Nod*)malloc(n * sizeof(Nod));

	for (int i = 0; i < n; i++) {
		vizitat[i] = 0;
		rezultat[i].cost = inf;
	}

	rezultat[start].cost = 0;
	vizitat[start] = 1;

	int nod = start;
	int next = -1;

	for (int i = 0; i < n - 1; i++) { /* toate drumurile */
		int min = inf;asta era in bucla de mai jos inainte
		for (int j = 0; j < n; j++) { /* toate nodurile */
			if (vizitat[j] == 0) {
				if (rezultat[j].cost > rezultat[nod].cost + a[nod][j]) {
					rezultat[j].cost = rezultat[nod].cost + a[nod][j];
					rezultat[j].parinte = nod;
				}

				if (rezultat[j].cost < min) {
					min = rezultat[j].cost;
					next = j;
				}
			}
		}
		nod = next;
		vizitat[nod] = 1;
	}
	free(vizitat);
	return rezultat;
}

void main() {

	char numefis[20];
	printf("Nume fisier: ");
	scanf("%s", numefis);
	int** a, n;
	citire_graf(numefis, &a, &n);
	afisare_matrice(a, n);

	int start;
	printf("Introduceti nod start: ");
	scanf("%d", &start);

	Nod* rezultat = Djisktra(a, n, start - 1);

	for (int i = 0; i < n; i++) {
		if (i != (start - 1)) { nu verficam corect aici, aveam != start inainte
			printf("\nDrumul de la %d la %d are costul: %d", start, i + 1, rezultat[i].cost);
			int nod = i;
			while (rezultat[nod].parinte != start - 1) {
				nod = rezultat[nod].parinte;
				printf("Nodul %d ", nod + 1);afisat dupa ce iau parintele, inainte se face pana sa iau parintele
			}
		}
	}

	for (int i = 0; i < n; i++)
		free(a[i]);
	free(a);
}
