#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer;
	float kilometriiParcursi;
	char initialaProducator;
};

struct Masina initializare(int id, int anFabricatie, const char* sofer, float kilometriiParcursi, char initialaProducator) {
	struct Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;

	if (sofer != NULL)
	{
		m.sofer = (char*)malloc(strlen(sofer) + 1);
		strcpy_s(m.sofer, strlen(sofer) + 1, sofer);
	}
	else
		m.sofer = NULL;

	m.kilometriiParcursi = kilometriiParcursi;
	m.initialaProducator = initialaProducator;
	return m;
}

void afisare(struct Masina m) {
	printf("ID: %d \n", m.id);
	printf("An fabricatie: %d \n", m.anFabricatie);
	printf("Sofer: %s \n", m.sofer);
	printf("Kilometrii Parcursi : %f \n", m.kilometriiParcursi);
	printf("Initiala producator: %c \n", m.initialaProducator);
}

void afisareVector(struct Masina* vector, int nrElemente) {
	//apelarea elementelor din vector cu functia afisare

	if (vector != NULL && nrElemente > 0)
		for (int i = 0; i < nrElemente; i++)
		{
			afisare(vector[i]);
			printf("\n");
		}
}

struct Masina* copiazaPrimeleNElemente(struct Masina* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate

	struct Masina* vectorNou = NULL;
	if (vector != NULL && nrElementeCopiate <= nrElemente && nrElementeCopiate > 0)
	{
		vectorNou = malloc(sizeof(struct Masina) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++)
			//Shallow copy - copiaza aceeasi adresa de memorie
			vectorNou[i] = initializare(vector[i].id, vector[i].anFabricatie, vector[i].sofer, vector[i].kilometriiParcursi, vector[i].initialaProducator);
	}

	return vectorNou;
}

void dezalocare(struct Masina** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul

	if ((*vector) != NULL && *nrElemente > 0)
		for (int i = 0; i < *nrElemente; i++)
			free((*vector)[i].sofer);
	free(*vector);

	*vector = NULL;
	*nrElemente = 0;
}

void copiazaMasiniCuMultiKilometri(struct Masina* vector, char nrElemente, float prag, struct Masina** vectorNou, int* dimensiune) {
	if (vector != NULL && nrElemente > 0)
	{
		for (int i = 0; i < nrElemente; i++)
		{
			if (vector[i].kilometriiParcursi > prag)
			{
				(*dimensiune)++;
			}
		}
	}
	(*vectorNou) = malloc(sizeof(struct Masina) * (*dimensiune));
	int contor = 0;
	for (int i = 0; i < nrElemente; i++)
	{
		if (vector[i].kilometriiParcursi > prag)
		{
			(*vectorNou)[contor] = vector[i];
			(*vectorNou)[contor].sofer = malloc(sizeof(char) * strlen(vector[i].sofer) + 1);
			strcpy_s((*vectorNou)[contor].sofer, strlen(vector[i].sofer) + 1, vector[i].sofer);
			contor++;
		}
	}
}



struct Masina getPrimaMasinaDupaSofer(struct Masina* vector, int nrElemente, const char* soferCautat) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat

	for (int i = 0; i < nrElemente; i++)
		if (strcmp(vector[i].sofer, soferCautat) == 0)
			return vector[i];


	return initializare(-1, -1, NULL, -1, '-');
}



int main() {
	int nrElemente = 3;
	struct Masina* vector_masini = malloc(sizeof(struct Masina) * nrElemente);
	vector_masini[0] = initializare(1, 2010, "Marian", 2100, 'F');
	vector_masini[1] = initializare(2, 2008, "Cristi", 3500.6, 'A');
	vector_masini[2] = initializare(3, 2012, "Andrei", 1000, 'B');

	//afisareVector(vector_masini, nrElemente);

	int nrElementeCopiate = 2;
	struct Masina* vector_nou = copiazaPrimeleNElemente(vector_masini, nrElemente, 2);
	printf("Vector masini copiate: \n");
	afisareVector(vector_nou, nrElementeCopiate);

	dezalocare(&vector_nou, &nrElementeCopiate);

	float prag = 2000;
	copiazaMasiniCuMultiKilometri(vector_masini, nrElemente, prag, &vector_nou, &nrElementeCopiate);

	printf("Masini cu multi kilometri: \n");
	afisareVector(vector_nou, nrElementeCopiate);

	printf("Prima masina: \n");
	struct Masina primaMasina = getPrimaMasinaDupaSofer(vector_masini, nrElemente, "Ion");
	afisare(primaMasina);

	dezalocare(&vector_masini, &nrElemente);

	return 0;
}