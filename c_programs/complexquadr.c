// File:   complexquadr.c
// Author: Gregory K. Bowne
// Date:   14 1999
// Time:   9:48:45
// Brief:  This C program calculates the roots of a complex quadratic equation based on user-provided coefficients.
// It utilizes the complex.h and math.h libraries to handle complex number operations and calculate the discriminant.
// The user is prompted to input the real and imaginary parts of the coefficients, and the program then computes
// the discriminant and the complex roots using the quadratic formula. If the user enters invalid input,
// the program provides a clear error message and prompts for correct input.

#include <complex.h>
#include <math.h>
#include <stdio.h>

void clearInputBuffer()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
	}
}

// Function to read complex number coefficients
int readCoefficients(const char *prompt, double complex *coefficient)
{
	double real, imag;
	printf("%s", prompt);
	while (scanf("%lf %lf", &real, &imag) != 2)
	{
		printf("Invalid input. Please enter complex numbers in the format: real imaginary\n");
		clearInputBuffer();
	}
	*coefficient = real + imag * I;
	clearInputBuffer();
	return 0;
}
// Function to calculate the discriminant
double complex calculateDiscriminant(double complex a, double complex b, double complex c)
{
	return cpow(b, 2) - 4.0 * a * c;
}

// Function to calculate the roots
void calculateRoots(double complex a, double complex b, double complex discriminant, double complex *root1, double complex *root2)
{
	*root1 = (-b + csqrt(discriminant)) / (2.0 * a);
	*root2 = (-b - csqrt(discriminant)) / (2.0 * a);
}

int main()
{
	double complex a, b, c;
	double complex root1, root2, discriminant;
	double realPart, imagPart;

	printf("Complex Quadratic Root Calculator\n");
	printf("Please enter complex numbers in the format: real imaginary\n");

	// Loop to get coefficients with input validation
    while (1) {
        printf("Enter the real and imaginary parts of the first complex number (a): ");
        if (scanf("%lf %lf", &realPart, &imagPart) != 2) {
            printf("Invalid input. Please enter two numbers (real and imaginary).\n");
            clearInputBuffer();
            continue;
        }
        a = realPart + imagPart * I;
        break;
    }

    while (1) {
        printf("Enter the real and imaginary parts of the second complex number (b): ");
        if (scanf("%lf %lf", &realPart, &imagPart) != 2) {
            printf("Invalid input. Please enter two numbers (real and imaginary).\n");
            clearInputBuffer();
            continue;
        }
        b = realPart + imagPart * I;
        break;
    }

    while (1) {
        printf("Enter the real and imaginary parts of the third complex number (c): ");
        if (scanf("%lf %lf", &realPart, &imagPart) != 2) {
            printf("Invalid input. Please enter two numbers (real and imaginary).\n");
            clearInputBuffer();
            continue;
        }
        c = realPart + imagPart * I;
        break;
    }

	// Check for division by zero (a cannot be zero)
    if (creal(a) == 0.0 && cimag(a) == 0.0) {
        printf("Error: The coefficient 'a' cannot be zero.\n");
        return 1;
    }

	// Calculate the discriminant
	discriminant = calculateDiscriminant(a, b, c);

	// Calculate the roots
	calculateRoots(a, b, discriminant, &root1, &root2);


	readCoefficients("Enter the real and imaginary parts of the first complex number (a): ", &a);
	readCoefficients("Enter the real and imaginary parts of the second complex number (b): ", &b);
	readCoefficients("Enter the real and imaginary parts of the third complex number (c): ", &c);

	// Display the roots
	printf("Root  1 = %f + %fi\n", creal(root1), cimag(root1));
	printf("Root  2 = %f + %fi\n", creal(root2), cimag(root2));

	return 0;
}