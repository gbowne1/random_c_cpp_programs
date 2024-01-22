// File:   voltagediv.c
// Author: Gregory K. Bowne
// Date:   10 MAY 2020
// Time:   09:54:44
// Brief:  This program calculates voltage dividers

#include <stdio.h>

int main() {
    float R1, R2, V, Vout;

    printf("Enter the first resistance (R1) in ohms: ");
    scanf("%f", &R1);

    printf("Enter the second resistance (R2) in ohms: ");
    scanf("%f", &R2);

    printf("Enter the total voltage (V) in volts: ");
    scanf("%f", &V);

    Vout = (R2 / (R1 + R2)) * V;

    printf("The output voltage (Vout) is %.2f volts.\n", Vout);

    return 0;
}