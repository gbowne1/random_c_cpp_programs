#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void inverseMatrix(int n, float a[n][n], float inverse[n][n]);
bool doMatricesCommute(int n, float a[n][n], float b[n][n]);
void addMatrices(int n, float a[n][n], float b[n][n], float result[n][n]);
bool compareMatrices(int n, float a[n][n], float b[n][n]);
float determinant(int n, float a[n][n]);

void initializeIdentityMatrix(int n, float identity[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				identity[i][j] = 1.0;
			}
			else
			{
				identity[i][j] = 0.0;
			}
		}
	};
}
// Function to calculate the inverse of a matrix
void inverseMatrix(int n, float a[n][n], float inverse[n][n])
{
	float det = determinant(n, a);
	if (det == 0)
	{
		printf("Matrix is singular and cannot be inverted.\n");
		return;
	}

	float *adjugate = (float *)malloc(n * n * sizeof(float));
	if (adjugate == NULL)
	{
		printf("Memory allocation failed.\n");
		return;
	}

	// Initialize adjugate using the allocated memory
	// Fill adjugate with values

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			inverse[i][j] = adjugate[i * n + j] / det;
		}
	}

	free(adjugate);
}

// Function to check if two matrices commute
bool doMatricesCommute(int n, float a[n][n], float b[n][n])
{
	float ab[n][n], ba[n][n];
	float result_ab[n][n], result_ba[n][n];

	// Multiply A * B
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result_ab[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				result_ab[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	// Multiply B * A
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result_ba[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				result_ba[i][j] += b[i][k] * a[k][j];
			}
		}
	}

	return compareMatrices(n, result_ab, result_ba);
}

// Function to add two matrices
void addMatrices(int n, float a[n][n], float b[n][n], float result[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result[i][j] = a[i][j] + b[i][j];
		}
	}
}

// Function to compare two matrices
bool compareMatrices(int n, float a[n][n], float b[n][n])
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] != b[i][j])
			{
				return false;
			}
		}
	}
	return true;
}

int main()
{
	const int n = 3; // Example size of the matrix
	float a[n][n];	 // Placeholder for matrix A
	float b[n][n];	 // Placeholder for matrix B
	float a_inv[n][n], b_inv[n][n], sum_inv[n][n], sum[n][n], inv_sum[n][n];

	// Assume matrices a and b are filled with values here

	// Calculate inverses of A and B
	inverseMatrix(n, a, a_inv);
	inverseMatrix(n, b, b_inv);

	// Check if A and B commute
	if (doMatricesCommute(n, a, b))
	{
		// Add the inverses of A and B
		addMatrices(n, a_inv, b_inv, sum_inv);

		// Add A and B, and then calculate the inverse of the sum
		addMatrices(n, a, b, sum);
		inverseMatrix(n, sum, inv_sum);

		// Check if the sum of inverses is equal to the inverse of the sum
		if (compareMatrices(n, sum_inv, inv_sum))
		{
			printf("The matrices satisfy the condition.\n");
		}
		else
		{
			printf("The matrices do not satisfy the condition.\n");
		}
	}
	else
	{
		printf("Matrices A and B do not commute and therefore do not satisfy the condition.\n");
	}

	return 0;
}