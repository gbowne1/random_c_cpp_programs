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

#define _CRT_SECURE_NO_WARNINGS

#define MAX_COLORS 10
#define MAX_COLOR_NAME_SIZE 50

#define COMMAND_CODE_COLORS 1
#define COMMAND_NAME_COLORS "colors"
#define COMMAND_CODE_RESISTANCE 2
#define COMMAND_NAME_RESISTANCE "resistance"
#define COMMAND_CODE_TOLERANCE 3 // Define the new command code for tolerance
#define COMMAND_NAME_TOLERANCE "tolerance" // Define the name for the tolerance command
#define COMMAND_CODE_INVALID -1

#define POS_COMMAND_PARAMETER 1
#define POS_REMINDER_PARAMETER 2

#define NUM_MIM_PARAMETERS 3

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

	// Initialize
	for (int i = 0; i < MAX_COLORS; i++)
	{
		// Initialize colorNames
		rc.colorNames[i] = COLORS[i];

		// Initialize colorValues
		rc.colorValues[i] = i;

		// Initialize multipliers
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
double calculateMaxCurrent(double resistance)
{
	double wattage;
	double current;
	printf("%s", "please enter the wattage of the resistor...\n");
	scanf_s("%lf", &wattage);
	current = sqrt(wattage / resistance);
	return current;

}
double calculateResistance(ResistorColors rc, char *colors[], int numBands)
{
    double resistance = 0;
    for (int i = 0; i < numBands; i++)
    {
        int j = 0;
        while (strcmp(colors[i], rc.colorNames[j]) != 0 && j < MAX_COLORS)
        {
            j++;
        }
        if (j < MAX_COLORS)
        {
            resistance += rc.colorValues[j] * rc.multipliers[i];
        }
    }
    return resistance;
}

void calculateColorCodes(char colorCodes[MAX_COLORS][MAX_COLOR_NAME_SIZE], ResistorColors rc, double resistance)
{
    char resistanceStr[50];
snprintf(resistanceStr, sizeof(resistanceStr), "%.0f", resistance);

    int len = strlen(resistanceStr);
    for (int i = 0; i < len && i < MAX_COLORS; i++)
    {
        int digit = resistanceStr[i] - '0';
        strncpy(colorCodes[i], rc.colorNames[digit], MAX_COLOR_NAME_SIZE);
    }
}

double calculateTolerance(ResistorColors rc, char *colors[], int numBands)
{
	double tolerance = 0;
	for (int i = 0; i < numBands; i++)
	{
		for (int j = 0; j < MAX_COLORS; j++)
		{
			if (strcmp(colors[i], rc.colorNames[j]) == 0)
			{
				tolerance += rc.tolerances[j];
				break;
			}
		}
	}
	return tolerance;
}

void usage(char *appName)
{
	printf("Usage: %s %s <resistance>\n", appName, COMMAND_NAME_RESISTANCE);
	printf("Usage: %s %s <colors>\n", appName, COMMAND_NAME_COLORS);
	printf("Colors: ");
	for (int i = 0; i < MAX_COLORS; i++)
	{
		printf("%s ", COLORS[i]);
	}
	printf("\n");
}

int getCommandCode(char **parameters)
{
    if (strcmp(parameters[POS_COMMAND_PARAMETER], COMMAND_NAME_RESISTANCE) == 0)
    {
        return COMMAND_CODE_RESISTANCE;
    }
    if (strcmp(parameters[POS_COMMAND_PARAMETER], COMMAND_NAME_COLORS) == 0)
    {
        return COMMAND_CODE_COLORS;
    }
    if (strcmp(parameters[POS_COMMAND_PARAMETER], "tolerance") == 0) // New command for tolerance
    {
        return COMMAND_CODE_TOLERANCE;
    }

    return COMMAND_CODE_INVALID; // Handle invalid commands
}

int getNumBands(int numParameters)
{
	return numParameters - POS_REMINDER_PARAMETER;
}

char populateColors(char **colors, int numParameters, char **parameters)
{
	for (int i = 0, j = POS_REMINDER_PARAMETER; j < numParameters; i++, j++)
	{
		colors[i] = parameters[j];
	}
}

double getResistance(char **parameters)
{
	return atof(parameters[POS_REMINDER_PARAMETER]);
}

int main(int argc, char **argv)
{
	char *appName = argv[0];

	if (argc < NUM_MIM_PARAMETERS)
	{
		usage(appName);
		return 0;
	}

	ResistorColors rc = createResistorColors();
	int command = getCommandCode(argv);

	switch (command)
	{
	case COMMAND_CODE_COLORS:
	{
		int numBands = getNumBands(argc);

		char *colors[MAX_COLORS];
		populateColors(colors, argc, argv);

		double resistance = calculateResistance(rc, colors, numBands);
		printf("The resistance is %.2f ohms.\n", resistance);
		break;
	}

	case COMMAND_CODE_RESISTANCE:
	{
		char colorCodes[MAX_COLORS][MAX_COLOR_NAME_SIZE] = {0};
		double resistance = getResistance(argv);
		calculateColorCodes(colorCodes, rc, resistance);
		printf("The colors are ");
		for (int i = MAX_COLORS - 1; i >= 0; i--)
		{
			if (strcmp(colorCodes[i], "\0") != 0)
			{
				printf("%s ", colorCodes[i]);
			}
		}
		printf("\n");
		break;
	}

	case COMMAND_CODE_TOLERANCE:
	{
		int numBands = getNumBands(argc);

		char *colors[MAX_COLORS];
		populateColors(colors, argc, argv);

		double tolerance = calculateTolerance(rc, colors, numBands);
		printf("The tolerance is %.2f%%.\n", tolerance);
		break;
	}

	default:
		usage(appName);
	}

	return 0;
}
