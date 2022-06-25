#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Prajitura Prajitura;

struct Prajitura {
	int ID;
	char* producator;
	float pret;
};

Prajitura crearePrajitura(int ID, const char* producator, float pret) {
	Prajitura p;
	p.ID = ID;
	p.producator = (char*)malloc((strlen(producator) + 1) * sizeof(char));
	strcpy(p.producator, producator);
	p.pret = pret;
	return p;
}

void AfisarePrajitura(Prajitura p) {
	printf(" %d %s %.2f \r\n", p.ID, p.producator, p.pret);
}


typedef struct Nod Nod;
struct Nod {
	Prajitura info;
	Nod* left;
	Nod* right;
};

void insertArbore(Nod** radacina, Prajitura p) {

	if ((*radacina)) {

		if ((*radacina)->info.ID < p.ID) {
			insertArbore(&(*radacina)->right, p);
		}
		else if ((*radacina)->info.ID > p.ID) {
			insertArbore(&(*radacina)->left, p);
		}
	}
	else
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = p;
		nou->left = NULL;
		nou->right = NULL;
		(*radacina) = nou;
	}
}

void AfisarePRE(Nod* radacina) {

	if (radacina) {
		AfisarePrajitura(radacina->info);
		AfisarePRE(radacina->left);
		AfisarePRE(radacina->right);
	}
}
void AfisareIN(Nod* radacina) {

	if (radacina) {
		AfisareIN(radacina->left);
		AfisarePrajitura(radacina->info);
		AfisareIN(radacina->right);
	}
}
void AfisarePOST(Nod* radacina) {

	if (radacina) {
		AfisarePOST(radacina->left);
		AfisarePOST(radacina->right);
		AfisarePrajitura(radacina->info);
	}
}

Prajitura cautarePrajitura(Nod* radacina,int ID) {

	if (radacina) {
		if (radacina->info.ID == ID) {
			Prajitura p = crearePrajitura(radacina->info.ID, radacina->info.producator, radacina->info.pret);
			return p;
		}
		cautarePrajitura(radacina->left, ID);
		cautarePrajitura(radacina->right, ID);
	}
	else
		return crearePrajitura(0, "Anonim", 0);
}




Prajitura idMaxim(Nod* radacina) {
	if (radacina) {

		while (radacina->right) {
			radacina = radacina->right;
		}

		return radacina->info;
	}

}

Nod* nodMaxim(Nod* radacina) {

	if (radacina) {
		while (radacina->right) {
			radacina = radacina->right;
		}

		return radacina;
	}
}

void DezalocaArbore(Nod** radacina) {

	if ((*radacina)) {
		DezalocaArbore(&(*radacina)->left);
		DezalocaArbore(&(*radacina)->right);
		free((*radacina)->info.producator);
		free((*radacina));
	}
	(*radacina) = NULL;
}

int maxDepth(Nod* radacina) {

	if (radacina) {
		int st = maxDepth(radacina->left);
		int dr = maxDepth(radacina->right);

		if (st > dr)
			return st + 1;
		else
			return dr + 1;


	}
	else
		return 0;
}

int NrPrajituriCuPretSub(Nod* radacina, float pret) {

	int cnt = 0;

	if (radacina) {

		if (radacina->info.pret < pret) {
			cnt+= 1 + NrPrajituriCuPretSub(radacina->left, pret) + NrPrajituriCuPretSub(radacina->right, pret);
		}
		else
		{
			cnt += 0 + NrPrajituriCuPretSub(radacina->left, pret) + NrPrajituriCuPretSub(radacina->right, pret);
		}
	}
	return cnt;
}

void schimbareNumePrajitura(Nod** radacina, const char* NumeAnterior, const char* NumeNou) {
	if ((*radacina)) {

		if (strcmp((*radacina)->info.producator, NumeAnterior) == 0) {
			free((*radacina)->info.producator);
			(*radacina)->info.producator = (char*)malloc((strlen(NumeNou) + 1) * sizeof(char));
			strcpy((*radacina)->info.producator, NumeNou);
		}

		schimbareNumePrajitura(&(*radacina)->left, NumeAnterior, NumeNou);
		schimbareNumePrajitura(&(*radacina)->right, NumeAnterior, NumeNou);
	}

}

