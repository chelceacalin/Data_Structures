#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Elev Elev;
struct Elev {
	char* nume;
	int numarMatricol;
};

Elev creareElev(const char* nume, int nrMatricol) {

	Elev e;
	e.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(e.nume, nume);
	e.numarMatricol = nrMatricol;
	return e;
}

void afisareElev(Elev e) {
	printf("%s %d \n", e.nume, e.numarMatricol);
}

typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* next;
};


void InserareFinal(Nod** cap, Elev e) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->next = NULL;

	if ((*cap)) {

		Nod* aux = (*cap);
		
		while (aux->next)
			aux = aux->next;

		aux->next = nou;
	}
	else {
		(*cap) = nou;
	}
}

void afisareLista(Nod* cap) {

	while (cap) {

		afisareElev(cap->info);
		cap = cap->next;
	}
}

void dezalocaLista(Nod** cap) {

	if ((*cap)) {

		while ((*cap)) {

			Nod* aux = (*cap);
			(*cap) = (*cap)->next;
			free(aux->info.nume);
			free(aux);
		}
	}
}


typedef struct HashTable HashTable;
struct HashTable {
	
	Nod** vector;
	int dimensiune;
};

HashTable creareHashTable(int dimensiune) {
	HashTable ht;
	ht.dimensiune = dimensiune;
	
	ht.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < ht.dimensiune; i++)
		ht.vector[i] = NULL;
	return ht;
}

int functieHash(HashTable ht, Elev e) {
	return e.numarMatricol % ht.dimensiune;
}

void InserareHash(HashTable* ht, Elev e) {

	if (ht->dimensiune) {

		int pozitie = functieHash((*ht), e);

		if (ht->vector[pozitie]) {
			InserareFinal(&ht->vector[pozitie],e);
		}
		else
			InserareFinal(&ht->vector[pozitie], e);
	}

}


void afisareHash(HashTable ht) {

	if (ht.dimensiune) {
		for (int i = 0; i < ht.dimensiune; i++) {
			printf("\n\n Pozitie: %d \n", i);
			if (ht.vector[i]) {
				afisareLista(ht.vector[i]);
			}
			else
				printf(" - - - \n");
		}
	}
}


void dezalocaHash(HashTable* ht) {

	if (ht->dimensiune) {
		for (int i = 0; i < ht->dimensiune; i++) {
			if (ht->vector[i]) {
				dezalocaLista(&ht->vector[i]);
			}
		}
	}
}

Elev searchInHash(HashTable ht, int nrMatricol) {
	
	Elev e = creareElev("CEVA", nrMatricol);
	if (ht.dimensiune) {

		int pozitie = functieHash(ht, e);

		if (ht.vector[pozitie]) {

			Nod* aux = ht.vector[pozitie];

			while (aux) {

				if (aux->info.numarMatricol == nrMatricol)
					return aux->info;

				aux = aux->next;
			}
		}
		else
		{
			return creareElev("Negasit", 0);
		}
	}

}

void stergereInHash(HashTable* ht, int nrMatricol) {

	Elev e = creareElev("CEVA", nrMatricol);
	if ((*ht).dimensiune) {

		int pozitie = functieHash((*ht), e);

		if ((*ht).vector[pozitie]) {

			
			if ((*ht).vector[pozitie]->info.numarMatricol == nrMatricol) {
				Nod* aux = ht->vector[pozitie];
				ht->vector[pozitie] = ht->vector[pozitie]->next;

				free(aux->info.nume);
				free(aux);
			}
			else
			{
				Nod* aux = ht->vector[pozitie];
				while (aux->next && aux->next->info.numarMatricol != nrMatricol) {
					aux = aux->next;
				}

				if (aux->next) {

					Nod* temp = aux->next;

					if (temp->next) {
						aux->next = temp->next;
						free(temp->info.nume);
						free(temp);
					}
					else
					{
						free(aux->next->info.nume);
						free(aux->next);
						aux->next = NULL;
					}

				}
			}
			
		}
		else
		{
			return creareElev("Negasit", 0);
		}
	}

}


int main() {

	HashTable ht = creareHashTable(5);
	FILE* f = fopen("fisier.txt", "rt");
	if (!f) {
		printf("Eroare");
	}
	else
	{
		while (!feof(f)) {
			Elev e;
			
			char nume[20];
			fscanf(f, "%s", nume);
			e.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
			strcpy(e.nume, nume);
			fscanf(f, "%d", &e.numarMatricol);

		
			InserareHash(&ht, e);
		}
		fclose(f);
	}
	afisareHash(ht);
	printf("\n Dupa stergere: \n\n");
	//dezalocaHash(&ht);
	//Elev e = searchInHash(ht,52);
	//afisareElev(e);


	stergereInHash(&ht, 90);

	afisareHash(ht);


}