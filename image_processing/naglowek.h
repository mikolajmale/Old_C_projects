#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <stdlib.h>

typedef struct
{
	int szerokosc;
	int wysokosc;
	int skala;
	int **dane;
	char *nazwa;
}obraz;

int skanInt();
char *sprawdzNazwe(char *nazwa);
char *nadajNazwe(char *nazwa);
void znejdzKomyntorz(obraz *obrazy, FILE *plik);

void menu(obraz *obrazy);
obraz *dodejObraz(obraz *obrazy, int iteracja);
void wyswietlNazwe(obraz *obrazy, int iteracja);
void zakoncz(obraz *obrazy, int iteracja);
void zapyszObraz(obraz *obrazy, int iteracja);
void przepiszDane(obraz zapisz, obraz obrazy);
void przepiszObraz(char *nazwa, obraz obrazy);
void pokazObrazy(obraz *obrazy, int iteracja);
obraz *odejmObraz(obraz *obrazy, int iteracja);
void wybierzObraz(obraz *obrazy, int iteracja);
void progowanie(obraz *obrazy, int iteracja);
void negatyw(obraz *obrazy, int iteracja);
void pieprzSol(obraz *obrazy, int iteracja);
void sortowanieMaski(int **maska);
void filtrMedianowy(obraz *obrazy, int iteracja);
void histogram(obraz *obrazy, int iteracja);
void zapiszHistogram(int *hist, obraz *obrazy, int iteracja);
int znajdzMax(int *hist, obraz *obrazy, int iteracja);
void wyrysujHistogrem(obraz *obrazy, int iteracja, int max, int *hist);
void odbijOs(obraz *obrazy, int iteracja);
int sredniaWazona(int **maska, int **probka);
void filtrGausa(obraz *obrazy, int iteracja);
void splot(obraz *obrazy, int iteracja);
void obrot(obraz *obrazy, int iteracja);