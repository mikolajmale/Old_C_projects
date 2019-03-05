#include "naglowek.h"

int skanInt()
{
	int temp;
	while (1)
	{
		if (scanf("%d", &temp) == 1)
		{
			return temp;
		}
		printf("Bledny format, sprobuj ponownie:\t");
		scanf("%*s");
	}
}

char *sprawdzNazwe(char *nazwa) {
	FILE *plik;
	nazwa = malloc(sizeof(char) * 100);
	printf("podaj nazwe pliku zawierajacego sygnal wraz z .rozszerzenie\n");
	system("dir\n");
	scanf("%s", nazwa);

	while ((plik = fopen(nazwa, "r")) == NULL)
	{
		printf("taki plik nie istnieje, wprowadz ponownie nazwe z .rozszerzenie\n");
		scanf("%s", nazwa);
	}
	fclose(plik);
	return nazwa;
}

char *nadajNazwe(char *nazwa) {
	nazwa = calloc(100, sizeof(char));
	printf("podaj nazwe pliku:\t");
	scanf("%s", nazwa);
	strcat(nazwa, ".pgm");
	printf("%s\n", nazwa);
	return nazwa;
}

void znejdzKomyntorz(obraz *obrazy,FILE *plik) {
	if (fgetc(plik) == '#') {
		fscanf(plik,"%*s\n");
	}
	else
	{
		fseek(plik, -1, SEEK_CUR);
	}
}

