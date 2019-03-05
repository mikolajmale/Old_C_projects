#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef  struct stos {//struktura na stos
	float data;
	float redata;
	struct stos *previous;
}stos;

typedef struct {//struktura do przekazania wartosci funkcji
	float data;
	float redata;
}math;

void push(stos **sztos, float real, float imaginary);
math pop(stos **sztos);
void check(stos **sztos);
void clean(stos **sztos);
void pushFrom(stos **sztos, stos **temp);
int show(stos **sztos);
void pushFrom(stos **sztos, stos **temp);
char *avoid(char *bufor);
void add(stos **sztos);
void subtract(stos **sztos);
void multiply(stos **sztos);
int divide(stos **sztos);
int canIt(stos **sztos);
void coulping(stos **sztos);
int canIt2(stos **sztos);

float skanFloat();
int skanInt();
