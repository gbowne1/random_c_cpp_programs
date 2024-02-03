// File:   eigenvalue.c
// Author: Gregory K. Bowne
// Date:   12 OCT 2015
// Time:   9:01:22
// Brief:  This program does Eigenvalue in C

#include <stdio.h>
#include <math.h>

#define SIZE 10

int main() {
    float a[SIZE][SIZE], x[SIZE], x_new[SIZE];
    float lambda_old = 0, lambda_new = 1, error, temp;
    int i, j, n, step = 1;

    // Input the order of the matrix
    printf("Enter Order of Matrix: ");
    scanf_s("%d", &n);

    // Input the matrix elements
    printf("Enter Coefficient of Matrix:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            printf("a=%d ", i);
            scanf_s("%f", &a[i][j]);
        }
    }

    // Input the initial guess vector
    printf("Enter Initial Guess Vector:\n");
    for (i = 1; i <= n; i++) {
        printf("x=%d ", i);
        scanf_s("%f", &x[i]);
    }

    // Input the tolerable error
    printf("Enter Tolerable Error: ");
    scanf_s("%f", &error);

    while (fabs(lambda_new - lambda_old) > error) {
        // Matrix-vector multiplication
        for (i = 1; i <= n; i++) {
            temp = 0.0;
            for (j = 1; j <= n; j++) {
                temp = temp + a[i][j] * x[j];
            }
            x_new[i] = temp;
        }

        // Finding largest element of x_new
        lambda_new = fabs(x_new[1]);
        for (i = 2; i <= n; i++) {
            if (fabs(x_new[i]) > lambda_new) {
                lambda_new = fabs(x_new[i]);
            }
        }

        // Normalization
        for (i = 1; i <= n; i++) {
            x[i] = x_new[i] / lambda_new;
        }

        // Display intermediate results
        printf("\n\nSTEP-%d:\n", step);
        printf("Eigen Value = %f\n", lambda_new);
        printf("Eigen Vector: ");
        for (i = 1; i <= n; i++) {
            printf("%f ", x[i]);
        }

        lambda_old = lambda_new;
        step++;
    }

    // Display the final result
    printf("\n\nThe required eigen value is %f", lambda_new);
    printf("\n\nThe required eigen vector is:\n");
    for (i = 1; i <= n; i++) {
        printf("%f ", x[i]);
    }

    return 0;
}