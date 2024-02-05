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
	
char *COLORS[MAX_COLORS] = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "gray", "white"};

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
	for (int i = 0; i < MAX_COLORS; i++)
	{
		rc.colorNames[i] = COLORS[i];
	}

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

void usage(char *appName)
{
    printf("Usage: %s <colors>\n", appName);
    printf("Colors: ");
    for (int i = 0; i < MAX_COLORS; i++) {
        printf("%s ", COLORS[i]);
    }
    printf("\n");
}

int getNumBands(int numParameters)
{
    return numParameters - 1;
}

char populateColors(char **colors, int numParameters, char **parameters)
{
    for (int i = 0, j = 1; j < numParameters; i++, j++)
    {
        colors[i] = parameters[j];
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage(argv[0]);
        return 0;
    }

    int numBands = getNumBands(argc);

    char *colors[MAX_COLORS];
    populateColors(colors, argc, argv);

	ResistorColors rc = createResistorColors();
	double resistance = calculateResistance(rc, colors, numBands);
	printf("The resistance is %.2f ohms.\n", resistance);
	calculateColorCodes(rc, resistance, numBands);

    return 0;
}
