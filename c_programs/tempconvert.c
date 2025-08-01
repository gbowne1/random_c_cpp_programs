/* File:   tempconvert.c
 * Author: Gregory K. Bowne
 * Date:   14 JUN 2002
 * Time:   13:56:21
 * Brief:  A temperature conversion program (Celsius, Fahrenheit, Kelvin)
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

/* Configuration */
#define MAX_INPUT_LENGTH 100
#define PRECISION 15
#define KELVIN_OFFSET 273.15

/* ANSI Color Codes */
#define COLOR_RESET  "\033[0m"
#define COLOR_RED    "\033[1;31m"
#define COLOR_GREEN  "\033[1;32m"
#define COLOR_YELLOW "\033[1;33m"
#define COLOR_CYAN   "\033[1;36m"

/* Function prototypes */
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
            printf(COLOR_RED "Invalid input. Exiting program.\n" COLOR_RESET);
            return EXIT_FAILURE;
        }

        if (choice == 4) {
            printf(COLOR_GREEN "Exiting program. Goodbye!\n" COLOR_RESET);
            break;
        }

        printf(COLOR_CYAN "Enter temperature value: " COLOR_RESET);
        if (!getValidTemperature(&inputTemp)) {
            printf(COLOR_RED "Invalid temperature input. Exiting program.\n" COLOR_RESET);
            return EXIT_FAILURE;
        }

        if (choice == 3 && inputTemp < 0.0) {
            printf(COLOR_RED "Error: Kelvin cannot be negative.\n" COLOR_RESET);
            continue;
        }

        convertTemperature(choice, inputTemp);

        printf("\nDo you want to perform another conversion? (y/n): ");
        char response[MAX_INPUT_LENGTH];
        if (!fgets(response, sizeof(response), stdin)) {
            break;
        }

        if (tolower(response[0]) != 'y') {
            continueProgram = false;
        }
    }

    return EXIT_SUCCESS;
}

void displayMenu(void) {
    printf(COLOR_YELLOW "\nTemperature Conversion Menu\n" COLOR_RESET);
    printf("1. Convert Celsius to Fahrenheit and Kelvin\n");
    printf("2. Convert Fahrenheit to Celsius and Kelvin\n");
    printf("3. Convert Kelvin to Celsius and Fahrenheit\n");
    printf("4. Exit\n");
    printf("Enter your choice (1-4): ");
}

bool getValidChoice(int *choice) {
    char buffer[MAX_INPUT_LENGTH];

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            return false;
        }

        if (sscanf(buffer, "%d", choice) != 1 || *choice < 1 || *choice > 4) {
            printf(COLOR_RED "Invalid choice. Please enter a number between 1 and 4: " COLOR_RESET);
        } else {
            return true;
        }
    }
}

bool getValidTemperature(double *temp) {
    char buffer[MAX_INPUT_LENGTH];

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            return false;
        }

        if (sscanf(buffer, "%lf", temp) != 1) {
            printf(COLOR_RED "Invalid temperature. Please enter a valid number: " COLOR_RESET);
        } else {
            return true;
        }
    }
}

void convertTemperature(int choice, double inputTemp) {
    double celsius, fahrenheit, kelvin;

    switch (choice) {
        case 1:
            fahrenheit = celsiusToFahrenheit(inputTemp);
            kelvin = celsiusToKelvin(inputTemp);
            printf(COLOR_GREEN "%.*f°C = %.*f°F, %.*f K\n" COLOR_RESET,
                   PRECISION, inputTemp, PRECISION, fahrenheit, PRECISION, kelvin);
            break;
        case 2:
            celsius = fahrenheitToCelsius(inputTemp);
            kelvin = celsiusToKelvin(celsius);
            printf(COLOR_GREEN "%.*f°F = %.*f°C, %.*f K\n" COLOR_RESET,
                   PRECISION, inputTemp, PRECISION, celsius, PRECISION, kelvin);
            break;
        case 3:
            if (inputTemp < 0.0) {
                printf(COLOR_RED "Kelvin temperature cannot be negative.\n" COLOR_RESET);
                return;
            }
            celsius = kelvinToCelsius(inputTemp);
            fahrenheit = celsiusToFahrenheit(celsius);
            printf(COLOR_GREEN "%.*f K = %.*f°C, %.*f°F\n" COLOR_RESET,
                   PRECISION, inputTemp, PRECISION, celsius, PRECISION, fahrenheit);
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
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */ 
    }
}
