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

#define TARGET_VALUE 64
#define TOLERANCE 0.000001

// Function to calculate the value of the equation
double func(double x) {
    return x * x - TARGET_VALUE;
}

// Function to calculate the derivative of the equation
double derivFunc(double x) {
    return 2 * x;
}

// Implementation of the Newton-Raphson method
double newtonRaphson(double x, int maxIterations, double tolerance) {
    double prev_x = x;
    for (int i =  0; i < maxIterations; i++) {
        if (derivFunc(x) ==  0) {
            printf("Derivative is zero, cannot proceed.\n");
            return x; // Return the last valid guess
        }
        double h = func(x) / derivFunc(x);
        prev_x = x;
        x = x - h;
        printf("Iteration %d, x = %lf, f(x) = %lf\n", i +  1, x, func(x));
        if (fabs(x - prev_x) < tolerance) {
            printf("Converged after %d iterations.\n", i +  1);
            break;
        }
    }
    return x;
}

int main() {

    double initialGuess;
    int maxIterations;
	double targetValue;

	printf("This program calculates the square root of %d using the Newton-Raphson method.\n", TARGET_VALUE);

    // Prompt the user for the initial guess
    printf("Enter initial guess: ");
    if (scanf("%lf", &initialGuess) != 1) {
        printf("Invalid input for initial guess.\n");
        return 1;
    }
    // Prompt the user for the maximum number of iterations
    printf("Enter maximum number of iterations: ");
    if (scanf("%d", &maxIterations) != 1) {
        printf("Invalid input for maximum number of iterations.\n");
        return 1;
    }

	double tolerance =  0.0001;

    // Call the Newton-Raphson method and print the result
    double root = newtonRaphson(initialGuess, maxIterations, tolerance);
	if (!isnan(root)) {
    	printf("Approximate root: %lf\n", root);
	} else {
   		printf("Failed to find a root.\n");
	}

    return 0;
}
