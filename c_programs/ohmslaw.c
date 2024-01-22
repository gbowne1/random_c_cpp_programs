// File:   ohmslaw.c
// Author: Gregory K. Bowne
// Date:   10 MAY 2020
// Time:   09:54:44
// Brief:  This program calculates ohms law, becuase we can and we have the technology

#include <stdio.h>

int main() {
    float I, R, V;

    printf("Enter the current (I) in amperes: ");
    scanf("%f", &I);

    printf("Enter the resistance (R) in ohms: ");
    scanf("%f", &R);

    V = I * R;

    printf("The voltage (V) is %.2f volts.\n", V);

    return 0;
}
