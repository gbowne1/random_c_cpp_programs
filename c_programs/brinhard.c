// File:   brinhard.c
// Author: Gregory K. Bowne
// Date:   18 OCT 2024
// Time:   14:22:35
// Brief:  This program calculates Brinell hardness given applied load, ball diameter and indentation diameter.

/**
 * @file brinell_hardness.c
 * @brief Calculates Brinell hardness given applied load, ball diameter, and indentation diameter.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <limits.h>

// Define constant for pi
#define M_PI 3.14159265358979323846

/**
 * @brief Calculates Brinell hardness.
 *
 * @param P Applied load in kgf.
 * @param D Diameter of the ball in mm.
 * @param d Diameter of the indentation in mm.
 *
 * @return Brinell hardness value or -1.0 on error.
 */
double calculate_brinnell_hardness(double P, double D, double d) {
    // Check for invalid input
    if (P <= 0 || D <= 0 || d <= 0 || d >= D) {
        fprintf(stderr, "Error: Invalid input. P, D, and d must be greater than 0, and d must be less than D.\n");
        return -1.0;
    }
    
    // Calculate Brinell hardness
    return (2 * P) / (M_PI * D * (D - sqrt(D * D - d * d)));
}

/**
 * @brief Safely reads a double value from the user.
 *
 * @param prompt Prompt to display to the user.
 *
 * @return The read double value.
 */
double read_double(const char *prompt) {
    double value;
    char input[100];

    while (true) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error: Failed to read input.\n");
            exit(EXIT_FAILURE);
        }

        char *endptr;
        value = strtod(input, &endptr);

        // Check for invalid input
        if (endptr == input || *endptr != '\n') {
            printf("Invalid input. Please enter a valid number.\n");
        } else if (value < 0 || value > DBL_MAX) {
            printf("Value out of range. Please enter a positive number.\n");
        } else {
            break;
        }
    }

    return value;
}

int main(void) {
    double P, D, d;

    // Input values
    P = read_double("Enter the applied load (P) in kgf: ");
    D = read_double("Enter the diameter of the ball (D) in mm: ");
    d = read_double("Enter the diameter of the indentation (d) in mm: ");

    // Calculate Brinell hardness
    double HB = calculate_brinnell_hardness(P, D, d);

    // Output the result
    if (HB < 0) {
        return EXIT_FAILURE;
    }
    printf("Brinell Hardness (HB) = %.2f\n", HB);

    return EXIT_SUCCESS;
}