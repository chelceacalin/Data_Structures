#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Teatru Teatru;
struct Teatru {
	int id;
	char* denumire;
	int nrLocuri;
	float pretBilet;
};

Teatru initializare(int i, const char* d, int n, float p) {
	Teatru t;
	t.id = i;
	t.denumire = (char*)malloc(sizeof(char) * (strlen(d) + 1));
	strcpy(t.denumire, d);
	t.nrLocuri = n;
	t.pretBilet = p;
	return t;
}

void afisare(Teatru t) {
	printf("ID : %d %s , %d locuri, pretul %5.2f \n",t.id, t.denumire, t.nrLocuri, t.pretBilet);
}

typedef struct Heap Heap;
struct Heap {
	Teatru* vector;
	int dimensiune;
};


void FiltrareHeap(Heap *h,int index){
	int indexMax = index;
	int indexStang = 2 * indexMax + 1;
	int indexDrept = 2 * indexMax + 2;

	if (indexStang < h->dimensiune && h->vector[indexStang].id > h->vector[indexMax].id) {
		indexMax = indexStang;
	}

	if (indexDrept < h->dimensiune && h->vector[indexDrept].id > h->vector[indexMax].id) {
		indexMax = indexDrept;
	}

	if (indexMax != index) {
		Teatru t = h->vector[indexMax];
		h->vector[indexMax] = h->vector[index];
		h->vector[index] = t;

		for(int i=(h->dimensiune-1)/2;i>=0;i--)
			FiltrareHeap(h, i);
	}
}


void afisareHeap(Heap h) {
	if (h.dimensiune) {

		for (int i = 0; i < h.dimensiune; i++) {
			afisare(h.vector[i]);
		}
	}
}

void InserareHeap(Heap* h, Teatru t) {

	Teatru* nouVect = (Teatru*)malloc((h->dimensiune + 1) * sizeof(Teatru));

	for (int i = 0; i < h->dimensiune; i++) {
		nouVect[i] = h->vector[i];
	}

	nouVect[h->dimensiune] = t;

	h->vector = nouVect;
	h->dimensiune++;

	for (int i = (h->dimensiune - 1) / 2; i >= 0; i--) {
		FiltrareHeap(h, i);
	}
}

Teatru extragereHeap(Heap* h) {

	if (h->dimensiune) {

		Teatru aux = h->vector[0];
		h->vector[0] = h->vector[h->dimensiune - 1];
		h->vector[h->dimensiune - 1] = aux;

		h->dimensiune--;

		return aux;
	}
	else
		return initializare(0, "0", 0, 0);
}

void dezaloca(Heap* h) {

	if (h->dimensiune) {
		for (int i = 0; i < h->dimensiune; i++) {
			free(h->vector[i].denumire);
		}
	}
	free(h->vector);
	h->dimensiune = 0;
}

int main() {

	Heap h;
	h.dimensiune = 0;
	FILE* f = fopen("fisier.txt", "rt");
	if (!f) {
		printf("Eroare");
	}
	else
	{
		while (!feof(f)) {
			Teatru t;

			//ID
			fscanf(f, "%d", &t.id);

			//NUME
			char nume[30];
			fscanf(f, "%s", nume);
			t.denumire = (char*)malloc((strlen(nume) + 1) * sizeof(char));
			strcpy(t.denumire, nume);

			/// nrlocuri
			fscanf(f, "%d", &t.nrLocuri);

			//BILET
			fscanf(f, "%f", &t.pretBilet);

			InserareHeap(&h, t);
		}
		fclose(f);
	}

	afisareHeap(h);
	printf("\n\n Afisare teatru extras : \n");
	Teatru t = extragereHeap(&h);
	afisare(t);

	printf("\n\n Dupa Extragere : \n");
	for (int i = (h.dimensiune - 1) / 2; i >= 0; i--)
		FiltrareHeap(&h, i);
	afisareHeap(h);

	//printf("\n\n Dupa Dezalocare : \n");
	//dezaloca(&h);
	//afisareHeap(h);
	printf("\n\n Print Manual : \n");
	for (int i = 0; i < h.dimensiune; i++)
		printf("%d %s \n", h.vector[i].id, h.vector[i].denumire);


};