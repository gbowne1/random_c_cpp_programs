// File:   speakerbox.c
// Author: Gregory K. Bowne
// Date:   11 NOV 2023
// Time:   13:56:21
// Brief:  This program calculates the size of a speaker box for use when building custom speaker boxes,.
//         It is open-source and can be used to understand the calculations involved in speaker box design

#include <stdio.h>

// Function to calculate the internal volume of the speaker box
double calculateInternalVolume(double width, double height, double depth, double driverDisplacement, double portDisplacement) {
    // Calculate the internal volume
    double internalVolume = (width) * (height) * (depth);
    // Adjust for driver and port displacements
    internalVolume -= driverDisplacement;
    internalVolume -= portDisplacement;
    return internalVolume;
}

int main() {
    // Input values for width, height, and depth
    double width, height, depth, driverDisplacement, portDisplacement;

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

    return 0;
}

