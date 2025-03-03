#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer;
	float kilometriParcursi;
	char initialaProducator;
};

struct Masina initializare(int id, int anFabricatie, char* sofer, float kilometriParcursi, char initialaProducator) {
	struct Masina s;
	s.id = 1;
	//initializare structura 
	return s;
}

void afisare(struct Masina s) {
	//afisarea tuturor atributelor.
}

void modifica_Atribut(struct Masina s) {
	//modificarea unui atribut
}

void dezalocare(struct Masina* s) {
	//dezalocare campuri alocate dinamic
}

int main() {
	struct Masina masina();

	return 0;
}