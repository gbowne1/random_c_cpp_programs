#define _CRT_SECURE_NO_WARNINGS

// File:   voltagediv.c
// Author: Gregory K. Bowne
// Date:   10 MAY 2020
// Time:   09:54:44
// Brief:  This program calculates voltage dividers

#include <stdio.h>

float calculateOutputVoltage(float R1, float R2, float V)
{
	if (R1 <= 0 || R2 <= 0 || V <= 0)
	{
		printf("Error: All values must be positive.\n");
		return -1;
	}
	return (R2 / (R1 + R2)) * V;
}

int main()
{
	float R1, R2, V, Vout;

	do
	{
		printf("Enter the first resistance (R1) in ohms: ");
	} while (scanf("%f", &R1) != 1 || R1 <= 0);

	do
	{
		printf("Enter the second resistance (R2) in ohms: ");
		scanf("%f", &R2);
		if (R2 <= 0)
			printf("Invalid input. Please enter a positive number.\n");
	} while (R2 <= 0);

	do
	{
		printf("Enter the total voltage (V) in volts: ");
		scanf("%f", &V);
		if (V <= 0)
			printf("Invalid input. Please enter a positive number.\n");
	} while (V <= 0);

	Vout = calculateOutputVoltage(R1, R2, V);

	if (Vout != -1)
	{
		printf("The output voltage (Vout) is %.2f volts.\n", Vout);
	}

	return 0;
}