float CalculeazaPreturiTotale(Nod* radacina) {

	float pTotal = 0;

	if (radacina) {
		float val = radacina->info.pret;
		pTotal += val+ CalculeazaPreturiTotale(radacina->left)+ CalculeazaPreturiTotale(radacina->right);
	}
	else
		return 0;

	return pTotal;
	
}

void afisareNivel(Nod* radacina, int nivelCautat, int nivelCurent) {

	if (radacina) {

		if (nivelCautat == nivelCurent) {
			AfisarePrajitura(radacina->info);
		}
		else
		{
			afisareNivel(radacina->left, nivelCautat, nivelCurent + 1);
			afisareNivel(radacina->right, nivelCautat, nivelCurent + 1);
		}
	}
}

Nod* cautaMinim(Nod* radacina) {
	if (radacina) {
		while (radacina->left)
			radacina = radacina->left;

		return radacina;
	}
}

void stergePrajitura(Nod** radacina, int ID) {
	if ((*radacina)) {

		if ((*radacina)->info.ID < ID) {
			stergePrajitura(&(*radacina)->right, ID);
		}
		else

			if ((*radacina)->info.ID > ID) {
				stergePrajitura(&(*radacina)->left , ID);
			}
			else

				if ((*radacina)->info.ID == ID) { //daca am gasit ID-ul
				
				
						//DACA E NOD FRUNZA
					if ((*radacina)->left == NULL && (*radacina)->right == NULL) {
						free((*radacina)->info.producator);
						free((*radacina));
						(*radacina) = NULL;
					}
					else
				
					if ((*radacina)->right == NULL && (*radacina)->left != NULL) { //doar stang
						Nod* aux = (*radacina);
						(*radacina) = (*radacina)->left;
						free(aux->info.producator);
						free(aux);
					}
					else
					if ((*radacina)->right != NULL && (*radacina)->left == NULL) { //are doar drept
						Nod* aux = (*radacina);
						(*radacina) = (*radacina)->right;
						free(aux->info.producator);
						free(aux);
						
					}
					else
						if ((*radacina)->right != NULL && (*radacina)->left != NULL) { //are 2 copii

							Nod* maxim = cautaMinim((*radacina)->right);
							free((*radacina)->info.producator);
							/* free((*radacina)); */
							(*radacina)->info = crearePrajitura(maxim->info.ID, maxim->info.producator, maxim->info.pret);
							stergePrajitura(&(*radacina)->right, maxim->info.ID);
						}

				}
	}

}

int main() {
	Nod* radacina = NULL;
	insertArbore(&radacina, crearePrajitura(10, "P10", 10));
	insertArbore(&radacina, crearePrajitura(7, "P7", 7));
	insertArbore(&radacina, crearePrajitura(3, "P4", 3));
	insertArbore(&radacina, crearePrajitura(4, "P4", 4));
	insertArbore(&radacina, crearePrajitura(11, "P11", 11));
	AfisarePRE(radacina);

	/*Prajitura P = cautarePrajitura(radacina,2);
	AfisarePrajitura(P);*/

	/*Prajitura g = idMaxim(radacina);
	AfisarePrajitura(g);*/

	/*Nod* max = nodMaxim(radacina);
	AfisarePrajitura(max->info);*/

	//DezalocaArbore(&radacina);
	//printf("\n Dupa dezalocare \n");
	//AfisarePRE(radacina);

	/*int depth = maxDepth(radacina);
	printf("Inaltime: %d", depth);*/

	/*int contorPrajituriCuPretSub = NrPrajituriCuPretSub(radacina, 9);
	printf("Contor: %d", contorPrajituriCuPretSub);*/

	//printf("\n Dupa Schimbare Nume \n");
	//schimbareNumePrajitura(&radacina, "P4", "PRAJITURA_NR_4");
	//AfisarePRE(radacina);

	/*float pTotal = CalculeazaPreturiTotale(radacina);
	printf("Preturi Totale: %.2f", pTotal); */

	stergePrajitura(&radacina, 10);
	printf("\n Dupa Stergere \n");
	AfisarePRE(radacina);
}