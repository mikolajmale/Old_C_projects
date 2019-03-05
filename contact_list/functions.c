#include "header.h"

void addNormal(list **seed) {
	list *contact = calloc(1, sizeof(list));
	list *temp;
	getData(contact);//pobierz dane od uzytkownika
	if (((*seed)->next == NULL) && ((*seed)->previous == NULL)) {//co jak pierwszy element
		contact->previous = *seed;
		(*seed)->next = contact;
		contact->next = NULL;
	}
	else
	{
		temp = (*seed)->next;
		temp->previous = contact;
		contact->next = temp;
		contact->previous = (*seed);
		(*seed)->next = contact;
	}
}

void addLoad(list **seed, FILE *file) {//jako parametr -> glowny wskaznik na liste i wskaznik na plik z ktorego czytamy
	list *contact = calloc(1, sizeof(list));//pamiec na nowy kontakt
	list *temp;
	contact->group = calloc(20, sizeof(char));//pamiec na poszcegolne informacje
	contact->lastname = calloc(20, sizeof(char));
	contact->number = calloc(20, sizeof(char));
	contact->name = calloc(20, sizeof(char));
	fscanf(file, "%[^;]s", contact->name);//wczytuj odpowiednie kolumny w excelu i pomjaj znaki robocze
	fscanf(file, ";");
	fscanf(file, "%[^;]s", contact->lastname);
	fscanf(file, ";");
	fscanf(file, "%[^;]s", contact->group);
	fscanf(file, ";");
	fscanf(file, "%[^\n]s", contact->number);
	fscanf(file, "\n");
	if (((*seed)->next == NULL) && ((*seed)->previous == NULL)) {//cojesi piereszy element
		contact->previous = *seed;
		(*seed)->next = contact;
		contact->next = NULL;
	}
	else
	{
		temp = (*seed)->next;
		temp->previous = contact;
		contact->next = temp;
		contact->previous = (*seed);
		(*seed)->next = contact;
	}
}

void getData(list *contact) {//obsluz uzytkownika i wpisz w argument funkcji podane dane kontaktu
	contact->group = calloc(20, sizeof(char));
	contact->lastname = calloc(20, sizeof(char));
	contact->number = calloc(20, sizeof(char));
	contact->name = calloc(20, sizeof(char));
	printf("type: name\n");
	scanf("%[^\n]s", contact->name);
	scanf("%*c");
	printf("type: last name\n");
	scanf("%[^\n]s", contact->lastname);
	scanf("%*c");
	printf("type: group\n");
	scanf("%[^\n]s", contact->group);
	scanf("%*c");
	printf("type: number\n");
	scanf("%[^\n]s", contact->number);
	scanf("%*c");
	
}

void clean(list **seed) {

	while ((*seed)->next != NULL)
	{
		(*seed) = (*seed)->next;
		free((*seed)->previous);
		free((*seed)->group);
		free((*seed)->lastname);
		free((*seed)->number);
		free((*seed)->name);
	}
	free((*seed));
}

void showList(list **seed) {
	int i = 0;
	while ((*seed)->next != NULL)//przewijaj liste - pokazuj kontakty
	{
		i++;
		(*seed) = (*seed)->next;
		printf("%d. name: %s \t last name: %s \t group: %s \t number: %s \n",i, (*seed)->name, (*seed)->lastname, (*seed)->group, (*seed)->number);
	}
	while ((*seed)->previous != NULL)//przewin wskaznik spowrotem
	{
		(*seed) = (*seed)->previous;
	}
}

int countList(list **seed) {
	int i=0;
	while ((*seed)->next != NULL)
	{
		(*seed) = (*seed)->next;
		i++;
	}
	while ((*seed)->previous != NULL)
	{
		(*seed) = (*seed)->previous;
	}
	return i;
}

void loadContacts(list **seed) {
	FILE *file;
	char *name = checkName();//sprawdz czy jest taki plik
	char *temp = calloc(20, sizeof(char));
	file = fopen(name, "r");
	

	
	while (fgetc(file)!=EOF)//rob dopoki nie napotkasz znaku konca pliku
	{
		fseek(file, -1, SEEK_CUR);
		addLoad(seed, file);//dodaj kontakt z pliku
		
	}
	fclose(file);
	free(name);
	free(temp);
}

void saveContacts(list **seed) {
	FILE *file;
	char *name[20];
	printf("TYPE NAME OF YOUR CONTACTS\n");
	scanf("%[^\n]s\n",name);
	strcat(name, ".csv");//dopisz do nazwy pliku rozszerzeie
	file = fopen(name,"w");
	while ((*seed)->next != NULL)//dopoki nie skonczy sie lista - w odpowiednim formacie wpisuj dane do arkusza
	{
		(*seed) = (*seed)->next;
		fprintf(file,"%s;%s;%s;%s\n", (*seed)->name, (*seed)->lastname, (*seed)->group, (*seed)->number);
	}
	while ((*seed)->previous != NULL)//przewin wskaznik seed na poczatke listy
	{
		(*seed) = (*seed)->previous;
	}
	fclose(file);
}

