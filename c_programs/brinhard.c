// File:   brinhard.c
// Author: Gregory K. Bowne
// Date:   18 OCT 2024 (Updated 09 MAY 2025)
// Brief:  Calculates Brinell hardness (HB) and related values. Includes standard validation.
// Update: to add standards compliance checks for ASTM E10 / ISO 6506.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>
#include <limits.h>

#define M_PI 3.14159265358979323846

/**
 * @brief Calculates Brinell hardness.
 *
 * @param P Applied load in kgf.
 * @param D Diameter of the ball in mm.
 * @param d Diameter of the indentation in mm.
 * @return Brinell hardness value or -1.0 on error.
 */
double calculate_brinnell_hardness(double P, double D, double d) {
    if (P <= 0 || D <= 0 || d <= 0 || d >= D) {
        fprintf(stderr, "Error: Invalid input. P, D, and d must be greater than 0, and d < D.\n");
        return -1.0;
    }

    return (2 * P) / (M_PI * D * (D - sqrt(D * D - d * d)));
}

/**
 * @brief Reads a double value from user with validation.
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

        if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
            printf("Invalid input. Please enter a valid number.\n");
        } else if (value < 0 || value > DBL_MAX) {
            printf("Value out of range. Please enter a positive number.\n");
        } else {
            break;
        }
    }

    return value;
}

/**
 * @brief Prints detailed calculation summary.
 */
void print_summary(double P, double D, double d, double HB) {
    double A = M_PI * D * (D - sqrt(D * D - d * d));
    double HB_MPa = HB * 9.80665;
    double h = (D - sqrt(D * D - d * d)) / 2;

    printf("\n--- Brinell Hardness Calculation Summary ---\n");
    printf("Applied Load (P):           %.15f kgf\n", P);
    printf("Ball Diameter (D):          %.15f mm\n", D);
    printf("Indentation Diameter (d):   %.15f mm\n", d);
    printf("Indentation Depth (h):      %.15f mm\n", h);
    printf("Contact Area (A):           %.15f mm^2\n", A);
    printf("Brinell Hardness (HB):      %.15f kgf/mm^2\n", HB);
    printf("Brinell Hardness (MPa):     %.15f MPa\n", HB_MPa);
}

/**
 * @brief Validates inputs against ASTM E10 / ISO 6506 recommended limits.
 */
void validate_against_standards(double P, double D, double d) {
    double d_D_ratio = d / D;
    printf("\n--- Standards Validation (ASTM E10 / ISO 6506) ---\n");
    printf("Indentation to Ball Ratio (d/D): %.5f\n", d_D_ratio);

    if (d_D_ratio < 0.24 || d_D_ratio > 0.6) {
        printf("WARNING: d/D ratio out of recommended range [0.24–0.6] per ASTM E10.\n");
    } else {
        printf("PASS: d/D ratio within ASTM E10 / ISO 6506 recommended limits.\n");
    }

    // TODO: Add more checks for P/D² range per material class, if needed.
}

/**
 * @brief Main program entry point.
 */
int main(void) {
    double P, D, d;

    P = read_double("Enter the applied load (P) in kgf: ");
    D = read_double("Enter the diameter of the ball (D) in mm: ");
    d = read_double("Enter the diameter of the indentation (d) in mm: ");

    double HB = calculate_brinnell_hardness(P, D, d);
    if (HB < 0) return EXIT_FAILURE;

    print_summary(P, D, d, HB);
    validate_against_standards(P, D, d);

    return EXIT_SUCCESS;
}
