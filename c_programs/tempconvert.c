// File:   tempconvert.c
// Author: Gregory K. Bowne
// Date:   14 JUN 2002
// Time:   13:56:21
// Brief:  This program that can convert C to F and F to C

#include <stdio.h>
#include <stdlib.h>

// Function to convert Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

// Function to convert Fahrenheit to Celsius
double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

int main() {
    double tempC, tempF;
    char choice;

    printf("Enter temperature in Celsius or Fahrenheit (C/F): ");
    scanf(" %c", &choice);

    if (choice == 'C' || choice == 'c') {
        printf("Enter temperature in Celsius: ");
        scanf("%lf", &tempC);
        tempF = celsiusToFahrenheit(tempC);
        printf("%.2lf degrees Celsius is %.2lf degrees Fahrenheit.\n", tempC, tempF);
    } else if (choice == 'F' || choice == 'f') {
        printf("Enter temperature in Fahrenheit: ");
        scanf("%lf", &tempF);
        tempC = fahrenheitToCelsius(tempF);
        printf("%.2lf degrees Fahrenheit is %.2lf degrees Celsius.\n", tempF, tempC);
    } else {
        printf("Invalid choice!\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}