#include "header.h"
//czy poprawnie wprowadzone dane
int skanInt()
{
	int temp;
	while (1)
	{
		if (scanf("%d", &temp) == 1)
		{
			return temp;
		}
		printf("Bledny format, sprobuj ponownie:\t");
		scanf("%*s");
	}
}

float skanFloat()
{
	float temp;
	while (1)
	{
		if (scanf("%f", &temp) == 1)
		{
			return temp;
		}
		printf("Bledny format, sprobuj ponownie:\t");
		scanf("%*s");
	}
}