#include "biblioteka.h"

void utworzBaze() {
	FILE *plik;
	if (sprawdzUtworzenie()==0)
	{
		plik = fopen("terminy_sesja.csv", "w");
		fprintf(plik, "Subject;Start Date;Start Time;End Date;End Time;All Day Event;Description;Location;Private\n");
		fclose(plik);
	}
}

void dodajRecznie(kurs **seed) {
	kurs *contact = calloc(1, sizeof(kurs));
	kurs *temp;
	zbierzDane(contact);
	if (((*seed)->nastepny == NULL) && ((*seed)->poprzedni == NULL)) {
		contact->poprzedni = *seed;
		(*seed)->nastepny = contact;
		contact->nastepny = NULL;
	}
	else
	{
		temp = (*seed)->nastepny;
		temp->poprzedni = contact;
		contact->nastepny = temp;
		contact->poprzedni = (*seed);
		(*seed)->nastepny = contact;
	}
}

void zbierzDane(kurs *contact) {
	contact ->miejsce = calloc(20, sizeof(char));
	contact ->nazwa_kursu = calloc(40, sizeof(char));
	contact ->prowadzacy = calloc(30, sizeof(char));
	contact ->status = calloc(20, sizeof(char));
	
	while ('\n' != getchar());
	printf("podaj: nazwa kursu\n");
	scanf("%[^\n]s", contact->nazwa_kursu);
	scanf("%*c");
	printf("podaj: data\n");
	contact->data = sprawdzDate();
	while ('\n' != getchar());
	printf("podaj: godzina\n");
	contact->godzina = sprawdzGodzine();
	while ('\n' != getchar());
	printf("podaj: punkty ECTS\n");
	contact->ects = scanInt();
	while (contact->ects<1)
	{
		printf("nie prawidlowa ilosc punktow ects\n");
		contact->ects = scanInt();
	}
	while ('\n' != getchar());
	printf("podaj: miejsce\n");
	scanf("%[^\n]s", contact->miejsce);
	scanf("%*c");
	printf("podaj: prowadzacy\n");
	scanf("%[^\n]s", contact->prowadzacy);
	scanf("%*c");
	contact->ocena = 0;
	strcpy(contact->status, "W TRAKCIE");
}

void pokazKursy(kurs **seed) {
	int i = 0;
	while ((*seed)->nastepny != NULL)
	{
		i++;
		(*seed) = (*seed)->nastepny;
		printf("%d. nazwa kursu: %s \t data: %s \t godzina: %s \t ECTS: %d \t ocena: %f \t status: %s \t miejsce: %s \t prowadzacy: %s \n\n", i, (*seed)->nazwa_kursu, (*seed)->data, (*seed)->godzina, (*seed)->ects, (*seed)->ocena, (*seed)->status, (*seed)->miejsce, (*seed)->prowadzacy);
	}
	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}
}

void wyczysc(kurs **seed) {

	while ((*seed)->nastepny != NULL)
	{
		(*seed) = (*seed)->nastepny;
		free((*seed)->poprzedni);
		free((*seed)->data);
		free((*seed)->miejsce);
		free((*seed)->nazwa_kursu);
		free((*seed)->prowadzacy);
		free((*seed)->status);
		free((*seed)->godzina);
	}
	free((*seed));
}

void wyczyscBezZakonczenia(kurs **seed) {

	while ((*seed)->nastepny != NULL)
	{
		(*seed) = (*seed)->nastepny;
		free((*seed)->poprzedni);
		free((*seed)->data);
		free((*seed)->miejsce);
		free((*seed)->nazwa_kursu);
		free((*seed)->prowadzacy);
		free((*seed)->status);
		free((*seed)->godzina);
	}

}

void wczytajPlan(kurs **zarodek){
	FILE *plik;
	char *smiec = calloc(300, sizeof(char));
	plik = fopen("terminy_sesja.csv", "r");
	fscanf(plik, "%[^\n]s", smiec);
	fscanf(plik, "\n");
	while (fgetc(plik) != EOF)
	{
		fseek(plik, -1, SEEK_CUR);
		wczytajZPliku(zarodek, plik);
	}
	fclose(plik);
	free(smiec);
}

