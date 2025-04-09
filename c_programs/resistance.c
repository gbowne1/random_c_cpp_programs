// File:   resistance.c
// Author: Gregory K. Bowne
// Date:   17 MAY 2021
// Time:   11:34:38
// Brief:  This program calculates series and parallel resistance.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Function to calculate the max current flowing trough a resistor
float calcMaxCurrent(float resistor, float wattage)
{
	float current = 0;
	current = sqrt(wattage / resistor);
	return current;
}

// Function to calculate total resistance in series
float calcSeriesResistance(float resistors[], int count)
{
	float total = 0;
	for (int i = 0; i < count; i++)
	{
		total += resistors[i];
	}
	return total;
}

// Function to calculate total resistance in parallel
float calcParallelResistance(float resistors[], int count)
{
	float total = 0;
	for (int i = 0; i < count; i++)
	{
		total += 1 / resistors[i];
	}
	return 1 / total;
}

int main()
{
	int count;
	printf("Enter the number of resistors: ");
	scanf("%d", &count);

	float *resistors = (float *)malloc(count * sizeof(float));
	if (resistors == NULL)
	{
		printf("Memory allocation failed.\n");
		return 1;
	}
	for (int i = 0; i < count; i++)
	{
		printf("Enter the resistance of resistor %d: ", i + 1);
		scanf("%f", &resistors[i]);
	}

	float series = calcSeriesResistance(resistors, count);
	float parallel = calcParallelResistance(resistors, count);
	free(resistors);

	printf("Total resistance in series: %.2f ohms\n", series);
	printf("Total resistance in parallel: %.2f ohms\n", parallel);

	return 0;

	return 0;
}
