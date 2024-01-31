// File:   tempconvert.c
// Author: Gregory K. Bowne
// Date:   14 JUN 2002
// Time:   13:56:21
// Brief:  This program that can convert C to F and F to C

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to convert Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Function to convert Fahrenheit to Celsius
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

// Function to convert Celsius to Kelvin
double celsiusToKelvin(double celsius) {
    return celsius + 273.15;
}

// Function to convert Kelvin to Celsius
double kelvinToCelsius(double kelvin) {
    return kelvin - 273.15;
}

int main() {
    double tempC, tempF, tempK;
    char choice;

    printf("Enter temperature in Celsius or Fahrenheit or Kelvin (C/F/K): ");
    scanf(" %c", &choice);
    choice = toupper(choice);

    switch (choice) {
        case 'C':
            printf("Enter temperature in Celsius: ");
            scanf("%lf", &tempC);
            tempF = celsiusToFahrenheit(tempC);
            tempK = celsiusToKelvin(tempC);
            printf("%.2lf degrees Celsius is %.2lf degrees Fahrenheit, %.2lf degrees Kelvin.\n", tempC, tempF, tempK);
            break;
        case 'F':
            printf("Enter temperature in Fahrenheit: ");
            scanf("%lf", &tempF);
            tempC = fahrenheitToCelsius(tempF);
            tempK = celsiusToKelvin(fahrenheitToCelsius(tempF));
            printf("%.2lf degrees Fahrenheit is %.2lf degrees Celsius, %.2lf degrees Kelvin.\n", tempF, tempC, tempK);
            break;
        case 'K':
            printf("Enter temperature in Kelvin: ");
            scanf("%lf", &tempK);
            tempC = kelvinToCelsius(tempK);
            tempF = celsiusToFahrenheit(kelvinToCelsius(tempK));
            printf("%.2lf degrees Kelvin is %.2lf degrees Celsius, %.2lf degrees Fahrenheit.\n", tempK, tempC, tempF);
            break;
        default:
            printf("Invalid choice!\n");
            exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