void wczytajZPliku(kurs **seed, FILE *file) {
	kurs *contact = calloc(1, sizeof(kurs));
	kurs *temp;
	char *smiec = calloc(300, sizeof(char));
	contact->data = calloc(20, sizeof(char));
	contact->miejsce = calloc(20, sizeof(char));
	contact->nazwa_kursu = calloc(40, sizeof(char));
	contact->prowadzacy = calloc(30, sizeof(char));
	contact->status = calloc(20, sizeof(char));
	contact->godzina = calloc(20, sizeof(char));


	fscanf(file, "%[^;]s", contact->nazwa_kursu);
	fscanf(file, ";");
	fscanf(file, "%[^;]s", contact->data);
	fscanf(file, ";");
	fscanf(file, "%[^;]s", contact->godzina);
	fscanf(file, ";");

	fscanf(file, "%*s;%*s;%*s;");

	//description
	fscanf(file, "%[^/]s", contact->status);
	fscanf(file, "/");
	fscanf(file, "%[^/]s", contact->prowadzacy);
	fscanf(file, "/");
	fscanf(file, "%f", &contact->ocena);
	fscanf(file, "/");
	fscanf(file, "%d", &contact->ects);
	fscanf(file, ";");
	//location
	fscanf(file, "%[^;]s", contact->miejsce);
	fscanf(file, "%[^\n]s", smiec);
	fscanf(file, "\n");

	if (((*seed)->nastepny == NULL) && ((*seed)->poprzedni == NULL)) {
		contact->poprzedni = *seed;
		(*seed)->nastepny = contact;
		contact->nastepny = NULL;
	}
	else
	{
		temp = (*seed)->nastepny;
		temp->poprzedni = contact;
		contact->nastepny = temp;
		contact->poprzedni = (*seed);
		(*seed)->nastepny = contact;
	}
	free(smiec);
}

void segregujKursy(kurs **seed) {
	int option = 0;
	int check = 0;
	int end = 0;
	int size = liczDlugosc(seed), i;
	char first;
	kurs *temp = (*seed)->nastepny;
	kurs *temp1 = NULL, *temp2 = NULL;
	kurs *fromseed = (*seed)->nastepny;

	if ((*seed)->nastepny != NULL)
	{
		temp = temp->nastepny;

		for (i = 0; i < size; i++)
		{
			if (i != 0) {
				temp = (*seed)->nastepny;
				temp = temp->nastepny;
				fromseed = (*seed)->nastepny;
			}

			while ((temp != NULL) && (end != 1))
			{

				if (strcoll(fromseed->nazwa_kursu, temp->nazwa_kursu)>0)
				{
					if (temp->nastepny != NULL)
					{
						check = 1;
						temp1 = temp->nastepny;
						temp2 = fromseed->poprzedni;
						//first pair
						temp2->nastepny = temp;
						temp->poprzedni = temp2;
						//second pair
						temp->nastepny = fromseed;
						fromseed->poprzedni = temp;
						//third pair
						fromseed->nastepny = temp1;
						temp1->poprzedni = fromseed;
					}
					else
					{
						end = 1;
						temp1 = temp->nastepny;
						temp2 = fromseed->poprzedni;
						//first pair
						temp2->nastepny = temp;
						temp->poprzedni = temp2;
						//second pair
						temp->nastepny = fromseed;
						fromseed->poprzedni = temp;
						//third pair
						fromseed->nastepny = temp1;
					}
				}

				if (check == 0)
				{
					temp = temp->nastepny;
					fromseed = fromseed->nastepny;
				}
				else
				{
					temp = temp1;
				}

				check = 0;
			}
		}

	}
	else
	{
		printf("NOT ENOUGH CONTACTS TO EXECUTE\n");
	}
}

int liczDlugosc(kurs **seed) {
	int i = 0;
	while ((*seed)->nastepny != NULL)
	{
		(*seed) = (*seed)->nastepny;
		i++;
	}
	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}
	return i;
}

void segregujEcts(kurs **seed) {
	int option = 0;
	int check = 0;
	int end = 0;
	int size = liczDlugosc(seed), i;
	char first;
	kurs *temp = (*seed)->nastepny;
	kurs *temp1 = NULL, *temp2 = NULL;
	kurs *fromseed = (*seed)->nastepny;

	if ((*seed)->nastepny != NULL)
	{
		temp = temp->nastepny;

		for (i = 0; i < size; i++)
		{
			if (i != 0) {
				temp = (*seed)->nastepny;
				temp = temp->nastepny;
				fromseed = (*seed)->nastepny;
			}

			while ((temp != NULL) && (end != 1))
			{

				if (fromseed->ects < temp->ects)
				{
					if (temp->nastepny != NULL)
					{
						check = 1;
						temp1 = temp->nastepny;
						temp2 = fromseed->poprzedni;
						//first pair
						temp2->nastepny = temp;
						temp->poprzedni = temp2;
						//second pair
						temp->nastepny = fromseed;
						fromseed->poprzedni = temp;
						//third pair
						fromseed->nastepny = temp1;
						temp1->poprzedni = fromseed;
					}
					else
					{
						end = 1;
						temp1 = temp->nastepny;
						temp2 = fromseed->poprzedni;
						//first pair
						temp2->nastepny = temp;
						temp->poprzedni = temp2;
						//second pair
						temp->nastepny = fromseed;
						fromseed->poprzedni = temp;
						//third pair
						fromseed->nastepny = temp1;
					}
				}

				if (check == 0)
				{
					temp = temp->nastepny;
					fromseed = fromseed->nastepny;
				}
				else
				{
					temp = temp1;
				}

				check = 0;
			}
		}

	}
	else
	{
		printf("NOT ENOUGH CONTACTS TO EXECUTE\n");
	}
}

