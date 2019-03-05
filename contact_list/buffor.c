#include "header.h"

void optionsPrint() {
	printf("\n\t\t CHOOSE RIGHT NUMBER TO EXECUTE\n");
	printf("0. EXIT PROGRAM\n");
	printf("1. LOAD CONTACTS\n");
	printf("2. SAVE CONTACTS\n");
	printf("3. ADD CONTACT\n");
	printf("4. REMOVE CONTACT\n");
	printf("5. SHOW MY CONTACTS\n");
	printf("6. SORT MY CONTACTS BY: GROUPS\n");
	printf("7. SORT MY CONTACTS BY: NAMES\n");
	printf("8. SORT MY CONTACTS BY: LAST NAMES\n");
	printf("9. SEARCH FOR CONTACT\n");
	printf("10. SHOW CONTACTS IN GIVEN GROUP\n");

}

int scanInt()
{
	int number;
	while (1)
	{
		if (!scanf("%d", &number))
		{
			while ('\n' != getchar());
			printf("TRY AGAIN - WRONG FORMAT\n ");
		}
		else return number;
	}
}

char *scanString()
{
	char *string = calloc(20,sizeof(char));
	while (1)
	{
		if (!scanf("%s", string))
		{
			while ('\n' != getchar());
			printf("TRY AGAIN - WRONG FORMAT\n ");
		}
		else return string;
	}
}

char *checkName() {
	FILE *plik;
	char *name;
	name = calloc(100,sizeof(char));
	printf("TYPE NAME WITH .xls\n");
	system("dir\n");//pokaz pliki w folderze
	scanf("%[^\n]s", name);//zaladuj stringa podanego przez uzytkownika
	scanf("%*c");//wyrzuc entera
	while ((plik = fopen(name, "r")) == NULL)//jaksie nie udalo otworzyc -> powtorz operaje
	{
		printf("NON EXISTING FILE TRY AGAIN\n");
		scanf("%[^\n]s", name);
		scanf("%*c");
	}
	fclose(plik);//zamknij plik
	return name;
}

void search(list **seed) {
	char temp,*buffor = calloc(100,sizeof(char));
	int count= 0;
	char *compare_name,*compare_lastname;
	compare_lastname = calloc(30, sizeof(char));//wyszukuje na podstawie imienia i nazwiska
	compare_name = calloc(30, sizeof(char));
	//while ('\n' != getchar());

	do
	{
		temp = getch();//pobierz znak od uzytkownika
		if (temp == 8)//sprawdzy czy backspace
		{
			if (count>0)//jesli sa juz wpisane jakies znaki to usun ten znak z bufora i zdekrementuj licznik count
			{
				count--;
				buffor[count] = '\0';//wpisz na miejsce ostatniego znaku => znak konca stringa
			}
		}
		else//jak nie backspace to dodaj znak
		{
			*(buffor + count) = temp;
		}

		if (strlen(buffor)==1&& buffor[0]>96)// jesli uzytkownik wpsal z malej litery to zamien ja w buforze na duza
		{
			buffor[0] = buffor[0] - 32;
		}

		system("cls");
		printf("TYPING FIELD: \t%s\n", buffor);
		if (temp!=8)//zwieksz liczik jak nie usuniecie znaku
		{
			count++;
		}


		//searching for contacts
		while ((*seed)->next != NULL)
		{
			(*seed) = (*seed)->next;//przewin liste w poszukiwaniu stringow ktore sa identyczne z tym wpisywanym przez uzytkownika
			compare_name = strstr((*seed)->name, buffor);
			compare_lastname = strstr((*seed)->lastname, buffor);


				
			if (compare_lastname == NULL && compare_name != NULL) {
				if (strlen(compare_name) >= count) {
					printf("name: %s \t last name: %s \t group: %s \t number: %s \n", (*seed)->name, (*seed)->lastname, (*seed)->group, (*seed)->number);
				}
			}
			if (compare_lastname != NULL && compare_name == NULL) {
				if (strlen(compare_lastname) >= count) {
					printf("name: %s \t last name: %s \t group: %s \t number: %s \n", (*seed)->name, (*seed)->lastname, (*seed)->group, (*seed)->number);
				}
			}
			if (compare_lastname != NULL && compare_name != NULL) {
				if (strlen(compare_name) >= count || strlen(compare_lastname) >= count) {
					printf("name: %s \t last name: %s \t group: %s \t number: %s \n", (*seed)->name, (*seed)->lastname, (*seed)->group, (*seed)->number);
				}
			}
	
		}
		while ((*seed)->previous != NULL)
		{
			(*seed) = (*seed)->previous;
		}


	} while (temp != 13);//dopoki uzytkownik nie nacisnie enter
	system("cls");
	

	free(compare_lastname);
	free(compare_name);
	free(buffor);
}


void searchGroup(list **seed) {
	char temp, *buffor = calloc(100, sizeof(char));
	int count = 0;
	char *compare_group;
	compare_group = calloc(30, sizeof(char));

	do
	{
		temp = getch();
		if (temp == 8)
		{
			if (count>0)
			{
				count--;
				buffor[count] = '\0';
			}
		}
		else
		{
			*(buffor + count) = temp;
		}
		system("cls");
		printf("TYPING FIELD: \t%s\n", buffor);
		if (temp != 8)
		{
			count++;
		}
		//searching for contacts
		while ((*seed)->next != NULL)
		{
			(*seed) = (*seed)->next;
			compare_group = strstr((*seed)->group, buffor);

			if (compare_group!=NULL)
			{
				if (strlen(compare_group)>=count)
				{
					printf("name: %s \t last name: %s \t group: %s \t number: %s \n", (*seed)->name, (*seed)->lastname, (*seed)->group, (*seed)->number);
				}
			}

		}
		while ((*seed)->previous != NULL)
		{
			(*seed) = (*seed)->previous;
		}
	} while (temp != 13);
	system("cls");


	free(compare_group);
	free(buffor);
}

void avoid(char *buff,int sizeofbuff,int sizeofdelet) {
	char *temp;
	int i;
	temp = calloc(sizeofbuff, sizeof(char));

	for ( i = 0; i < sizeofbuff; i++)
	{
		temp[i] = buff[i + sizeofdelet];
	}
	for (i = 0; i < sizeofbuff; i++)
	{
		buff[i ] = temp[i];
	}
	free(temp);

}