#include "biblioteka.h"

void wypiszMenu() {
	printf("\n**********************************\n");
	printf("\t1. DODAJ KURS\n");
	printf("\t2. DODAJ/ZMIEN DATE\n");
	printf("\t3. POSEGREGUJ\n");
	printf("\t4. ZAPISZ PLAN\n");
	printf("\t5. ZMIEN STATUS KURSU\n");
	printf("\t6. USUN WYBRANY KURS\n");
	printf("\t7. WYLICZ SREDNIA NA SEMESTR\n");
	printf("\t8. WYCZYSC PLAN\n");
	printf("\t9. WYJDZ Z PROGRAMU\n");
	printf("\t10. WYSZUKAJ PRZEDZIALEM DAT\n");
	printf("**********************************\n");
}

int scanInt()
{
	int number;
	while (1)
	{
		if (!scanf("%d", &number))
		{
			while ('\n' != getchar());
			printf("Z£Y FORMAT - SPROBUJ PONOWNIE\n ");
		}
		else return number;
	}
}

float scanFloat()
{
	float number;
	while (1)
	{
		if (!scanf("%f", &number))
		{
			while ('\n' != getchar());
			printf("Z£Y FORMAT - SPROBUJ PONOWNIE\n ");
		}
		else return number;
	}
}

int sprawdzUtworzenie() {
	FILE *plik;
	int sprawdz=0;
	plik = fopen("terminy_sesja.csv", "r");
	if (plik!=NULL)
	{
		fclose(plik);
		sprawdz = 1;
	}
	return sprawdz;
}

/*kurs *wyszukaj(kurs **seed) {
	kurs *zmienna;
	int numer,i=0;
	printf("podaj numer kursu z listy powyzej\n");
	numer = scanInt();

	while (numer<1||numer>liczDlugosc(seed))
	{
		printf("wartosc spoza zakresu, sprobuj ponownie:\t");
		numer = scanInt();
	}

	while (i!=numer)
	{
		(*seed) = (*seed)->nastepny;
		i++;
	}

	zmienna = (*seed);

	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}
	return zmienna;
}*/

int pokazDynamicznie(kurs **seed) {
	char temp, *buffor = calloc(100, sizeof(char));
	int count = 0;
	int number=-1, i = 0;
	int check=0;


	do
	{
		temp = getch();
		if (temp == 8)
		{
			if (count > 0)
			{
				count--;
				buffor[count] = '\0';
			}

		}
		else
		{
			*(buffor + count) = temp;
		};
		//miejsce na magie
		if (count<2)
		{
			if (isdigit(buffor[0])!=0&&buffor!=NULL)
			{
				sscanf(buffor, "%d", &number);

				if (number>0 && number<liczDlugosc(seed) + 1)
				{
					while (i != number)
					{
						(*seed) = (*seed)->nastepny;
						i++;
					}
					if (count>0)
					{
						if (isdigit(buffor[count]) == 0) {

							buffor[count] = '\0';
							count--;
						}
					}
					if (check > 0)
					{
						printf("\rwpisane wyrazenie:%s\t%d. - %s                                     ", buffor, i, (*seed)->nazwa_kursu);
					}
					else
					{
						printf("wpisane wyrazenie:%s\t%d. - %s                                       ",buffor, i, (*seed)->nazwa_kursu);
					}

					while ((*seed)->poprzedni != NULL)
					{
						(*seed) = (*seed)->poprzedni;
					}
					check++;
					i = 0;
				}
				else
				{
					printf("\rwpisane wyrazenie:%s\tnie ma takiego kursu                        ",buffor);
				}
			}
		}else
		{
			buffor[count] = '\0';
			count--;
		}

		//miejsce na magie
		if (temp != 8)
		{
			count++;
		};

	} while (temp != 13);
	printf("\n");
	free(buffor);
	return number;
}

char *sprawdzDate() {
	int dzien, miesiac, rok;
	char *data = calloc(20, sizeof(char));
	printf("dzien: ");
	dzien = scanInt();
	while (dzien<1||dzien>31)
	{
		printf("\n blednie podany dzien podaj ponownie\t dzien: ");
		dzien = scanInt();
	}
	printf("\tmiesiac: ");
	miesiac = scanInt();
	while (miesiac<1||miesiac>12)
	{
		printf("\n blednie podany miesiac podaj ponownie\t miesiac: ");
	}
	printf("\trok: ");
	rok = scanInt();
	while (rok<2017)
	{
		printf("\n blednie podany rok podaj ponownie\t rok: ");
		rok = scanInt();
	}
	sprintf(data, "%d.%d.%d", dzien, miesiac, rok);
	
	return data;
}

char *sprawdzGodzine() {
	int godzina, minuta;
	char *godzinaa = calloc(10, sizeof(char));

	printf("\tgodzina: ");
	godzina = scanInt();
	while (godzina<0||godzina>23)
	{
		printf("\n blednie podana godzina podaj ponownie\t godzina: ");
		godzina = scanInt();
	}

	printf("\tminuta: ");
	minuta = scanInt();
	while (minuta<0||minuta>59)
	{
		printf("\n blednie podana minuta podaj ponownie\t minuta: ");
		minuta = scanInt();
	}
	sprintf(godzinaa, "%d:%d", godzina, minuta);
	return godzinaa;
}

float sprawdzOcene() {
	float ocena;
	printf("podaj ocene jaka dostales: ");
	ocena = scanFloat();
	while (ocena<3||ocena>=6)
	{
		printf("nie ma takej oceny - sprobuj ponownie\n");
		ocena = scanFloat();
	}
	return ocena;
}

kurs *wyszukaj(kurs **seed) {
	kurs *zmienna;
	int numer, i = 0;
	printf("podaj numer kursu z listy powyzej\n");
	numer = pokazDynamicznie(seed);

	while (numer==-1)
	{
		printf("blad wybrania kursu");
		numer = pokazDynamicznie(seed);
	}

	while (i != numer)
	{
		(*seed) = (*seed)->nastepny;
		i++;
	}

	zmienna = (*seed);

	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}
	return zmienna;
}