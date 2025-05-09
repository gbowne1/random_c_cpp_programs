// File:   complexquadr.c
// Author: Gregory K. Bowne
// Date:   March 14, 1999
// Brief:  This C program calculates the roots of a complex quadratic equation 
//         based on user-provided coefficients using complex number operations.

#include <stdio.h>
#include <math.h>
#include <complex.h>

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Function to read complex number coefficients from the user
int readCoefficients(const char *prompt, double complex *coefficient) {
    double real, imag;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf %lf", &real, &imag) == 2) {
            *coefficient = real + imag * I;
            clearInputBuffer();
            return 0;
        } else {
            printf("Invalid input. Please enter complex numbers in the format: real imaginary\n");
            clearInputBuffer();
        }
    }
}

// Function to calculate the discriminant
double complex calculateDiscriminant(double complex a, double complex b, double complex c) {
    return cpow(b, 2) - 4.0 * a * c;
}

// Function to calculate the roots of the quadratic equation
void calculateRoots(double complex a, double complex b, double complex discriminant,
                    double complex *root1, double complex *root2) {
    if (root1)
        *root1 = (-b + csqrt(discriminant)) / (2.0 * a);
    if (root2)
        *root2 = (-b - csqrt(discriminant)) / (2.0 * a);
}

const char* classifyCoefficients(double complex a, double complex b, double complex c) {
    int a_real = (cimag(a) == 0.0);
    int b_real = (cimag(b) == 0.0);
    int c_real = (cimag(c) == 0.0);

    int a_imag = (creal(a) == 0.0) && (cimag(a) != 0.0);
    int b_imag = (creal(b) == 0.0) && (cimag(b) != 0.0);
    int c_imag = (creal(c) == 0.0) && (cimag(c) != 0.0);

    if (a_real && b_real && c_real)
        return "Real coefficients";
    if (a_real && b_real && !c_real)
        return "Real coefficients with complex constant";
    if (a_real && b_real && c_real) {
        double disc = creal(cpow(b, 2)) - 4 * creal(a) * creal(c);
        if (disc >= 0)
            return "Real coefficients with distinct real roots";
        else
            return "Real coefficients with complex roots";
    }
    if (a_imag && b_imag && c_imag)
        return "Purely imaginary coefficients";
    if (!a_real || !b_real || !c_real)
        return "Mixed real and imaginary coefficients";
    return "Unknown type";
}

int main() {
    double complex a, b, c;
    double complex root1, root2, discriminant;

    printf("=== Complex Quadratic Root Calculator ===\n");
    printf("Please enter each complex coefficient as two space-separated numbers:\n");
    printf("Format: real_part imaginary_part (e.g., 2 3 for 2 + 3i)\n\n");

    // Read coefficients
    readCoefficients("Enter coefficient a (real imaginary): ", &a);
    if (creal(a) == 0.0 && cimag(a) == 0.0) {
        printf("Error: The coefficient 'a' cannot be zero (not a quadratic equation).\n");
        return 1;
    }

    readCoefficients("Enter coefficient b (real imaginary): ", &b);
    readCoefficients("Enter coefficient c (real imaginary): ", &c);

    const char* classification = classifyCoefficients(a, b, c);
    printf("\nCoefficient Type: %s\n", classification);

    // Calculate discriminant and roots
    discriminant = calculateDiscriminant(a, b, c);
    calculateRoots(a, b, discriminant, &root1, &root2);

    // Display the results
    printf("\n--- Results ---\n");
    printf("Root 1 = %.4f + %.4fi\n", creal(root1), cimag(root1));
    printf("Root 2 = %.4f + %.4fi\n", creal(root2), cimag(root2));

    return 0;
}
