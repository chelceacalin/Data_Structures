#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Facultate  Facultate;

struct Facultate {
	int id;
	char* nume;
};

Facultate creareFacultate(int id, char* nume) {
	Facultate f;

	f.id = id;
	f.nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(f.nume, nume);
	return f;
}
void AfisFacultate(Facultate f) {
	printf(" %d %s \r\n", f.id, f.nume);
}

typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

struct NodPrincipal {

	Facultate info;
	NodPrincipal* next;
	NodSecundar* vecini;
};

struct NodSecundar {
	
	NodSecundar* next;
	NodPrincipal* info;
};


void afisareNodSecundar(NodSecundar* cap) {

	while (cap) {
		printf("\n");
		AfisFacultate(cap->info->info);
		cap = cap->next;
	}
}

void afisareGraf(NodPrincipal* cap) {
	while (cap) {
		printf("\n Nod Principal: %d %s \r\n", cap->info.id, cap->info.nume);
		afisareNodSecundar(cap->vecini);
		cap = cap->next;
		
	}
}


void dezalocaListaSecundara(NodSecundar** cap) {
	
		while ((*cap)) {
		NodSecundar* aux = (*cap);
		(*cap) = (*cap)->next;
		free(aux);
	}
}

	

void dezalocaGraf(NodPrincipal** cap) {
	
	while ((*cap)) {
		NodPrincipal* aux = (*cap);
		
		NodSecundar* sec = aux->vecini;
		dezalocaListaSecundara(&sec);

		(*cap) = (*cap)->next;
		free(aux->info.nume);
		free(aux);
	}
	(*cap) = NULL;

}






//grupare
void inserareNodPrincipal(NodPrincipal** cap, Facultate f) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = f;
	nou->next = NULL;
	nou->vecini = NULL;

	if ((*cap)) {

		NodPrincipal* aux = (*cap);
		while (aux->next)
			aux = aux->next;

		aux->next = nou;

	}
	else {
		(*cap) = nou;
	}
}

void InserareNodSecundar(NodSecundar** cap, NodPrincipal* info) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->info = info;
	nou->next = NULL;

	if ((*cap)) {
		NodSecundar* aux = (*cap);

		while (aux->next) {
			aux = aux->next;
		}
		aux->next = nou;
	}
	else
	{
		(*cap) = nou;
	}
}

NodPrincipal* cautaNod(NodPrincipal* cap, int ID) {

	if (cap) {

		while (cap) {
			if (cap->info.id == ID)
				return cap;
			cap = cap->next;
		}
	}
}



void creareMuchie(NodPrincipal* cap, int id1, int id2) {
	NodPrincipal* nod1 = cautaNod(cap, id1);
	NodPrincipal* nod2 = cautaNod(cap, id2);

	if (nod1 && nod2) {
		InserareNodSecundar(&nod1->vecini, nod2);
		InserareNodSecundar(&nod2->vecini, nod1);
	}
}


int main() {
	
	NodPrincipal* listaPr=NULL;

	inserareNodPrincipal(&listaPr, creareFacultate(1, "Fac-1"));
	inserareNodPrincipal(&listaPr, creareFacultate(2, "Fac-2"));
	inserareNodPrincipal(&listaPr, creareFacultate(3, "Fac-3"));
	inserareNodPrincipal(&listaPr, creareFacultate(4, "Fac-4"));
	inserareNodPrincipal(&listaPr, creareFacultate(6, "Fac-5"));
	inserareNodPrincipal(&listaPr, creareFacultate(5, "Fac-6"));

	creareMuchie(listaPr, 1, 2);
	creareMuchie(listaPr, 1, 3);
	creareMuchie(listaPr, 1, 4);
	afisareGraf(listaPr);
	printf("\n Dupa Dezalocare: ");
	dezalocaGraf(&listaPr);
	afisareGraf(listaPr);
}