#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct kurs {
	struct kurs *poprzedni;
	struct kurs *nastepny;
	char *nazwa_kursu;
	char *data;
	int ects;
	char *status;
	float ocena;
	char *miejsce;
	char *prowadzacy;
	char *godzina;
}kurs;


//bufor
void wypiszMenu();
int scanInt();
int sprawdzUtworzenie();
kurs *wyszukaj(kurs **seed);
char *sprawdzDate();
char *sprawdzGodzine();
float scanFloat();
float sprawdzOcene();
int pokazDynamicznie(kurs **seed);
//kurs *wyszukajtemp(kurs **seed);

//cia³o
void utworzBaze();
void zbierzDane(kurs *contact);
void dodajRecznie(kurs **seed);
void pokazKursy(kurs **seed);
void wyczysc(kurs **seed);
void wyczyscBezZakonczenia(kurs **seed);
void wczytajZPliku(kurs **seed, FILE *file);
void wczytajPlan(kurs **zarodek);
int liczDlugosc(kurs **seed);
void segregujKursy(kurs **seed);
void segregujEcts(kurs **seed);
void zapiszPlan(kurs **seed);
void wyczyscPlan(kurs **seed);
void wyrzucWybrany(kurs **seed);
void zmienStatus(kurs **seed);
void zmienDate(kurs **seed);
int porownajDaty(kurs *pierwszy, kurs *drugi);
void segregujDaty(kurs **seed);
void liczSrednia(kurs **seed);
int porownajDatyProjekt(kurs *pierwszy, char *data_2);
void szukajDat(kurs **seed);