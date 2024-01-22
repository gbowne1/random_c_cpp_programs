// File:   gageblockstack.c
// Author: Gregory K. Bowne
// Date:   17 Mar 2020
// Time:   09:54:22
// Brief:  This program calculates the necessary gage block stack to give a resulting angle when used with a sine bar.
//         This also useful in a metalworking or machining environment.

#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

int main() {
    double angle; // Angle in decimal degrees
    double sineBarLength; // Length of the sine bar in inches
    double height; // Height in inches

    printf("Enter the angle (in decimal degrees): ");
    scanf("%lf", &angle);

    printf("Enter the length of the sine bar (in inches): ");
    scanf("%lf", &sineBarLength);

    // Convert the angle to radians
    angle = angle * M_PI / 180.0;

    // Calculate the height
    height = sineBarLength * sin(angle);

    printf("Required gage block stack height: %.4lf inches\n", height);

    return 0;
}