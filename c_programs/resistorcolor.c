// File:   resistorcolor.c
// Author: Gregory K. Bowne
// Date:   11 Mar 2020
// Time:   19:50:22
// Brief:  This program shows the color codes for resistors used in electronics. It should be able to both give
// the color bands for a given value and give you the value for given color bands.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLORS 10

typedef struct
{
	char *colorNames[MAX_COLORS];
	int colorValues[MAX_COLORS];
	double multipliers[MAX_COLORS];
	double tolerances[MAX_COLORS];
} ResistorColors;

ResistorColors createResistorColors()
{
	ResistorColors rc;

	// Initialize colorNames
	rc.colorNames[0] = "black";
	rc.colorNames[1] = "brown";
	rc.colorNames[2] = "red";
	rc.colorNames[3] = "orange";
	rc.colorNames[4] = "yellow";
	rc.colorNames[5] = "green";
	rc.colorNames[6] = "blue";
	rc.colorNames[7] = "violet";
	rc.colorNames[8] = "gray";
	rc.colorNames[9] = "white";

	// Initialize colorValues
	for (int i = 0; i < MAX_COLORS; i++)
	{
		rc.colorValues[i] = i;
	}

	// Initialize multipliers
	for (int i = 0; i < MAX_COLORS; i++)
	{
		rc.multipliers[i] = pow(10, i);
	}

	// Initialize tolerances
	rc.tolerances[0] = 1.0;
	rc.tolerances[1] = 1.5;
	rc.tolerances[2] = 2.0;
	rc.tolerances[3] = 3.0;
	rc.tolerances[4] = 5.0;

	return rc;
}

double calculateResistance(ResistorColors rc, char *colors[], int numBands)
{
	double resistance = 0;
	for (int i = 0; i < numBands; i++)
	{
		for (int j = 0; j < MAX_COLORS; j++)
		{
			if (strcmp(colors[i], rc.colorNames[j]) == 0)
			{
				resistance += rc.colorValues[j] * rc.multipliers[i];
				break;
			}
		}
	}
	return resistance;
}

char **calculateColorCodes(ResistorColors rc, double resistance, int numBands)
{
	char **colorCodes = malloc(MAX_COLORS * sizeof(char *));
	for (int i = 0; i < MAX_COLORS; i++)
	{
		colorCodes[i] = malloc(10 * sizeof(char)); // Allocate space for the color code string
	}

	// Convert the resistance value to a string
	char resistanceStr[50];
	sprintf(resistanceStr, "%.0f", resistance);

	int len = strlen(resistanceStr);
	for (int i = 0; i < len; i++)
	{
		int digit = resistanceStr[i] - '0';
		strcpy(colorCodes[i], rc.colorNames[digit]);
	}

	return colorCodes;
}

int main()
{
	ResistorColors rc = createResistorColors();
	char *colors[MAX_COLORS];
	int numBands;
	// Get the colors from the user...
	double resistance = calculateResistance(rc, colors, numBands);
	printf("The resistance is %.2f ohms.\n", resistance);
	calculateColorCodes(rc, resistance, numBands);
	return 0;
}
