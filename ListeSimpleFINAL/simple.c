#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Avion Avion;
struct Avion {
	char* companie;
	int capacitate;
};

Avion creareAvion(const char* companie, int capacitate) {
	Avion a;
	a.companie = (char*)malloc((strlen(companie) + 1) * sizeof(char));
	strcpy(a.companie, companie);
	a.capacitate = capacitate;
	return a;
}
void AfiseazaAvion(Avion a) {
	printf("%s %d \r\n", a.companie, a.capacitate);
}


typedef struct Nod Nod;
struct Nod {
	Avion info;
	Nod* next;
};

void InserareInceput(Nod** cap,Avion a) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;

	if ((*cap)) {

		nou->next = (*cap);
		(*cap) = nou;
	}
	else
	{
		(*cap) = nou;
	}
}

void InserareFinal(Nod** cap, Avion a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;

	if ((*cap)) {

		Nod* aux = (*cap);
		while (aux->next)
			aux = aux->next;

		aux->next = nou;
	}
	else
	{
		(*cap) = nou;
	}
}

void AfisareLista(Nod* cap) {

	while (cap) {

		AfiseazaAvion(cap->info);
		cap = cap->next;
	}
}

void Dezaloca(Nod** cap) {

	if ((*cap)) {


		while ((*cap)) {

			Nod* aux = (*cap);
			(*cap) = (*cap)->next;
			free(aux->info.companie);
			free(aux);
		}
	}
	(*cap) = NULL;
}


void stergeCapacitate(Nod** cap, int capacitate) {
	
	if ((*cap)) {

		if ((*cap)->info.capacitate == capacitate) {
			Nod* aux = (*cap);
			(*cap) = (*cap)->next;
			free(aux->info.companie);
			free(aux);
		}
		else
		{
			Nod* aux = (*cap);

			while (aux->next && aux->next->info.capacitate != capacitate) {
				aux = aux->next;
			}


			if (aux->next)
			{
				Nod* temp = aux->next;

				if (temp->next) {
					aux->next = temp->next;
					free(temp->info.companie);
					free(temp);
				}
				else
				{
					free(aux->next->info.companie);
					aux->next = NULL;
				}
			}
		}
	}
}

void sortareListaDupaCapacitate(Nod** cap) {

	if((*cap)){
	
		Nod* aux = (*cap);

		while (aux->next) {

			Nod* temp = aux->next;

			while (temp) {

				if (aux->info.capacitate > temp->info.capacitate) {
					Avion a = aux->info;
					aux->info = temp->info;
					temp->info = a;
				}

				temp = temp->next;
			}
			aux = aux->next;
		}
	}
}

int sumaCapacitati(Nod* cap) {

	int sum = 0;
	while (cap) {
		int val = cap->info.capacitate;
		sum += val;
		cap = cap->next;
	}
	return sum;
}

Nod* cautaCapacitate(Nod* cap, int capacitate) {


	if (cap) {

		while (cap) {

			if (cap->info.capacitate ==capacitate)
				return cap;

			cap = cap->next;
		}

	}
}


void StergerePozitie(Nod** cap, int pozitie) {

	if ((*cap)) {
		
		if (pozitie == 1) {
			Nod* aux = (*cap);
			(*cap) = (*cap)->next;
			free(aux->info.companie);
			free(aux);
		}
		else
		{
			Nod* aux = (*cap);
			int cnt = 1;

			while(aux->next && cnt < pozitie - 1) {
				aux = aux->next;
				cnt++;
			}

			if (aux->next) {

				Nod* temp = aux->next;
				if (temp->next) {
					aux->next = temp->next;
					free(temp->info.companie);
					free(temp);
				}
				else
				{
					free(aux->next->info.companie);
					aux->next = NULL;
				}
			}
		}
	}
}

void InserarePozitie(Nod** cap, int pozitie,Avion a) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = a;
	nou->next = NULL;
	
	int cnt = 1;
	if ((*cap)) {

		Nod* aux = (*cap);
		if (pozitie == 1) {
			InserareInceput(&(*cap), a);
		}
		else
		{
			while (aux->next && cnt < pozitie - 1) {
				aux = aux->next;
				cnt++;
			}

			if (aux->next) {

				Nod* temp = aux->next;

				aux->next = nou;
				nou->next = temp;
			}
			else
			{
				InserareFinal(&(*cap), a);
			}

		}
	
	}
	
}

void CitireLista(const char* numefisier, Nod** cap) {

	FILE* f = fopen(numefisier, "rt");
	if (!f) {
		printf("Eroare");
	}
	else
	{
		while(!feof(f)){
			Avion a;
			char nume[20];
			fscanf(f, "%s", nume);
			a.companie = (char*)malloc((strlen(nume) + 1) * sizeof(char));
			strcpy(a.companie, nume);
			fscanf(f, "%d", &a.capacitate);
			InserareInceput(&(*cap), a);
			
		}
		fclose(f);
	}

}

int main() {

	Nod* lista = NULL;
	InserareInceput(&lista, creareAvion("C1", 1));
	InserareInceput(&lista, creareAvion("C2", 2));
	InserareInceput(&lista, creareAvion("C3", 3));
	//AfisareLista(lista);
	//printf("Afisarea Lista 1 \n\n");

	InserareFinal(&lista, creareAvion("C4", 4));
	InserareFinal(&lista, creareAvion("C5", 5));
	InserareFinal(&lista, creareAvion("C6", 6));
	//AfisareLista(lista);
	/*Dezaloca(&lista);
	printf("Afisarea Lista DUPA DEZALOCARE \n\n");
	AfisareLista(lista);*/
	/*printf("Afisarea Lista DUPA STERGERE \n\n");*/

	//stergeCapacitate(&lista,1);
	//AfisareLista(lista);
	sortareListaDupaCapacitate(&lista);
	printf("Afisarea Lista DUPA SORTARE \n\n");
	AfisareLista(lista);


	//printf("Afisarea Lista DUPA Cautare \n\n");

	//Nod* nou = cautaCapacitate(lista,6);
	//AfiseazaAvion(nou->info);

		/*int suma = sumaCapacitati(lista);
		printf("%d", suma);*/


	StergerePozitie(&lista, 6);
	printf("Afisarea Lista DUPA STERGERE POZITIE \n\n");
	AfisareLista(lista);

	InserarePozitie(&lista, 5, creareAvion("PozNoua", 10));

	printf("Afisarea Lista DUPA INSERARE POZITIE \n\n");
	AfisareLista(lista);

	printf("Afisarea Lista DUPA CITIRE FISIER \n\n");
	Nod* listaFisier = NULL;
	CitireLista("fisier.txt", &listaFisier);
	AfisareLista(listaFisier);
}