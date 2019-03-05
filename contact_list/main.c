#include "header.h"

int main() {
	int option,end1=1;
	int sort = 0;
	list *seed = calloc(1, sizeof(list));
	seed->group = NULL; seed->lastname = NULL; seed->name = NULL; seed->number = NULL; seed->next = NULL; seed->previous = NULL;
	setlocale(LC_ALL, "polish");


	while (end1!=0)
	{
		optionsPrint();
		option = scanInt();//sprawdz co wpisla uzytkownik
		scanf("%*c");
		switch (option)
		{
		case 0:
			end1 = 0;//exit
			clean(&seed);//wyczysc po kolei wszytkie elementy listy
			break;
		case 1:
			loadContacts(&seed);
			break;
		case 2:
			saveContacts(&seed);
			break;
		case 3:
			switch (sort)
			{
			case 0:
				addNormal(&seed);//dodaj kontakt z poziomu uzytkownika
					break;
			case 1:
				addNormal(&seed);
				sortGroup(&seed);//zeby dzialalo trzeba 2 razy posortowac
				sortGroup(&seed);
				break;
			case 2:
				addNormal(&seed);
				sortName(&seed);
				sortName(&seed);
				break;
			case 3:
				addNormal(&seed);
				sortLastName(&seed);
				sortLastName(&seed);
				break;
			default:
				break;
			}

			break;
		case 4:
			rremove(&seed);
			break;
		case 5:
			showList(&seed);
			break;
		case 6:
			sort = 1;//zmienna sort przechowuje informacje o tym jakie ostatnio sortoanie bylo wykonane  - do odpowiedniego dodawania nowych kontaktow
			sortGroup(&seed);
			sortGroup(&seed);
			break;
		case 7:
			sort = 2;
			sortName(&seed);
			sortName(&seed);
			break;
		case 8:
			sort = 3;
			sortLastName(&seed);
			sortLastName(&seed);
			break;
		case 9:
			search(&seed);
			break;
		case 10:
			searchGroup(&seed);
			break;
		default:
			break;
		}
	}



}