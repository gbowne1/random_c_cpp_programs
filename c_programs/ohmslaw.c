// File: ohmslaw.c
// Author: Gregory K. Bowne
// Date:   10 MAY 2020
// Time:   09:54:44
// Brief:  This program calculates voltage using Ohm's Law.

#include <stdio.h>

int main()
{
	// Declare variables for current, resistance, and voltage
	float current, resistance, voltage;

	// Prompt user to enter current in amperes
	printf("Enter the current (I) in amperes: ");
	if (scanf("%f", &current) != 1)
	{ // Check for successful input
		fprintf(stderr, "Error: Invalid input for current.\n");
		return 1; // Indicate failure
	}

	// Prompt user to enter resistance in ohms
	printf("Enter the resistance (R) in ohms: ");
	if (scanf("%f", &resistance) != 1)
	{ // Check for successful input
		fprintf(stderr, "Error: Invalid input for resistance.\n");
		return 1; // Indicate failure
	}

	// Calculate voltage using Ohm's Law: V = I * R
	voltage = current * resistance;

	// Print the calculated voltage with two decimal places
	printf("The voltage (V) is %.2f volts.\n", voltage);

	return 0; // Indicate successful execution
}
