// File:   rcnetwork.c
// Author: Gregory K. Bowne
// Date:   11 SEPT 2019
// Time:   13:51:11
// Brief:  This program calculates a rc network consisting of a resistor and capacitor

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

// Function to calculate the characteristic frequency
double calculateCharacteristicFrequency(double resistance, double capacitance) {
    return 1 / (2 * M_PI * resistance * capacitance);
}

// Function to calculate the capacitor charge time
double calculateCapacitorChargeTime(double resistance, double capacitance) {
    return 0.693 / (resistance * capacitance);
}

// Function to calculate the RC time constant
double calculateRCtimeConstant(double resistance, double capacitance) {
    return resistance * capacitance;
}

int main() {
    double resistance, capacitance;
	char input[100];

    printf("Enter the resistance (R) in ohms: ");
    fgets(input, sizeof(input), stdin);
    resistance = strtod(input, NULL);

    printf("Enter the capacitance (C) in farads: ");
    fgets(input, sizeof(input), stdin);
    capacitance = strtod(input, NULL);

    printf("The characteristic frequency (f) is %.2f Hz.\n", calculateCharacteristicFrequency(resistance, capacitance));
    printf("The capacitor charge time (tau) is %.2f seconds.\n", calculateCapacitorChargeTime(resistance, capacitance));
    printf("The RC time constant (τ) is %.2f seconds.\n", calculateRCtimeConstant(resistance, capacitance));

    return 0;
}