// Filename: quadraticsolv.c
// Author: Gregory K. Bowne 
// Date: 12 NOV 2024
// Brief: This code is a simple C program for calculating the roots of a quadratic equation of the form:
// ax2+bx+c=0 and takes 3 coefficients as inputs.
// It calculates the discriminant (b2−4acb^2 - 4ac) to determine the nature of the roots

#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double discriminant, realPart, imaginaryPart;
    double root1, root2;

    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 || a == 0) {
        printf("Invalid input.\n");
        return 1;
    }

    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Roots are real and different: %.2f and %.2f\n", root1, root2);
    } else if (discriminant == 0) {
        root1 = -b / (2 * a);
        printf("Roots are real and same: %.2f\n", root1);
    } else {
        realPart = -b / (2 * a);
        imaginaryPart = sqrt(-discriminant) / (2 * a);
        printf("Roots are complex and different: %.2f + %.2fi and %.2f - %.2fi\n", realPart, imaginaryPart, realPart, imaginaryPart);
    }

    return 0;
}
