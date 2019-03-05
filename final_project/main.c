#include "biblioteka.h"

int main() {
	int menu=0,segreguj,upewnij;
	kurs *zarodek = calloc(1,sizeof(kurs));
	zarodek->data = NULL; zarodek->ects = 0; zarodek->miejsce = NULL; zarodek->nastepny = NULL; zarodek->nazwa_kursu = NULL; zarodek->ocena = 0; zarodek->poprzedni = NULL; zarodek->prowadzacy = NULL; zarodek->status = NULL;
	setlocale(LC_ALL, "polish");

	utworzBaze();
	wczytajPlan(&zarodek);
	while (menu!=9)
	{
		pokazKursy(&zarodek);
		wypiszMenu();
		printf("\twybierz opcje:\t");
		menu = scanInt();
		switch (menu)
		{
		case 1:
			dodajRecznie(&zarodek);
			break;
		case 2:
			zmienDate(&zarodek);
			break;
		case 3:
			printf("\n1 -> segreguj alfabetycznie nazwami kursu\n2 -> segreguj datami\n3 -> segreguj iloscia punktow ects\n");
			segreguj = scanInt();
			//jaka segregacja
			switch (segreguj)
			{
			case 1:
				segregujKursy(&zarodek);
				segregujKursy(&zarodek);
				break;
			case 2:
				segregujDaty(&zarodek);
				segregujDaty(&zarodek);
				break;
			case 3:
				segregujEcts(&zarodek);
				segregujEcts(&zarodek);
				break;
			default:
				break;
			}
			//koniec segregacji
			break;
		case 4:
			zapiszPlan(&zarodek);
			break;
		case 5:
			zmienStatus(&zarodek);
			break;
		case 6:
			wyrzucWybrany(&zarodek);
			break;
		case 7:
			liczSrednia(&zarodek);
			break;
		case 8:
			printf("\n czy napewno chcesz wyczyscic obecny plan?\n\tkazda liczba naturalna -> NIE\n\t\t2 -> TAK\n");
			upewnij = scanInt();
			//upewnij sie
			if (upewnij==2)
			{
				wyczyscPlan(&zarodek);
				zarodek->data = NULL; zarodek->ects = 0; zarodek->miejsce = NULL; zarodek->nastepny = NULL; zarodek->nazwa_kursu = NULL; zarodek->ocena = 0; zarodek->poprzedni = NULL; zarodek->prowadzacy = NULL; zarodek->status = NULL;
			}
			//upewnij sie
			break;
		case 9:
			wyczysc(&zarodek);
			break;
		case 10:
			szukajDat(&zarodek);
			break;
		default:
			system("cls");
			printf("taka opcja nie istnieje");
			break;
		}
	}
}