int sortName(list **seed) {
	int option = 0;
	int check = 0;
	int end = 0;
	int size = countList(seed),i;
	char first;
	list *temp = (*seed)->next;
	list *temp1 = NULL,*temp2 = NULL;
	list *fromseed= (*seed)->next;

	if ((*seed)->next!=NULL)
	{
		temp = temp->next;

		for ( i = 0; i < size; i++)
		{
			if (i != 0) {
				temp = (*seed)->next;
				temp = temp->next;
				fromseed = (*seed)->next;
			}

			while ((temp != NULL) && (end != 1))
			{

				if (strcoll(fromseed->name, temp->name)>0)
				{
					if (temp->next != NULL)
					{
						check = 1;
						temp1 = temp->next;
						temp2 = fromseed->previous;
						//first pair
						temp2->next = temp;
						temp->previous = temp2;
						//second pair
						temp->next = fromseed;
						fromseed->previous = temp;
						//third pair
						fromseed->next = temp1;
						temp1->previous = fromseed;
					}
					else
					{
						end = 1;
						temp1 = temp->next;
						temp2 = fromseed->previous;
						//first pair
						temp2->next = temp;
						temp->previous = temp2;
						//second pair
						temp->next = fromseed;
						fromseed->previous = temp;
						//third pair
						fromseed->next = temp1;
					}
				}

				if (check == 0)
				{
					temp = temp->next;
					fromseed = fromseed->next;
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

int sortLastName(list **seed) {
	int option = 0;
	int check = 0;
	int end = 0;
	int size = countList(seed), i;
	char first;
	list *temp = (*seed)->next;
	list *temp1 = NULL, *temp2 = NULL;
	list *fromseed = (*seed)->next;

	if ((*seed)->next != NULL)
	{
		temp = temp->next;

		for (i = 0; i < size; i++)
		{
			if (i != 0) {
				temp = (*seed)->next;
				temp = temp->next;
				fromseed = (*seed)->next;
			}

			while ((temp != NULL) && (end != 1))
			{

				if (strcoll(fromseed->lastname, temp->lastname)>0)
				{
					if (temp->next != NULL)
					{
						check = 1;
						temp1 = temp->next;
						temp2 = fromseed->previous;
						//first pair
						temp2->next = temp;
						temp->previous = temp2;
						//second pair
						temp->next = fromseed;
						fromseed->previous = temp;
						//third pair
						fromseed->next = temp1;
						temp1->previous = fromseed;
					}
					else
					{
						end = 1;
						temp1 = temp->next;
						temp2 = fromseed->previous;
						//first pair
						temp2->next = temp;
						temp->previous = temp2;
						//second pair
						temp->next = fromseed;
						fromseed->previous = temp;
						//third pair
						fromseed->next = temp1;
					}
				}

				if (check == 0)
				{
					temp = temp->next;
					fromseed = fromseed->next;
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

int sortGroup(list **seed) {
	int option = 0;
	int check = 0;
	int end = 0;
	int size = countList(seed), i;
	char first;
	list *temp = (*seed)->next;
	list *temp1 = NULL, *temp2 = NULL;
	list *fromseed = (*seed)->next;

	if ((*seed)->next != NULL)//czy jest odpowiednia ilosc czlonow listy zeby wykonac zamaine
	{
		temp = temp->next;

		for (i = 0; i < size; i++)
		{
			if (i != 0) {
				temp = (*seed)->next;
				temp = temp->next;
				fromseed = (*seed)->next;
			}

			while ((temp != NULL) && (end != 1))
			{

				if (strcoll(fromseed->group, temp->group)>0)// porownaj nazwy dwoch 
				{//jesli ma nastapic alfabetyczna zamiana kontaktow to:
					if (temp->next != NULL)// jesli nie koniec listy
					{// pozamieniaj odpowiednio wskazniki elementow listy
						check = 1;
						temp1 = temp->next;
						temp2 = fromseed->previous;
						//first pair
						temp2->next = temp;
						temp->previous = temp2;
						//second pair
						temp->next = fromseed;
						fromseed->previous = temp;
						//third pair
						fromseed->next = temp1;
						temp1->previous = fromseed;
					}
					else
					{
						end = 1;
						temp1 = temp->next;
						temp2 = fromseed->previous;
						//first pair
						temp2->next = temp;
						temp->previous = temp2;
						//second pair
						temp->next = fromseed;
						fromseed->previous = temp;
						//third pair
						fromseed->next = temp1;
					}
				}

				if (check == 0)
				{
					temp = temp->next;
					fromseed = fromseed->next;
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

void rremove(list **seed) {
	int choose,i=0;
	list *to_remove, *next_c;
	int size = countList(seed);//ile kontaktow
	printf("TYPE LISTING NUMBER OF CONTACT YOU WANT TO REMOVE, TOTAL AMOUNT OF YOUR CONTACTS: %d\n", size);
	choose = scanInt();//sprawdz czy poprawnie wpisane

	while (choose>size||choose<1)//czy wpisana wartosc miesci sie w przedziale dostepnych kontaktow
	{
		printf("DONT HAVE SUCH CONTACT, TRY AGAIN\n");
		choose = scanInt();
	}

	while (i!= choose-1)
	{
		(*seed) = (*seed)->next;
		i++;
	}
	//in this place to_remove is our wanted contact
	to_remove = (*seed)->next;//nasz poszukiwany gagatek
	if (to_remove->next!=NULL)//zapelnij luke po usunietym
	{
		next_c = to_remove->next;

		(*seed)->next = next_c;
		next_c->previous = (*seed);
	}
	else
	{
		(*seed)->next = NULL;
	}
	


	free(to_remove->group);//usun
	free(to_remove->lastname);
	free(to_remove->number);
	free(to_remove->name);
	free(to_remove);

	while ((*seed)->previous != NULL)//przewin wskaznik
	{
		(*seed) = (*seed)->previous;
	}

}
