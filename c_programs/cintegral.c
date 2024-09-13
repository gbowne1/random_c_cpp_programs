#include <stdio.h>

double integrate_2x(double x) {
    return x * x; // Antiderivative of 2x is x^2
}

int main() {
    double lower_bound = 10.0;
    double upper_bound = 13.0;

    double result = integrate_2x(upper_bound) - integrate_2x(lower_bound);

    printf("The definite integral of 2x dx from 10 to 13 is: %.2f\n", result);

    return 0;
}