void zapiszPlan(kurs **seed) {
	FILE *plik = fopen("terminy_sesja.csv", "w");
	fprintf(plik, "Subject;Start Date;Start Time;End Date;End Time;All Day Event;Description;Location;Private\n");

	while ((*seed)->nastepny != NULL)
	{
		(*seed) = (*seed)->nastepny;
		fprintf(plik, "%s;%s;%s;%s;%s;False;%s/%s/%f/%d;%s;False\n", (*seed)->nazwa_kursu, (*seed)->data, (*seed)->godzina, (*seed)->data, (*seed)->godzina, (*seed)->status, (*seed)->prowadzacy, (*seed)->ocena, (*seed)->ects, (*seed)->miejsce);
	}
	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}


	fclose(plik);
}

void wyczyscPlan(kurs **seed) {
	FILE *plik = fopen("terminy_sesja.csv", "w");
	wyczyscBezZakonczenia(seed);
	fprintf(plik, "Subject;Start Date;Start Time;End Date;End Time;All Day Event;Description;Location;Private\n");
	fclose(plik);
}

void wyrzucWybrany(kurs **seed) {
	kurs *wybrany,*w_nastepny,*w_poprzedni;

	wybrany = wyszukaj(seed);

	if (wybrany->nastepny != NULL && wybrany->poprzedni!=NULL)
	{
		w_nastepny = wybrany->nastepny;
		w_poprzedni = wybrany->poprzedni;

		w_poprzedni->nastepny = w_nastepny;
		w_nastepny->poprzedni = w_poprzedni;
	}
	if (wybrany->nastepny == NULL)
	{
		w_poprzedni = wybrany->poprzedni;

		w_poprzedni->nastepny = NULL;
	}
	if (wybrany->poprzedni == NULL)
	{
		w_nastepny = wybrany->nastepny;

		w_nastepny->poprzedni = NULL;
	}

	free(wybrany->data);
	free(wybrany->miejsce);
	free(wybrany->nazwa_kursu);
	free(wybrany->prowadzacy);
	free(wybrany->status);
	free(wybrany->godzina);
	free(wybrany);
}

void zmienStatus(kurs **seed) {
	kurs *wybrane = wyszukaj(seed);
	int wybierz,koniec=0;
	printf("\n1 -> W TRAKCIE\t2 -> UWALONE\t3 -> ZDANE\n");
	wybierz = scanInt();
	while (koniec!=1)
	{
		switch (wybierz)
		{
		case 1:
			koniec = 1;
			strcpy(wybrane->status, "W TRAKCIE");
			break;
		case 2:
			koniec = 1;
			strcpy(wybrane->status, "UWALONE");
			wybrane->ocena = 2;
			break;
		case 3:
			koniec = 1;
			strcpy(wybrane->status, "ZDANE");
			wybrane->ocena = sprawdzOcene();
			break;
		default:
			printf("bledna opcja sprobuj ponownie\n");
			break;
		}
	}
}

void zmienDate(kurs **seed) {
	kurs *wybrane = wyszukaj(seed);
	if (wybrane->data != NULL)
	{
		free(wybrane->data);
	}

	wybrane->data = sprawdzDate();
}

int porownajDaty(kurs *pierwszy,kurs *drugi){
	char *data_1 = pierwszy->data, *data_2 = drugi->data;
	int dzien_1, miesiac_1, rok_1;
	int dzien_2, miesiac_2, rok_2;
	int porownanie = 0;
	//jesli pierwszy wczesniej od drugiego to porownanie == 0, jak daty rowne to tez
	sscanf(data_1, "%d.%d.%d",&dzien_1,&miesiac_1,&rok_1);
	sscanf(data_2, "%d.%d.%d", &dzien_2, &miesiac_2, &rok_2);
	if (rok_2<rok_1)
	{
		porownanie = 1;
	}
	if ((rok_1==rok_2)&&(miesiac_2<miesiac_1))
	{
		porownanie = 1;
	}
	if ((rok_1 == rok_2) && (miesiac_2==miesiac_1) && (dzien_2<dzien_1))
	{
		porownanie = 1;
	}
	return porownanie;
}

