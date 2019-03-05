#include "naglowek.h"

void menu(obraz *obrazy) {
	int wyraz;
	int iteracja=0;
	printf("WPROWADZ LICZBE CALKOWITA ZEBY UZYWAC MENU\n");
	while (1)
	{
		printf("*******************MENU********************\n");
		printf("1 - DODEJ OBRAZ\n");
		printf("2 - WYSWIOTL DOSTYPNE UOBRAZY\n");
		printf("3 - ZAPYSZ OBREZ\n");
		printf("4 - ODEJM OBRAZ\n");
		printf("5 - WYBIRZ OBRUZ\n");
		printf("6 - PROGOWENIE\n");
		printf("7 - NEGETYW\n");
		printf("8 - PIUPRZ UND SOLE\n");
		printf("9 - FLIRT MEDIJANOWY\n");
		printf("10 - HISTOGREM\n");
		printf("11 - LUSTRZANE ODBICIE\n");
		printf("12 - FYLTR GAUSA\n");
		printf("13 - SPLOT 3 NA 3\n");
		printf("*******************MENU********************\n");

		wyswietlNazwe(obrazy,iteracja);
		pokazObrazy(obrazy, iteracja);
		wyraz = skanInt();
		switch (wyraz)
		{
		case 1:
			iteracja++;
			obrazy = dodejObraz(obrazy, iteracja);
			break;
		case 2:
			break;
		case 3:
			zapyszObraz(obrazy, iteracja);
			break;
		case 4:
			if (1 > iteracja) {
				system("cls");
				printf("NIE MASZ CZEGO ODJAC\n");
				break;
			}
			iteracja--;
			obrazy = odejmObraz(obrazy, iteracja);
			break;
		case 6:
			wybierzObraz(obrazy, iteracja);
			break;
		case 7:
			if (iteracja > 0) {
				progowanie(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 8:
			if (iteracja > 0) {
				negatyw(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 9:
			if (iteracja > 0) {
				pieprzSol(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 10:
			if (iteracja > 0) {
				filtrMedianowy(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 11:
			if (iteracja > 0) {
				histogram(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 12:
			if (iteracja > 0) {
				odbijOs(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 13:
			if (iteracja > 0) {
				filtrGausa(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;
		case 14:
			if (iteracja > 0) {
				splot(obrazy, iteracja);
			}
			else {
				printf("KAJ TY KCESZ TO ZROBIC???\n");
			}
			break;

		default:
			system("cls");
			printf("NIE MA TAKIEJ OPCJI W MENU SPROBUJ PONOWNIE\n");
			break;
		}
	}

}

obraz *dodejObraz(obraz *obrazy,int iteracja) {
	FILE *plik;
	int i,j;
	obrazy = realloc(obrazy, sizeof(obraz)*(iteracja));
	obrazy[iteracja-1].nazwa = sprawdzNazwe(obrazy[iteracja-1].nazwa);
	plik = fopen(obrazy[iteracja-1].nazwa, "r");
	fscanf(plik,"%*c%*d\n");
	znejdzKomyntorz(obrazy, plik);
	fscanf(plik, "%d %d\n", &obrazy[iteracja-1].szerokosc, &obrazy[iteracja-1].wysokosc);
	znejdzKomyntorz(obrazy, plik);
	fscanf(plik, "%d\n", &obrazy[iteracja-1].skala);
	znejdzKomyntorz(obrazy, plik);
	obrazy[iteracja-1].dane = malloc(obrazy[iteracja-1].wysokosc * sizeof(int*));
	for ( i = 0; i < obrazy[iteracja-1].wysokosc; i++)
	{
		obrazy[iteracja-1].dane[i] = malloc(obrazy[iteracja-1].szerokosc * sizeof(int));
	}
	for (i = 0; i < obrazy[iteracja-1].wysokosc; i++) {

		for ( j = 0; j <obrazy[iteracja-1].szerokosc; j++)
		{
			fscanf(plik, "%d", &obrazy[iteracja-1].dane[i][j]);
		}
		znejdzKomyntorz(obrazy, plik);
		fscanf(plik, "\n");
		znejdzKomyntorz(obrazy, plik);
	}

	fclose(plik);
	return obrazy;
}

void pokazObrazy(obraz *obrazy, int iteracja) {
	int i;
	if (iteracja == 0) {
		printf("BRAK WCZYTANYCH OBRAZOW\n");
	}
	else
	{
		for ( i = 0; i < iteracja; i++)
		{
			printf("%d.\t%s\n",i+1,obrazy[i].nazwa);
		}
	}

}

obraz *odejmObraz(obraz *obrazy, int iteracja) {
	obraz temp;
	printf("WYBIRZ KTORY OBREZ CHCYSZ WYHUŒTAÆ\n");
	int odejm = skanInt();
	while ((odejm < 1) || (odejm > iteracja+1)) {
		printf("NIEPOPRAWNA DANA, SPROBEJ PONOWNIJ\n");
		odejm = skanInt();
	}
	if (iteracja != 0) {
		temp = obrazy[iteracja];
		obrazy[iteracja] = obrazy[odejm - 1];
		obrazy[odejm - 1] = temp;
	}

	obrazy = realloc(obrazy, sizeof(obraz)*iteracja);
	return obrazy;
}

void wyswietlNazwe(obraz *obrazy, int iteracja) {
	printf("obecny plik:\t");
	if (obrazy == NULL)printf("brak\n"); else
	{
		printf("%s\n", obrazy[iteracja-1].nazwa);
	}
}

void zapyszObraz(obraz *obrazy, int iteracja) {
	//obraz zapisz = {0,0,0,NULL,NULL};
	char *nazwa = NULL;

	int temp = iteracja;
	if (obrazy == NULL) {
		printf("NIE MASZ CZEGO ZAPISAC");
	}
	else
	{
		nazwa = nadajNazwe(nazwa);
		przepiszObraz(nazwa, obrazy[temp-1]);

	}
}

/*void zakoncz(obraz *obrazy, int iteracja) {
	int i,w;
	int temp = iteracja;
	if (temp == 0)exit(1);

	for ( i = 0; i < temp; i++)
	{
		for ( w = 0; w < obrazy[i].wysokosc; w++)
		{
			free(obrazy[i].dane[w]);
		}
		free(obrazy[i].dane);
		free(obrazy[i].nazwa);
	}
	exit(1);
}*/

void przepiszDane(obraz zapisz, obraz obrazy) {
	int i,j;
	zapisz.dane = calloc(obrazy.wysokosc, sizeof(int*));
	for ( i = 0; i < obrazy.wysokosc; i++)
	{
		zapisz.dane[i] = calloc(obrazy.szerokosc, sizeof(int));
	}
	for ( i = 0; i < obrazy.wysokosc; i++)
	{
		for (j = 0; j < obrazy.szerokosc; j++) {
			zapisz.dane[i][j] = obrazy.dane[i][j];
		}
	}
}

void przepiszObraz(char *nazwa, obraz obrazy) {
	FILE *plik;
	int i, j;
	plik = fopen(nazwa, "w");
	fprintf(plik, "%c%d\n", 'P', 2);
	fprintf(plik, "%d %d\n", obrazy.szerokosc, obrazy.wysokosc);
	fprintf(plik, "%d\n", obrazy.skala);

	for ( i = 0; i < obrazy.wysokosc; i++)
	{
		for (j = 0; j < obrazy.szerokosc; j++) {
			fprintf(plik, "%d ", obrazy.dane[i][j]);
		}
		fprintf(plik, "\n");
	}

	fclose(plik);
}


void wybierzObraz(obraz *obrazy, int iteracja) {
	int temp;
	obraz t;
	if (iteracja == 0) {
		printf("NIE MASZ CZEGO WYBRAC");
		
	}else{
	printf("wybierz obraz z listy na ktorym chcesz pracowac\n");
	temp = skanInt();
	if ((temp > iteracja) || (temp < 1)) {
		printf("NE MA TAKIEGO OBRAZU\n");
	}
	else
	{
		t = obrazy[iteracja - 1];
		obrazy[iteracja - 1] = obrazy[temp - 1];
		obrazy[temp - 1] = t;
	}
	}
}

void progowanie(obraz *obrazy, int iteracja) {
	int i,j;
	int prog;
	printf("wybierz prog - liczba calkowita od 0 do %d\n", obrazy[iteracja - 1].skala);
	prog = skanInt();
	while ((prog < 0) || (prog > obrazy[iteracja - 1].skala)) {
		printf("NIE POPROWNO WORTOSC - WRYCHTUJ PONOWNI\t");
		prog = skanInt();
	}
	for (i = 0; i < obrazy[iteracja - 1].wysokosc; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].szerokosc; j++) {
			if (obrazy[iteracja - 1].dane[i][j] < prog) {
				obrazy[iteracja - 1].dane[i][j] = 0;
			}
		}
	}
}

void negatyw(obraz *obrazy, int iteracja) {
	int i, j;
	int *temp;
	temp = malloc(sizeof(int)*obrazy[iteracja - 1].szerokosc);

	for (i = 0; i < obrazy[iteracja - 1].wysokosc; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].szerokosc; j++) 
			{
				temp[j] = obrazy[iteracja - 1].dane[i][j];
			}

		for (j = 0; j < obrazy[iteracja - 1].szerokosc; j++) {
			if (j != obrazy[iteracja - 1].szerokosc) {
				obrazy[iteracja - 1].dane[i][j + 1] = obrazy[iteracja - 1].skala - temp[j];
			}
		}
	}
}

void pieprzSol(obraz *obrazy, int iteracja) {
	int los;
	int lotto;
	int i, j;

	for (i = 0; i < obrazy[iteracja - 1].wysokosc; i++)
	{
		los = rand() % obrazy[iteracja - 1].skala;
		los = (int)round(los / 3);
		if (los == 0)los = 1;
		for (j = 0; j < obrazy[iteracja - 1].szerokosc; j++) {
			if (j%los==0) {
				lotto = rand();
				if(lotto%2 == 0){
				obrazy[iteracja - 1].dane[i][j] = 0;
				}else{ obrazy[iteracja - 1].dane[i][j] = obrazy[iteracja - 1].skala; }
			}
		}
	}
}

void filtrMedianowy(obraz *obrazy, int iteracja) {
	int **maska;
	int i, j, k, l;

	maska = malloc(sizeof(int*) * 3);
	for ( i = 0; i < 3; i++)
	{
		maska[i] = malloc(sizeof(int) * 3);
	}

	for ( i = 0; i < obrazy[iteracja-1].wysokosc-3; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].szerokosc-3; j++) {
			for ( k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					maska[k][l] = obrazy[iteracja - 1].dane[i+k][j+l];
				}
			}
			sortowanieMaski(maska);
			obrazy[iteracja - 1].dane[i+1][j+1] = maska[1][1];
		}
	}

}

void sortowanieMaski(int **maska) {
	int k,l,j;
	int temp;
	for (k = 0; k < 3; k++)
	{
		for (j = 0; j < 1; j++) {
			for (l = 0; l < 2; l++)
			{

				if (maska[k][l] > maska[k][l + 1]) {
					temp = maska[k][l];
					maska[k][l] = maska[k][l + 1];
					maska[k][l + 1] = temp;
				}
			}
		}
	}
	if (maska[0][1] > maska[1][1]) {
		temp = maska[0][1];
		maska[0][1] = maska[1][1];
		maska[1][1] = temp;
	}
	if (maska[1][1] > maska[2][1]) {
		temp = maska[1][1];
		maska[1][1] = maska[2][1];
		maska[2][1] = temp;
	}
	if (maska[0][1] > maska[1][1]) {
		temp = maska[0][1];
		maska[0][1] = maska[1][1];
		maska[1][1] = temp;
	}

}

//sprawdzaj czy wartosci pixeli miesci sie w skali szarosci

void histogram(obraz *obrazy, int iteracja) {
	int *hist;
	int i, j;
	int max;
	hist = calloc((obrazy[iteracja - 1].skala + 1),sizeof(int));
	for ( i = 0; i < obrazy[iteracja - 1].wysokosc; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].szerokosc; j++) {
			if ((obrazy[iteracja - 1].dane[i][j]<0)||(obrazy[iteracja - 1].dane[i][j]>obrazy[iteracja - 1].skala)) {
				printf("OJOJOJ COS TU NIE GRA CHYBA KTOS TU SZKALE SZAROSCI PRZEKROCZYL!!!/n");
			}
			else {
				hist[obrazy[iteracja - 1].dane[i][j]]++;
			}
		}
	}
	zapiszHistogram(hist, obrazy, iteracja);
	max = znajdzMax(hist, obrazy, iteracja);
	wyrysujHistogrem(obrazy, iteracja, max, hist);
	free(hist);
}

void zapiszHistogram(int *hist,obraz *obrazy,int iteracja) {
	FILE *plik;
	int i;
	plik = fopen("histogram.csv", "w");

	for ( i = 0; i < obrazy[iteracja-1].skala + 1; i++)
	{
		fprintf(plik, "%d;%d\n",i,hist[i]);
	}

	fclose(plik);
}

int znajdzMax(int *hist, obraz *obrazy, int iteracja) {
	int i;
	int temp;
	int *histi;
	histi = malloc(sizeof(int)*(obrazy[iteracja - 1].skala + 1));
	for (i = 0; i < (obrazy[iteracja - 1].skala+1); i++)
	{
		histi[i] = hist[i];
	}
	for ( i = 0; i <( obrazy[iteracja - 1].skala); i++)
	{
		if (histi[i] > histi[i + 1]) {
			temp = histi[i];
			histi[i] = histi[i + 1];
			histi[i + 1] = temp;
		}
	}
	return histi[obrazy[iteracja - 1].skala];
	free(histi);
}

void wyrysujHistogrem(obraz *obrazy, int iteracja, int max, int *hist) {
	FILE *plik;
	int i,j,l=0;
	int **histogram;
	histogram = calloc(max+1, sizeof(int*));
	for ( i = 0; i < max+1; i++)
	{
		histogram[i] = calloc((obrazy[iteracja - 1].skala + 1), sizeof(int));
	}
	i = 0;
		for (j = 0; j < obrazy[iteracja - 1].skala + 1; j++) {
			for ( l = 0; l < hist[j]; l++)
			{
				histogram[max - i][j] = 1;
				i++;
			}
			i = 0;
		}
		plik = fopen("histogram.pgm", "w");

		fprintf(plik, "%c%d\n", 'P', 2);
		fprintf(plik, "%d %d\n", obrazy[iteracja - 1].skala + 1, max);
		fprintf(plik, "%d\n", 2);

		for (i = 0; i < max; i++)
		{
			for (j = 0; j < obrazy[iteracja - 1].skala + 1; j++) {
				fprintf(plik, "%d ", histogram[i][j]);
			}
			fprintf(plik, "\n");
		}



	fclose(plik);

}

void odbijOs(obraz *obrazy, int iteracja) {
	int i, j;
	int temp;
	int szer = (int)round(obrazy[iteracja - 1].szerokosc/2);
	for ( i = 0; i < obrazy[iteracja-1].wysokosc; i++)
	{
		for (j = 0; j < szer; j++) {
			temp = obrazy[iteracja - 1].dane[i][j];
			obrazy[iteracja - 1].dane[i][j] = obrazy[iteracja - 1].dane[i][obrazy[iteracja - 1].szerokosc - j];
			obrazy[iteracja - 1].dane[i][obrazy[iteracja - 1].szerokosc - j] = temp;
		}
	}
}

void filtrGausa(obraz *obrazy, int iteracja) {
	int maska[3][3] = { { 1,2,1 }, { 2,4,2 }, { 1,2,1 } };
	int probka[3][3];
	int i, j,k,l;

	int b, z;
	int wynik[3][3];
	int suma = 0;
	int sumawag = 0;
	int srednia;

	for (i = 0; i < obrazy[iteracja - 1].wysokosc - 3; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].szerokosc - 3; j++) {
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					probka[k][l] = obrazy[iteracja - 1].dane[i + k][j + l];
				}
			}

			//KOPIA KODU
			for (b = 0; b < 3; b++)
			{
				for (z = 0; z < 3; z++) {
					wynik[b][z] = maska[b][z] * probka[b][z];
				}
			}
			for (b = 0; b < 3; b++)
			{
				for (z = 0; z < 3; z++) {
					suma = suma + wynik[b][z];
				}
			}
			for (b = 0; b < 3; b++)
			{
				for (z = 0; z < 3; z++) {
					sumawag = sumawag + maska[b][z];
				}
			}
			srednia = (int)round(suma / sumawag);
			//KOPIA KODU
			suma = 0;
			sumawag = 0;
			obrazy[iteracja - 1].dane[i + 1][j + 1] = srednia;
		}
	}
}

/*void splot(obraz *obrazy, int iteracja) {
	int maska[3][3];
	int probka[3][3];
	int i, j, k, l;
	int b, z;
	int wynik[3][3];
	int suma = 0;
	int sumawag = 0;
	int srednia;
	printf("podaj wspolczynniki maski wierszami od lewej do prawej (liczby calkowite)\n");
	for (b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			maska[b][z] = skanInt();
		}
	}
	for (b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			sumawag = sumawag + maska[b][z];
		}
	}
	while (sumawag == 0) {
		printf("suma wag nie moze byc rowna 0, sprobuj ponownie\n");
		for (b = 0; b < 3; b++)
		{
			for (z = 0; z < 3; z++) {
				maska[b][z] = skanInt();
			}
		}
		for (b = 0; b < 3; b++)
		{
			for (z = 0; z < 3; z++) {
				sumawag = sumawag + maska[b][z];
			}
		}
	}
	

	for (i = 0; i < obrazy[iteracja - 1].wysokosc - 3; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].szerokosc - 3; j++) {
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					probka[k][l] = obrazy[iteracja - 1].dane[i + k][j + l];
				}
			}

			//KOPIA KODU
			for (b = 0; b < 3; b++)
			{
				for (z = 0; z < 3; z++) {
					wynik[b][z] = maska[b][z] * probka[b][z];
				}
			}
			for (b = 0; b < 3; b++)
			{
				for (z = 0; z < 3; z++) {
					suma = suma + wynik[b][z];
				}
			}

			srednia = (int)round(suma / sumawag);
			//KOPIA KODU
			suma = 0;
			obrazy[iteracja - 1].dane[i + 1][j + 1] = srednia;
		}
	}
}*/

int sredniaWazona(int **maska, int **probka) {
	int b, z;
	int wynik[3][3];
	int suma=0;
	int sumawag = 0;
	int srednia;
	for ( b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			wynik[b][z] = maska[b][z] * probka[b][z];
		}
	}
	for (b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			suma = suma + wynik[b][z];
		}
	}
	for (b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			sumawag = sumawag + probka[b][z];
		}
	}
	srednia = (int)round(suma / sumawag);
	return srednia;
}

