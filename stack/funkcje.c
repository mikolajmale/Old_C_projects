#include "header.h"

void push(stos **sztos, float real, float imaginary) {
	stos *newe;
	newe = malloc(sizeof(stos));
	newe->data = real;
	newe->redata = imaginary;

		newe->previous = *sztos;
		*sztos = newe;

	printf("%f im%f\n", (*sztos)->data, (*sztos)->redata);
}

void pushFrom(stos **sztos, stos **temp) {
	stos *newe;
	newe = malloc(sizeof(stos));
	newe->data = (*sztos)->data;
	newe->redata = (*sztos)->redata;

	newe->previous = *temp;
	*temp = newe;

}

math pop(stos **sztos) {
	stos *temp;
	math number;
	if ((*sztos)->previous == NULL) {
		printf("stos jest pusty\n");
	}
	else
	{
		number.data = (*sztos)->data;
		number.redata = (*sztos)->redata;
		printf("%f im%f\n", (*sztos)->data, (*sztos)->redata);
		temp = (*sztos)->previous;
		free(*sztos);
		*sztos = temp;
	}
	return number;
}

void check(stos **sztos) {
	if ((*sztos)->previous == NULL) {
		printf("stos jest pusty\n");
	}
	else
	{
		printf("stos nie jest pusty\n");
	}
}

void clean(stos **sztos) {
	while ((*sztos)->previous != NULL)
	{
		pop(sztos);
	}
	system("cls");
}

int show(stos **sztos) {
	int i=0;
	stos *temp = calloc(1,sizeof(stos));
	temp->data = 0;
	temp->redata = 0;
	temp->previous = NULL;
	while ((*sztos)->previous != NULL)
	{
		i++;
		pushFrom(sztos, &temp);
		pop(sztos);
	}
	system("cls");
	while (temp->previous != NULL)
	{
		pushFrom(&temp, sztos);
		pop(&temp);
	}
	return i;
}

char *avoid(char *bufor) {
	char temp[15];
	char *buff;
	int i;
	int str;
	buff = calloc(40, sizeof(char));
	sscanf(bufor, "%s", temp);
	str = strlen(temp);
	for ( i = 0; i < 39-str; i++)
	{
		buff[i] = bufor[i + str + 1];
	}
	free(bufor);
	return buff;
}

void add(stos **sztos) {
	math number1, number2,number3;
	number1 = pop(sztos);
	number2 = pop(sztos);
	number3.data = number1.data + number2.data;
	number3.redata = number1.redata + number2.redata;
	push(sztos, number3.data, number3.redata);
}

void subtract(stos **sztos) {
	math number1, number2, number3;
	number1 = pop(sztos);
	number2 = pop(sztos);
	number3.data = number1.data - number2.data;
	number3.redata = number1.redata - number2.redata;
	push(sztos, number3.data, number3.redata);
}

void multiply(stos **sztos) {
	math number1, number2, number3;
	number1 = pop(sztos);
	number2 = pop(sztos);
	number3.data = number1.data * number2.data - number1.redata*number2.redata;
	number3.redata = number1.redata*number2.data + number1.data*number2.redata;
	push(sztos, number3.data, number3.redata);
}

int divide(stos **sztos) {
	int question = 1;
	float denominator;
	math number1, number2, number3;
	number1 = pop(sztos);
	number2 = pop(sztos);
	denominator = number2.data*number2.data + number2.redata*number2.redata;
	if ((number2.data != 0) && (number2.redata != 0)) {
		number3.data = (number1.data * number2.data + number1.redata*number2.redata)/denominator;
		number3.redata = (number1.redata*number2.data - number1.data*number2.redata)/denominator;
		push(sztos, number3.data, number3.redata);
	}
	else
	{
		printf("ERROR - DIVIDING BY ZERO\n");
		question = 0;
	}
	return question;
}

int canIt(stos **sztos) {
	int can;
	int option=1;
	can = show(sztos);
	system("cls");
	if (can<2)
	{
		printf("ERROR - NOT ENOUGH NUMBERS TO EXECUTE\n");
		option = 0;
	}
	return option;
}
int canIt2(stos **sztos) {
	int can;
	int option = 1;
	can = show(sztos);
	system("cls");
	if (can<1)
	{
		printf("ERROR - NOT ENOUGH NUMBERS TO EXECUTE\n");
		option = 0;
	}
	return option;
}

void coulping(stos **sztos) {
	math number1;
	number1 = pop(sztos);
	number1.redata = -number1.redata;
	push(sztos, number1.data, number1.redata);
}
