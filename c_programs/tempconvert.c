// File:   tempconvert.c
// Author: Gregory K. Bowne
// Date:   14 JUN 2002
// Time:   13:56:21
// Brief:  This program that can convert C to F and F to C

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 100
#define PRECISION 2
#define KELVIN_OFFSET 273.15

// Function prototypes
void displayMenu(void);
bool getValidChoice(int *choice);
bool getValidTemperature(double *temp);
void convertTemperature(int choice, double inputTemp);
double celsiusToFahrenheit(double celsius);
double fahrenheitToCelsius(double fahrenheit);
double celsiusToKelvin(double celsius);
double kelvinToCelsius(double kelvin);
void clearInputBuffer(void);

int main(void) {
    int choice;
    double inputTemp;
    bool continueProgram = true;

    while (continueProgram) {
        displayMenu();
        
        if (!getValidChoice(&choice)) {
            fprintf(stderr, "Invalid input. Exiting program.\n");
            return EXIT_FAILURE;
        }

        if (choice == 4) {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        printf("Enter temperature value: ");
        if (!getValidTemperature(&inputTemp)) {
            fprintf(stderr, "Invalid temperature input. Exiting program.\n");
            return EXIT_FAILURE;
        }

        convertTemperature(choice, inputTemp);

        printf("\nDo you want to perform another conversion? (y/n): ");
        char response;
        scanf(" %c", &response);
        continueProgram = (response == 'y' || response == 'Y');
        clearInputBuffer();
    }

    return EXIT_SUCCESS;
}

void displayMenu(void) {
    printf("\nTemperature Conversion Menu\n");
    printf("1. Convert Celsius to Fahrenheit and Kelvin\n");
    printf("2. Convert Fahrenheit to Celsius and Kelvin\n");
    printf("3. Convert Kelvin to Celsius and Fahrenheit\n");
    printf("4. Exit\n");
    printf("Enter your choice (1-4): ");
}

bool getValidChoice(int *choice) {
    if (scanf("%d", choice) != 1) {
        clearInputBuffer();
        return false;
    }
    if (*choice < 1 || *choice > 4) {
        printf("Invalid choice. Please enter a number between 1 and 4.\n");
        return getValidChoice(choice);
    }
    return true;
}

bool getValidTemperature(double *temp) {
    if (scanf("%lf", temp) != 1) {
        clearInputBuffer();
        return false;
    }
    return true;
}

void convertTemperature(int choice, double inputTemp) {
    switch (choice) {
        case 1:
            printf("%.2f°C = %.2f°F, %.2f K\n", inputTemp, 
                   celsiusToFahrenheit(inputTemp), celsiusToKelvin(inputTemp));
            break;
        case 2:
            printf("%.2f°F = %.2f°C, %.2f K\n", inputTemp, 
                   fahrenheitToCelsius(inputTemp), 
                   celsiusToKelvin(fahrenheitToCelsius(inputTemp)));
            break;
        case 3:
            printf("%.2f K = %.2f°C, %.2f°F\n", inputTemp, 
                   kelvinToCelsius(inputTemp), 
                   celsiusToFahrenheit(kelvinToCelsius(inputTemp)));
            break;
    }
}

double celsiusToFahrenheit(double celsius) {
    return (celsius * 9.0 / 5.0) + 32.0;
}

double fahrenheitToCelsius(double fahrenheit) {
    return (fahrenheit - 32.0) * 5.0 / 9.0;
}

double celsiusToKelvin(double celsius) {
    return celsius + KELVIN_OFFSET;
}

double kelvinToCelsius(double kelvin) {
    return kelvin - KELVIN_OFFSET;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}