/*void obrot(obraz *obrazy, int iteracja) {
	int **nowe;
	int i,j;
	int temp;
	nowe = malloc(obrazy[iteracja - 1].szerokosc * sizeof(int*));
	for (i = 0; i < obrazy[iteracja - 1].szerokosc; i++) {
		nowe[i] = malloc(obrazy[iteracja - 1].wysokosc * sizeof(int));
	}
	for ( i = 0; i < obrazy[iteracja - 1].szerokosc; i++)
	{
		for (j = 0; j < obrazy[iteracja - 1].wysokosc; j++) {
			nowe[i][j] = obrazy[iteracja - 1].dane[obrazy[iteracja - 1].wysokosc -1- j][i];
		}
	}
	temp = obrazy[iteracja - 1].wysokosc;
	obrazy[iteracja - 1].wysokosc = obrazy[iteracja - 1].szerokosc;
	obrazy[iteracja - 1].szerokosc = temp;
	obrazy[iteracja - 1].dane = nowe;
	for ( i = 0; i < obrazy[iteracja - 1].szerokosc; i++)
	{
		free(obrazy[iteracja - 1].dane[i]);
	}
	free(obrazy[iteracja - 1].dane);
}*/

void splot(obraz *obrazy, int iteracja) {
	int b, z;
	int i, j;
	int probka[3][3];
	int maska[3][3];
	int suma = 0, srednia;
	int sumawag=0;
	int **wynik;
	int l = 0;
	wynik = calloc(obrazy[iteracja - 1].wysokosc, sizeof(int*));
	for (i = 0; i < obrazy[iteracja - 1].wysokosc; i++)
	{
		wynik[i] = calloc(obrazy[iteracja - 1].szerokosc, sizeof(int));
	}

	printf("podaj wspolczynniki maski wierszami od lewej do prawej (liczby calkowite)\n");
	for (b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			maska[b][z] = skanInt();
		}
	}

	for (b = 0; b < 3; b++)
	{
		for (z = 0; z < 3; z++) {
			sumawag = sumawag + maska[b][z];
		}
	}
	printf("suma wag: %d\n", sumawag);

	while (sumawag == 0) {
		printf("suma wag nie moze byc rowna 0, sprobuj ponownie\n");
		for (b = 0; b < 3; b++)
		{
			for (z = 0; z < 3; z++) {
				maska[b][z] = skanInt();
			}
		}
	}

		for (b = 0; b < obrazy[iteracja - 1].wysokosc - 2; b++)
		{
			for (z = 0; z < obrazy[iteracja - 1].szerokosc - 2; z++) {


				for (i = 0; i < 3; i++)//POBRANIE PROBKI	
				{
					for (j = 0; j < 3; j++) {
						probka[i][j] = obrazy[iteracja - 1].dane[i + b][j + z];
						probka[i][j] = probka[i][j] * maska[i][j];
					}
				}

				for (i = 0; i < 3; i++)
				{
					for (j = 0; j < 3; j++) {
						suma = suma + probka[i][j];
					}
				}

				srednia = suma / sumawag;
				suma = 0; //WYZEROWANIE WARTOSCI DLA NASTEPNEJ ITERACJ
				wynik[b + 1][z + 1] = srednia;

			}
		}
		printf("srednia: %d\n", srednia);
		for (b = 0; b < obrazy[iteracja - 1].wysokosc - 2; b++)//PRZEPSIANIE DANYCH
		{
			for (z = 0; z < obrazy[iteracja - 1].szerokosc - 2; z++) {

				obrazy[iteracja - 1].dane[b+1][z+1] = wynik[b + 1][z + 1] + 4;

			}
		}
	}
