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

struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod N;

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

void afisareListaMasini(N* nod) {
	while (nod)
	{
		afisareMasina(nod->info);
		nod = nod->next;
	}
}

void adaugaMasinaInLista(N** lista, Masina masinaNoua) {
	N* nodNou;
	nodNou = (N*)malloc(sizeof(N));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;

	if (*lista == NULL)
		(*lista) = nodNou;
	else
	{
		N* aux = (*lista);
		while (aux->next)
			aux = aux->next;
		aux->next = nodNou;
	}
}

void adaugaLaInceputInLista(/*lista de masini*/ Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
}

void* citireListaMasiniDinFisier(const char* numeFisier)
//pointer la void este un pointer generic 
//void simplu nu returneaza nimic
{
	FILE* f;
	f = fopen(numeFisier, "r");
	N** lista = NULL;
	while (!feof(f))
	{
		Masina m = citireMasinaDinFisier(f);
		adaugaMasinaInLista(&lista, m);
	}
	fclose(f);

	return lista;
}

void dezalocareListaMasini(N** lista) {
	while ((*lista))
	{
		N* p = (*lista);
		(*lista) = (*lista)->next;
		free(p->info.model);
		free(p->info.numeSofer);
		free(p);
	}
}

float calculeazaPretMediu(N* lista) {
	float suma = 0;
	int contor = 0;
	while (lista)
	{
		suma += lista->info.pret;
		contor++;
		lista = lista->next;
	}
	if (contor == 0)
		return 0;
	else return suma / contor;
}

void stergeMasiniDinSeria(/*lista masini*/ char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

float calculeazaPretulMasinilorUnuiSofer(N* lista, const char* numeSofer) {
	float suma = 0;
	while (lista)
	{
		if (strcpy(lista->info.numeSofer, numeSofer) == 0)
			suma += lista->info.pret;
		lista = lista->next;
	}
	return suma;
}

int getNrUsiMasinaScumpa(N* lista) {
	if (lista)
	{
		float pretMaxim = lista->info.pret;
		int nrUsi = lista->info.nrUsi;
		lista = lista->next;
		while (lista)
		{
			if (lista->info.pret > pretMaxim)
			{
				pretMaxim = lista->info.pret;
				nrUsi = lista->info.nrUsi;
			}
			lista = lista->next;
		}
		return nrUsi;
	}
	return 0;
}

int main() {
	N* listaMasini = NULL;
	listaMasini = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(listaMasini);
	printf("\n");

	float medie = calculeazaPretMediu(listaMasini);
	printf("Pretul mediu al masinilor este: %.2f\n", medie);

	float sumaSofer = calculeazaPretulMasinilorUnuiSofer(listaMasini, "Ionescu");
	printf("Suma masinilor lui Ionescu este: %.2f\n", sumaSofer);

	int nrUsi = getNrUsiMasinaScumpa(listaMasini);
	printf("Numarul de usi al masinii celei mai scumpe este: %d\n", nrUsi);

	dezalocareListaMasini(&listaMasini);

	return 0;
}