// File:   sqrtnewtonl.c
// Author: Gregory K. Bowne
// Date:   11 MAR 1999
// Time:   11:28:21
// Brief:  The Newton-Raphson method is an iterative technique for finding the roots of a real-valued function.
// It starts with an initial guess and then refines the estimate by finding the point where the tangent line to
// the graph of the function crosses the x-axis. This process is repeated until a sufficiently accurate result
// is obtained. The method is fast and easy to implement on a computer, making it useful for solving non-linear
// equations and systems of non-linear equations. However, it requires the derivative of the function and may
// become complicated if the derivative is not simple

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the value of the equation
double func(double x) {
    return x * x - 64; // Example function x^2 - 64
}

// Function to calculate the derivative of the equation
double derivFunc(double x) {
    return 2 * x; // Derivative of x^2 - 64
}

// Implementation of the Newton-Raphson method
double newtonRaphson(double x, int maxIterations) {
    for (int i = 0; i < maxIterations; i++) {
        // Check if the derivative is zero to avoid division by zero
        if (derivFunc(x) == 0) {
            printf("Derivative is zero, cannot proceed.\n");
            exit(0);
        }
        // Update the guess using the Newton-Raphson formula
        x = x - func(x) / derivFunc(x);
		printf("Iteration %d, x = %lf, f(x) = %lf\n", i + 1, x, func(x));
    }
    return x;
}

int main() {
    double initialGuess;
    int maxIterations;

    // Prompt the user for the initial guess
    printf("Enter initial guess: ");
    scanf("%lf", &initialGuess);

    // Prompt the user for the maximum number of iterations
    printf("Enter maximum number of iterations: ");
    scanf("%d", &maxIterations);

    // Call the Newton-Raphson method and print the result
    double root = newtonRaphson(initialGuess, maxIterations);
    printf("Approximate root: %lf\n", root);

    return 0;
}
