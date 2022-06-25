#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct Tara Tara;



struct Tara
{
	char* denumire;
	int populatie;
};

Tara CreareTara(const char* denumire, int populatie)
{
	Tara a;
	a.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(a.denumire, denumire);
	a.populatie = populatie;
	return a;
}

void AfisareTara(Tara t)
{
	printf("%s %d \n \n", t.denumire, t.populatie);
}

typedef struct Nod Nod;
struct Nod {

	Tara info;
	Nod* next;
};

void push(Nod** cap, Tara t) {


	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
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

void pushBack(Nod** cap, Tara t)
{


	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = t;
	nou->next = NULL;

	if ((*cap))
	{

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

Tara pop(Nod** cap) {

	if ((*cap)) {
		Nod* aux = (*cap);
		Tara t = aux->info;
		(*cap) = (*cap)->next;

		return t;
	}
	else
	{
		return CreareTara("ANONIM", 0);
	}

}

void afisareStiva(Nod** cap) {

	while ((*cap)) {
		Tara t = pop(&(*cap));
		AfisareTara(t);

	}
}

void stergeTara(Nod** cap, int populatie) {

	Nod* stivaAux = NULL;

	while ((*cap)->info.populatie != populatie) {
		Tara t = pop(&(*cap));
		push(&stivaAux, t);
	}

	if ((*cap)->info.populatie == populatie) {
		Tara t = pop(&(*cap));
		free(t.denumire);
	}

	while (stivaAux) {
		Tara t = pop(&stivaAux);
		push(&(*cap), t);
	}



}


int main() {
	Nod* stiva = NULL;
	push(&stiva, CreareTara("T1", 1));
	push(&stiva, CreareTara("T2", 2));
	push(&stiva, CreareTara("T3", 3));
	

	stergeTara(&stiva, 1);
	afisareStiva(&stiva);
	
}