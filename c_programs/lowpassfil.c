// File:   lowpassfil.c
// Author: Gregory K. Bowne
// Date:   11 NOV 2023
// Time:   13:56:21
// Brief:  This program calculates the cutoff frequency, gain, attenuation, and the values of resistor,
//         capacitor, and inductor for a simple low pass filter.
//         It is open-source and can be used to understand the calculations involved in filter design.

#include <stdio.h>
#include <math.h>

// Function to calculate the cutoff frequency
double calculateCutoffFrequency(double R, double C) {
    double fc = 1 / (2 * M_PI * R * C);
    return fc;
}

// Function to calculate the gain
double calculateGain(double f, double fc) {
    double G = 1 / sqrt(1 + pow((f / fc), 2));
    return G;
}

// Function to calculate the attenuation
double calculateAttenuation(double f, double fc) {
    double A = -10 * log10(1 + pow((f / fc), 2));
    return A;
}

// Function to calculate the resistor value for a given cutoff frequency and capacitor
double calculateResistor(double fc, double C) {
    double R = 1 / (2 * M_PI * fc * C);
    return R;
}

// Function to calculate the capacitor value for a given cutoff frequency and resistor
double calculateCapacitor(double fc, double R) {
    double C = 1 / (2 * M_PI * fc * R);
    return C;
}

// Function to calculate the inductance for a simple low pass filter
double calculateInductance(double fc, double C) {
    double L = 1 / (2 * M_PI * fc * C);
    return L;
}

int main() {
    double R = 1000; // in ohms
    double C = 10e-6; // in farads
    double f = 500; // in hertz

// Perform the calculations
    double fc = calculateCutoffFrequency(R, C);
    double G = calculateGain(f, fc);
    double A = calculateAttenuation(f, fc);
	double calculatedR = calculateResistor(fc, C);
    double calculatedC = calculateCapacitor(fc, R);
	double calculatedL = calculateInductance(fc, C);

// Print the results
    printf("Cutoff Frequency: %f Hz\n", fc);
    printf("Gain: %f\n", G);
    printf("Attenuation: %f dB\n", A);
	printf("Calculated Resistor: %f ohms\n", calculatedR);
    printf("Calculated Capacitor: %e farads\n", calculatedC);
	printf("Calculated Inductance: %e henrys\n", calculatedL);
    return 0;
}