#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Elev Elev;

struct Elev {
	char* nume;
	int nr_mat;
};


Elev creareElev(char* nume, int nr_mat) {

	Elev e;
	e.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(e.nume, nume);
	e.nr_mat = nr_mat;
	return e;
}

void AfisareElev(Elev e) {
	printf(" %s %d \r\n", e.nume, e.nr_mat);
}

typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* next;
	Nod* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* first;
	Nod* last;
};

void InsertInceput(ListaDubla* lista, Elev e) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->next = NULL;
	nou->prev = NULL;

	if (lista->first) {

		lista->first->prev = nou;
		nou->next = lista->first;
		lista->first = nou;
	}
	else
	{
		lista->first = nou;
		lista->last = nou;
	}
}

void InsertFinal(ListaDubla* lista, Elev e) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->next = NULL;
	nou->prev = NULL;

	if (lista->first) {
		Nod* aux = lista->first;

		while (aux->next)
			aux = aux->next;


		lista->last->next = nou;
		nou->prev = lista->last;
		lista->last = nou;
	}
	else {
		lista->first = nou;
		lista->last = nou;
	}
}

void AfisareLista(ListaDubla lista) {

	if (lista.first) {
		Nod* aux = lista.first;
		while (aux) {
			AfisareElev(aux->info);
			aux = aux->next;
		}
	}
}


void Dezaloca(ListaDubla* lista) {

	if (lista->first) {

		while (lista->first) {
			Nod* aux = lista->first;
			lista->first = lista->first->next;	
			free(aux->info.nume);
			free(aux);
		
		}
	}

}

void InserarePozitie(ListaDubla* lista, Elev e, int pozitie) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = e;
	nou->next = NULL;
	nou->prev = NULL;

	if (lista->first) {

		if (pozitie == 1) {
			InsertInceput(lista, e);
		}
		else
		{
			int cnt = 1;
			Nod* aux = lista->first;
			while (aux->next && cnt < pozitie - 1) {
				aux = aux->next;
				cnt++;
			}

			if (aux->next) {

				Nod* temp = aux->next;
				aux->next = nou;
				nou->prev = aux;
				nou->next = temp;
				temp->prev = nou;

			}
			else
				InsertFinal(lista, e);
		}

	}

}


void StergerePozitie(ListaDubla* lista, int pozitie) {

	if (lista->first) {

		if (pozitie == 1) {
			Nod* aux = lista->first;
			lista->first = lista->first->next;
			free(aux->info.nume);
			free(aux);
		}
		else
		{
			int cnt = 1;
			Nod* aux = lista->first;
			while (aux->next && cnt < pozitie - 1) {
				aux = aux->next;
				cnt++;
			}

			if (aux->next) {

				Nod* temp = aux->next;

				if (temp->next) {
					aux->next = temp->next;
					temp->next->prev = aux;
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

}

void SortareDuparNrMat(ListaDubla* lista) {
	
	if (lista->first) {

		Nod* aux = lista->first;
		while (aux->next) {
			Nod* p = aux->next;
			while (p) {
				if (aux->info.nr_mat > p->info.nr_mat) {
					Elev e = aux->info;
					aux->info = p->info;
					p->info = e;
				}
				p = p->next;
			}
			aux = aux->next;
		}
	}
}

int main() {
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	InsertInceput(&lista, creareElev("E1",1));
	InsertInceput(&lista, creareElev("E2", 2));
	InsertInceput(&lista, creareElev("E3", 3));
	InsertFinal(&lista, creareElev("E4", 4));
	InsertFinal(&lista, creareElev("E5", 5));
	InsertFinal(&lista, creareElev("E6", 6));
	//AfisareLista(lista);
	//Dezaloca(&lista);
	AfisareLista(lista);
	printf("\n\n DUPA INSEARE \n\n");
	InserarePozitie(&lista, creareElev("ELEV NOU", 10),7);
	AfisareLista(lista);

	printf("\n\n DUPA Stergere \n\n");
	StergerePozitie(&lista, 7);
	AfisareLista(lista);

	printf("\n\n DUPA SORTARE \n\n");
	SortareDuparNrMat(&lista);
	AfisareLista(lista);
}