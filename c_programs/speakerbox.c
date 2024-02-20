// File:   speakerbox.c
// Author: Gregory K. Bowne
// Date:   11 NOV 2023
// Time:   13:56:21
// Brief:  This program calculates the size of a speaker box for use when building custom speaker boxes,.
//         It is open-source and can be used to understand the calculations involved in speaker box design

#include <stdio.h>

// Function to calculate the internal volume of the speaker box
double calculateInternalVolume(double width, double height, double depth, double driverDisplacement, double portDisplacement)
{
	// Calculate the internal volume
	double internalVolume = (width) * (height) * (depth);
	// Adjust for driver and port displacements
	internalVolume -= driverDisplacement;
	internalVolume -= portDisplacement;
	internalVolume *= 0.0163871;
	return internalVolume;
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Function to read a double value with validation
double readDouble(const char *prompt)
{
	double value;
	printf("%s", prompt);
	while (scanf("%lf", &value) != 1)
	{
		printf("Invalid input. Please enter a number.\n");
		clearInputBuffer();
	}
	return value;
}
// Function to provide a recommendation based on the volume
void provideRecommendation(double volume)
{
	if (volume < 10)
	{
		printf("This volume is suitable for small bookshelf speakers.\n");
	}
	else if (volume >= 10 && volume < 30)
	{
		printf("This volume is suitable for medium-sized room speakers.\n");
	}
	else
	{
		printf("This volume is suitable for large floor-standing speakers.\n");
	}
}

int main()
{
	// Input values for width, height, and depth
	double width, height, depth, driverDisplacement, portDisplacement;

	printf("Enter the dimensions in inches.\n");

	// Prompt the user to input the dimensions of the speaker box
	printf("Enter the width of the speaker box: ");
	scanf("%lf", &width);
	printf("Enter the height of the speaker box: ");
	scanf("%lf", &height);
	printf("Enter the depth of the speaker box: ");
	scanf("%lf", &depth);

	// Prompt the user to input the driver displacement
	printf("Enter the driver displacement: ");
	scanf("%lf", &driverDisplacement);

	// Prompt the user to input the port displacement
	printf("Enter the port displacement: ");
	scanf("%lf", &portDisplacement);

	// Calculate the internal volume
	double volume = calculateInternalVolume(width, height, depth, driverDisplacement, portDisplacement);

	// Display the calculated internal volume
	printf("The internal volume of the speaker box is: %.2f cubic units\n", volume);
	provideRecommendation(volume);

	return 0;
}
