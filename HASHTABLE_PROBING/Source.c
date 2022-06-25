#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
} student;

typedef struct
{
	student** vect;
	int size;
} hashT;


student* creareStudent(int cod, const char* nume, float medie) {

	student* s=(student*)malloc(sizeof(student));
	s->cod = cod;
	s->medie = medie;
	s->nume = (char*)malloc((strlen(nume) + 1) * sizeof(char));
	strcpy(s->nume, nume);
	return s;
}

int functieHash(hashT tabela,int cheie)
{
	return cheie % tabela.size;
}


void inserare(hashT* ht, student* s) {

	int pozitie;
	if (ht->size) {

		pozitie = functieHash((*ht), s->cod);

		if (ht->vect[pozitie] == NULL) {
			ht->vect[pozitie] = s;
		}
		else {
			int index = 1;
			while (index + pozitie < ht->size) {

				if (ht->vect[index + pozitie] == NULL) {
					ht->vect[index + pozitie] = s;
				
				}
				index++;
			}
		}
	}
}

void stergere(hashT* ht, int Cod) {

	if (ht->vect) {

		int pozitie = functieHash((*ht), Cod);
		if (ht->vect[pozitie] = NULL)
			return  -1;
		else
		if (ht->vect[pozitie] == Cod) {
			free(ht->vect[pozitie]->nume);
			free(ht->vect[pozitie]);
			ht->vect[pozitie] = NULL;
		}
		else {
			int index = 1;

			while (index + pozitie < ht->size) {
				
				if (ht->vect[pozitie+index] == Cod) {
					free(ht->vect[pozitie+index]->nume);
					free(ht->vect[pozitie + index]);
					ht->vect[pozitie + index] = NULL;
					break;
				}

				
				index++;
			}
		}
	}

}

int main() {
	hashT ht;
	ht.size = 3;
	ht.vect = (student**)malloc(sizeof(student));
	for (int i = 0; i < ht.size; i++)
		ht.vect[i] = NULL;
	inserare(&ht, creareStudent(1, "Student-1", 1));
	inserare(&ht, creareStudent(2, "Student-1", 1));
	inserare(&ht, creareStudent(3, "Student-1", 1));

	stergere(&ht, 3);
	for (int i = 0; i < ht.size; i++) {
		if (ht.vect[i]) {
			printf("%d %s \r\n", ht.vect[i]->cod, ht.vect[i]->nume);

		}
	}
}