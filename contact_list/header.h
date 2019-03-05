#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <locale.h>

typedef  struct list {
	char *name;
	char *lastname;
	char *number;
	char *group;
	struct list *previous;
	struct list *next;
}list;

//BUFFOR FUNCTIONS
void optionsPrint();
int scanInt();
char *scanString();
char *checkName();
void search(list **seed);
void searchGroup(list **seed);
void avoid(char *buff, int sizeofbuff, int sizeofdelet);

//MAIN FUNCTIONS
void getData(list *contact);
void addNormal(list **seed);
void addLoad(list **seed, FILE *file);
void clean(list **seed);
void showList(list **seed);
void loadContacts(list **seed);
void saveContacts(list **seed);
int sortName(list **seed);
int countList(list **seed);
int sortGroup(list **seed);
int sortLastName(list **seed);
void rremove(list **seed);