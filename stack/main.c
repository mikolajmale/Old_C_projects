#include "header.h"

int main() {
	int menu = 1;
	int i = 0,endit=1,question;
	float real,imaginary=0;
	char charac, *command, *showo,*isempty,*clearo,*end;//zmienne do porownania z buforem
	stos *sztos = calloc(1, sizeof(stos));
	char *bufor;

	sztos->data = 0;
	sztos->redata = 0;
	sztos->previous = NULL;
	bufor = calloc(40, sizeof(char));
	command = calloc(20, sizeof(char));
	showo = calloc(20, sizeof(char));
	isempty = calloc(20, sizeof(char));
	clearo = calloc(20, sizeof(char));
	end = calloc(20, sizeof(char));
	strcpy(showo, "SHOW");//kopiowanie zawartosci do stringa
	strcpy(isempty, "EMPTY");
	strcpy(clearo, "CLEAR");
	strcpy(end, "END");

	while (endit!=0)
	{
		
		printf("komenda  - czy stos jest pusty \t EMPTY\n");
		printf("komenda  - wyswietl stos \t SHOW\n");
		printf("komenda  - wyczysc stos  \t CLEAR\n");
		printf("komenda  - zakoncz program  \t END\n");

		scanf("%[^\n]s", bufor);//zapisz caly ciag znakow do bufora
		scanf("%*c");//pomin znak nowej linii
		while (bufor[0] != '\0')//dopoki bufor nie bedie pusty
		{
			imaginary = 0;
			sscanf(bufor, "%s", command);
			if (strcmp(command,showo)==0)
			{
				show(&sztos);
				bufor = avoid(bufor);
			}
			if (strcmp(command, isempty) == 0)
			{
				check(&sztos);
				bufor = avoid(bufor);
			}
			if (strcmp(command, clearo) == 0)
			{
				clean(&sztos);
				bufor = avoid(bufor);
			}
			if (strcmp(command, end) == 0)
			{
				clean(&sztos);
				bufor = avoid(bufor);
				endit = 0;
			}

			if (sscanf(bufor, "%f", &real) == 1) {
				bufor = avoid(bufor);
				if ((bufor[0] == 'i') && (bufor[1] == 'm')) {
					if (sscanf(bufor, "%*c%*c%f", &imaginary) == 1)
					{
						bufor = avoid(bufor);
					}
				}

				push(&sztos, real, imaginary);
			}

			if (sscanf(bufor, "%c", &charac) == 1) {
				if (charac=='+')
				{
					if (canIt(&sztos) == 1)
					{
						add(&sztos);
						bufor = avoid(bufor);
					}
					else
					{
						bufor[0] = '\0';
					}
					
				}
				if (charac == '-')
				{
					if (canIt(&sztos) == 1)
					{
						subtract(&sztos);
						bufor = avoid(bufor);
					}
					else
					{
						bufor[0] = '\0';
					}
				}
				if (charac == 'c')
				{
					if (canIt2(&sztos) == 1)
					{
						coulping(&sztos);
						bufor = avoid(bufor);
					}
					else
					{
						bufor[0] = '\0';
					}
				}
				if (charac == '*')
				{
					if (canIt(&sztos) == 1)
					{
						multiply(&sztos);
						bufor = avoid(bufor);
					}
					else
					{
						bufor[0] = '\0';
					}
				}
				if (charac == '/')
				{


					if (canIt(&sztos) == 1)
					{
						question = divide(&sztos, bufor);
						if (question == 1) {
							bufor = avoid(bufor);
						}
						else
						{
							bufor[0] = '\0';
						}
					}
					else
					{
						bufor[0] = '\0';
					}

				}
			}
		}
	}

		
		free(end);
		free(clearo);
		free(showo);
		free(bufor);
		free(command);
}