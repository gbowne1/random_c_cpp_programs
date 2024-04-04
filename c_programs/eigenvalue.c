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
	printf("Enter Order of Matrix: ");
	scanf("%d", &n);

	// Check if the matrix size exceeds the maximum allowed size
	if (n > SIZE)
	{
		printf("Matrix size exceeds the maximum allowed size.\n");
		return 1; // Exit with an error code
	}

	// Input the matrix elements
	printf("Enter Coefficient of Matrix:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("a[%d][%d] = ", i, j);
			scanf("%f", &a[i][j]);
		}
	}

	// Input the initial guess vector
	printf("Enter Initial Guess Vector:\n");
	for (i = 0; i < n; i++)
	{
		printf("x[%d] = ", i);
		scanf("%f", &x[i]);
	}

	// Input the tolerable error
	printf("Enter Tolerable Error: ");
	scanf("%f", &error);

	// Main loop for eigenvalue computation
	for (step = 1; step <= MAX_ITERATIONS && fabs((lambda_new - lambda_old) / lambda_new) >= error; step++)
	{
		// Matrix-vector multiplication
		for (i = 0; i < n; i++)
		{
			temp = 0.0;
			largest_index = 0;
			for (j = 0; j < n; j++)
			{
				temp += a[i][j] * x[j];
				if (fabs(temp) > fabs(x_new[largest_index]))
				{
					largest_index = i;
				}
			}
			x_new[i] = temp;
		}

		// Finding largest element of x_new
		lambda_new = fabs(x_new[largest_index]);

		// Normalization
		for (i = 0; i < n; i++)
		{
			x[i] = x_new[i] / lambda_new;
		}

		// Optional: Display intermediate results (uncommented)
		printf("\n\nSTEP-%d:\n", step);
		printf("Eigen Value = %f\n", lambda_new);
		printf("Eigen Vector: ");
		for (i = 0; i < n; i++)
		{
			printf("%f ", x[i]);
		}
		printf("\n");

		lambda_old = lambda_new;
		step++;
	}

	// Display the final result
	printf("\n\nThe required eigen value is %f\n", lambda_new);
	printf("\n\nThe required eigen vector is:\n");
	for (i = 0; i < n; i++)
	{
		printf("%f ", x[i]);
	}

	return 0;
}