int porownajDatyProjekt(kurs *pierwszy, char *data_2) {
	char *data_1 = pierwszy->data;
	int dzien_1, miesiac_1, rok_1;
	int dzien_2, miesiac_2, rok_2;
	int porownanie = 0;
	//jesli pierwszy wczesniej od drugiego to porownanie == 0, jak daty rowne to tez
	sscanf(data_1, "%d.%d.%d", &dzien_1, &miesiac_1, &rok_1);
	sscanf(data_2, "%d.%d.%d", &dzien_2, &miesiac_2, &rok_2);
	if (rok_2<rok_1)
	{
		porownanie = 1;
	}
	if ((rok_1 == rok_2) && (miesiac_2<miesiac_1))
	{
		porownanie = 1;
	}
	if ((rok_1 == rok_2) && (miesiac_2 == miesiac_1) && (dzien_2<dzien_1))
	{
		porownanie = 1;
	}

	return porownanie;
}

void segregujDaty(kurs **seed) {
	int option = 0;
	int check = 0;
	int end = 0;
	int size = liczDlugosc(seed), i;
	char first;
	kurs *temp = (*seed)->nastepny;
	kurs *temp1 = NULL, *temp2 = NULL;
	kurs *fromseed = (*seed)->nastepny;

	if ((*seed)->nastepny != NULL)
	{
		temp = temp->nastepny;

		for (i = 0; i < size; i++)
		{
			if (i != 0) {
				temp = (*seed)->nastepny;
				temp = temp->nastepny;
				fromseed = (*seed)->nastepny;
			}

			while ((temp != NULL) && (end != 1))
			{
				
				if (porownajDaty(fromseed, temp)==1)
				{
					if (temp->nastepny != NULL)
					{
						check = 1;
						temp1 = temp->nastepny;
						temp2 = fromseed->poprzedni;
						//first pair
						temp2->nastepny = temp;
						temp->poprzedni = temp2;
						//second pair
						temp->nastepny = fromseed;
						fromseed->poprzedni = temp;
						//third pair
						fromseed->nastepny = temp1;
						temp1->poprzedni = fromseed;
					}
					else
					{
						end = 1;
						temp1 = temp->nastepny;
						temp2 = fromseed->poprzedni;
						//first pair
						temp2->nastepny = temp;
						temp->poprzedni = temp2;
						//second pair
						temp->nastepny = fromseed;
						fromseed->poprzedni = temp;
						//third pair
						fromseed->nastepny = temp1;
					}
				}

				if (check == 0)
				{
					temp = temp->nastepny;
					fromseed = fromseed->nastepny;
				}
				else
				{
					temp = temp1;
				}

				check = 0;
			}
		}

	}
	else
	{
		printf("NOT ENOUGH CONTACTS TO EXECUTE\n");
	}
}

void liczSrednia(kurs **seed) {
	float srednia,licznik=0,ocena;
	int suma_ects=0,ects;

	while ((*seed)->nastepny != NULL)
	{
		(*seed) = (*seed)->nastepny;
		ocena = (*seed)->ocena;
		if (ocena == 2)
		{
			ocena = 0;
		}
		ects = (*seed)->ects;
		licznik = licznik+ocena*ects;
		suma_ects = suma_ects + ects;
	}
	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}

	if (suma_ects!=0)
	{
		srednia = licznik / suma_ects;
		printf("***TWOJA ŒREDNIA W SEMESTRZE WYNOSI:\t%f ***\n", srednia);
	}
	else
	{
		printf("BLAD LICZENIA SREDNIEJ - ZEROWA ILOSC PUNTOW ECTS");
	}
	
} 

void szukajDat(kurs **seed) {
	char *data_1, *data_2;
	int i = 0;
	printf("podaj date poczatkowa:\t");
	data_1 = sprawdzDate();
	
	printf("podaj date koncowa:\t");
	data_2 = sprawdzDate();
	printf("\n**************************\n");
	while ((*seed)->nastepny != NULL)
	{
		(*seed) = (*seed)->nastepny;
		i++;
		if (porownajDatyProjekt((*seed),data_1)==1&&porownajDatyProjekt((*seed),data_2)==0)
		{
			printf("%d. nazwa kursu: %s \t data: %s \t godzina: %s \t ECTS: %d \t ocena: %f \t status: %s \t miejsce: %s \t prowadzacy: %s \n\n", i, (*seed)->nazwa_kursu, (*seed)->data, (*seed)->godzina, (*seed)->ects, (*seed)->ocena, (*seed)->status, (*seed)->miejsce, (*seed)->prowadzacy);
		}
	}
	while ((*seed)->poprzedni != NULL)
	{
		(*seed) = (*seed)->poprzedni;
	}
	printf("**************************\n");
}