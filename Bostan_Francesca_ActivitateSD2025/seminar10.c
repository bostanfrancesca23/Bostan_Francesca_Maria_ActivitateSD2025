#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod
{
	Masina* info;
	struct Nod* stanga;
	struct Nod* dreapta;
	int gradEchilibru;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//int calculeazaInaltimeArbore(/*arbore de masini*/) {
//	//calculeaza inaltimea arborelui care este data de 
//	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
//	return 0;
//}

void rotireStanga(Nod** arbore)
{
	Nod* aux = (*arbore)->dreapta;
	(*arbore)->dreapta = aux->stanga;
	aux->stanga = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru++;
}

void rotireDreapta(Nod** arbore)
{
	Nod* aux = (*arbore)->stanga;
	(*arbore)->stanga = aux->dreapta;
	aux->dreapta = (*arbore);
	(*arbore) = aux;
	(*arbore)->gradEchilibru--;
}

void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
	if ((*radacina))
	{
		if ((*radacina)->info->id > masinaNoua.id)
		{
			adaugaMasinaInArboreEchilibrat(&((*radacina)->stanga), masinaNoua);
			(*radacina)->gradEchilibru++;
		}
		else
		{
			adaugaMasinaInArboreEchilibrat(&((*radacina)->dreapta), masinaNoua);
			(*radacina)->gradEchilibru--;
		}

		if ((*radacina)->gradEchilibru == 2)
			//avem dezechilibru in stanga
			if ((*radacina)->stanga->gradEchilibru == 1)
				//rotire la dreapta
				rotireDreapta(radacina);
			else
			{
				rotireStanga(&((*radacina)->stanga));
				rotireDreapta(radacina);
			}

		if ((*radacina)->gradEchilibru == -2)
		{
			if ((*radacina)->dreapta->gradEchilibru == 1)
				rotireDreapta(&((*radacina)->dreapta));
			rotireStanga(&((*radacina)->stanga));
		}
	}
	else
	{
		Nod* radacinaNoua = malloc(sizeof(radacina));
		radacinaNoua->info = masinaNoua; //eroare
		radacinaNoua->dreapta = NULL;
		radacinaNoua->stanga = NULL;
		radacinaNoua->gradEchilibru = 0;
		(*radacina) = radacinaNoua;
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* f = fopen(numeFisier, "r");
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInArboreEchilibrat(&arbore, m);
	}
	fclose(f);

	return arbore;
}

void afisareMasiniDinArborePreOrdine(Nod* arbore) {
	if (arbore)
	{
		afisareMasina(arbore->info);
		afisareMasiniDinArborePreOrdine(arbore->stanga);
		afisareMasiniDinArborePreOrdine(arbore->dreapta);
	}
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main()
{
	Nod* arbore = citireArboreDeMasiniDinFisier("masini.txt");
	afisareMasiniDinArborePreOrdine(arbore);
	return 0;
}