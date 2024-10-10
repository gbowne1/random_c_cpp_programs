// File:   lowpassfil.c
// Author: Gregory K. Bowne
// Date:   11 NOV 2023
// Time:   13:56:21
// Brief:  This program calculates the cutoff frequency, gain, attenuation, and the values of resistor,
//         capacitor, and inductor for a simple low pass filter.
//         It is open-source and can be used to understand the calculations involved in filter design
//         I designed this in particular for the HF frequency ranges of the spectrum

#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

// Function to calculate the cutoff frequency
double calculateCutoffFrequency(double resistor, double capacitor)
{
	if (resistor <= 0 || capacitor <= 0)
	{
		printf("Error: Resistance and capacitance must be positive values.\n");
		return -1.0; // Or any invalid value to indicate error
	}
	double fc = 1 / (2 * M_PI * resistor * capacitor);
	return fc;
}

// Function to calculate the gain
double calculateGain(double frequency, double fc)
{
	double G = 1 / sqrt(1 + pow((frequency / fc), 2));
	return G;
}

// Function to calculate the attenuation
double calculateAttenuation(double frequency, double fc)
{
	double A = -10 * log10(1 + pow((frequency / fc), 2));
	return A;
}

// Function to calculate the resistor value for a given cutoff frequency and capacitor
double calculateResistor(double fc, double C)
{
	double R = 1 / (2 * M_PI * fc * C);
	return R;
}

// Function to calculate the capacitor value for a given cutoff frequency and resistor
double calculateCapacitor(double fc, double R)
{
	double C = 1 / (2 * M_PI * fc * R);
	return C;
}

// Function to calculate the inductance for a simple low pass filter
double calculateInductance(double fc, double C)
{
	double L = 1 / (2 * M_PI * fc * C);
	return L;
}

int main()
{
	double resistor;  // in ohms (user input)
	double capacitor; // in farads (user input)
	double frequency; // in hertz (user input)

	// User input: Resistance
	printf("Resistance (ohms): ");
	if (scanf("%lf", &resistor) != 1 || resistor <= 0)
	{
		printf("Error: Invalid resistance value. Please enter a positive number.\n");
		return 1;
	}

	// User input: Capacity
	printf("Capacity (Farads): ");
	if (scanf("%lf", &capacitor) != 1 || capacitor <= 0)
	{
		printf("Error: Invalid capacitance value. Please enter a positive number.\n");
		return 1;
	}

	// User input: Frequency
	printf("Frequency (hz): ");
	if (scanf("%lf", &frequency) != 1 || frequency <= 0)
	{
		printf("Error: Invalid frequency value. Please enter a positive number.\n");
		return 1;
	}

	// Perform the calculations (assuming valid input)
	double fc = calculateCutoffFrequency(resistor, capacitor);
	if (fc < 0)
	{
		return 1; // Error handling from calculateCutoffFrequency
	}
	double G = calculateGain(frequency, fc);
	double A = calculateAttenuation(frequency, fc);
	double calculatedResistor = calculateResistor(fc, capacitor);
	double calculatedCapacitor = calculateCapacitor(fc, resistor);
	// Print the results
	printf("Cutoff Frequency: %f Hz\n", fc);
	printf("Gain: %f\n", G);
	printf("Attenuation: %f dB\n", A);
	printf("Calculated Resistor: %f ohms\n", calculatedResistor);
	printf("Calculated Capacitor: %e farads\n", calculatedCapacitor);
	return 0;
}