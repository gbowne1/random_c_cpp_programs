// Date: 30 MAR 2025
// Brief: used to calculate derivatives. allows for keyboard input or file input 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Function to dynamically evaluate user-defined functions
double evaluate_function(const char* func, double x) {
    if (strcmp(func, "2x") == 0) {
        return 2 * x; // Example: Replace this with your desired logic for "2x"
    } else if (strcmp(func, "x^2") == 0) {
        return x * x; // Example for "x^2"
    } else if (strcmp(func, "sin(x)") == 0) {
        return sin(x); // Example for "sin(x)"
    } else {
        printf("Unsupported function: %s\n", func);
        exit(1);
    }
}

// Trapezoidal rule for numerical integration
double integrate(const char* func, double lower_bound, double upper_bound, int intervals) {
    double step = (upper_bound - lower_bound) / intervals;
    double sum = 0.0;

    for (int i = 0; i <= intervals; i++) {
        double x = lower_bound + i * step;
        if (i == 0 || i == intervals) {
            sum += evaluate_function(func, x); // First and last terms
        } else {
            sum += 2 * evaluate_function(func, x); // Middle terms
        }
    }

    return (step / 2) * sum;
}

int main() {
    char func[100];
    double lower_bound, upper_bound;
    int intervals;
    char input_mode;

    printf("Enter input mode (k for keyboard, f for file): ");
    scanf(" %c", &input_mode);

    if (input_mode == 'k') {
        // Keyboard input
        printf("Enter the function (e.g., 2x, x^2, sin(x)): ");
        scanf("%s", func);
        printf("Enter the lower bound: ");
        scanf("%lf", &lower_bound);
        printf("Enter the upper bound: ");
        scanf("%lf", &upper_bound);
        printf("Enter the number of intervals: ");
        scanf("%d", &intervals);
    } else if (input_mode == 'f') {
        // File input
        char filename[100];
        printf("Enter the filename: ");
        scanf("%s", filename);
        FILE* file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error: Unable to open file.\n");
            return 1;
        }
        fscanf(file, "%s %lf %lf %d", func, &lower_bound, &upper_bound, &intervals);
        fclose(file);
    } else {
        printf("Invalid input mode.\n");
        return 1;
    }

    double result = integrate(func, lower_bound, upper_bound, intervals);

    printf("The definite integral of %s from %.2f to %.2f is: %.6f\n", func, lower_bound, upper_bound, result);

    return 0;
}
