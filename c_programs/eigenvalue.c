#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define MAX_ITERATIONS 100

int main()
{
    float x_new[SIZE] = {0.0};
    float a[SIZE][SIZE], x[SIZE];
    float lambda_old = 0, lambda_new = 1, error, temp;
    int i, j, n, step = 1, largest_index;

    // Input the order of the matrix
    printf("Enter Order of Matrix (max %d): ", SIZE);
    scanf("%d", &n);

    // Check if the matrix size exceeds the maximum allowed size
    if (n > SIZE || n <= 0)
    {
        printf("Matrix size is invalid or exceeds the maximum allowed size.\n");
        return 1;
    }

    // Input the matrix elements
    printf("Enter Coefficient Matrix (%dx%d):\n", n, n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("a[%d][%d] = ", i, j);
            scanf("%f", &a[i][j]);
        }
    }

    // Input the initial guess vector
    printf("Enter Initial Guess Vector of size %d:\n", n);
    for (i = 0; i < n; i++)
    {
        printf("x[%d] = ", i);
        scanf("%f", &x[i]);
    }

    // Input the tolerable error
    printf("Enter Tolerable Error: ");
    scanf("%f", &error);

    // Power Method Loop
    for (step = 1; step <= MAX_ITERATIONS && fabs((lambda_new - lambda_old) / lambda_new) >= error; step++)
    {
        // Matrix-vector multiplication: x_new = A * x
        for (i = 0; i < n; i++)
        {
            temp = 0.0;
            for (j = 0; j < n; j++)
            {
                temp += a[i][j] * x[j];
            }
            x_new[i] = temp;
        }

        // Find the index of the largest absolute value in x_new
        largest_index = 0;
        for (i = 1; i < n; i++)
        {
            if (fabs(x_new[i]) > fabs(x_new[largest_index]))
            {
                largest_index = i;
            }
        }

        // Update eigenvalue estimate
        lambda_old = lambda_new;
        lambda_new = fabs(x_new[largest_index]);

        // Normalize vector
        for (i = 0; i < n; i++)
        {
            x[i] = x_new[i] / lambda_new;
        }

        // Print intermediate results
        printf("\nSTEP %d:\n", step);
        printf("Eigenvalue ≈ %f\n", lambda_new);
        printf("Eigenvector: ");
        for (i = 0; i < n; i++)
        {
            printf("%f ", x[i]);
        }
        printf("\n");
    }

    // Final output
    printf("\nFinal Result After %d Iterations:\n", step - 1);
    printf("Estimated Dominant Eigenvalue: %f\n", lambda_new);
    printf("Corresponding Eigenvector:\n");
    for (i = 0; i < n; i++)
    {
        printf("%f ", x[i]);
    }
    printf("\n");

    return 0;
}
