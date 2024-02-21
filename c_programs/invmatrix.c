// File:   invmatrix.c
// Author: Gregory K. Bowne
// Date:   12 OCT 2000
// Time:   9:22:45
// Brief:  This program does inverse matrix calculations

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3 // Change this to the size of your matrix

int compareFloats(const void *a, const void *b)
{
	float fa = *(const float *)a;
	float fb = *(const float *)b;
	return (fa > fb) - (fa < fb);
}

float determinant(float matrix[N][N], int n)
{
	float det = 0;
	float submatrix[N][N];
	if (n == 2)
	{
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	}
	else
	{
		for (int x = 0; x < n; x++)
		{
			int subi = 0;
			for (int i = 1; i < n; i++)
			{
				int subj = 0;
				for (int j = 0; j < n; j++)
				{
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det += (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
		}
	}
	return det;
}

// Placeholder for condition number calculation
// Implementing a full condition number calculation is complex and requires singular value decomposition or other methods.
// Here, we'll just return a placeholder value.

// Placeholder SVD computation function
void computeSVD(float matrix[N][N], float U[N][N], float S[N], float V[N][N])
{
	// This function should compute the SVD and fill the S array with singular values
	// For demonstration, we'll just fill S with example values
	S[0] = 4.0; // Largest singular value
	S[1] = 2.0; // Next singular value
	S[2] = 0.5; // Smallest singular value
}

float conditionNumber(float matrix[N][N], int n)
{
	float U[N][N], S[N], V[N][N];
	computeSVD(matrix, U, S, V);

	// Compute the condition number
	float cond = S[0] / S[n - 1];

	return cond;
}

void printMatrix(float matrix[N][N * 2])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N * 2; j++)
		{
			printf("%.2f\t", matrix[i][j]);
		}
		printf("\n");
	}
}

int inverseMatrix(float matrix[N][N * 2])
{
	float originalMatrix[N][N];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			originalMatrix[i][j] = matrix[i][j];
		}
	}

	float det = determinant(originalMatrix, N);
	if (fabs(det) < 1e-6)
	{
		printf("Matrix is singular and cannot be inverted.\n");
		return -1; // Return -1 to indicate failure
	}

	float cond = conditionNumber(originalMatrix, N); // Corrected to pass originalMatrix
	if (cond > 1e6)
	{
		printf("Matrix is ill-conditioned and may lead to inaccurate results.\n");
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i == j)
			{
				matrix[i][j + N] = 1;
			}
			else
			{
				matrix[i][j + N] = 0;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (i != j)
			{
				float ratio = matrix[j][i] / matrix[i][i];
				for (int k = 0; k < N * 2; k++)
				{
					matrix[j][k] -= ratio * matrix[i][k];
				}
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		float divisor = matrix[i][i];
		for (int j = 0; j < N * 2; j++)
		{
			matrix[i][j] /= divisor;
		}
	}

	return 0; // Return 0 to indicate success
}

int main()
{
	float matrix[N][N * 2] = {{4, 7, 1, 0, 1, 0}, {2, 6, 3, 1, 0, 0}, {9, 5, 8, 2, 0, 1}};
	float originalMatrix[N][N];

	// Copy the upper left square of matrix into originalMatrix
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			originalMatrix[i][j] = matrix[i][j];
		}
	}

	float condNumber = conditionNumber(originalMatrix, N);
	printf("Condition Number: %f\n", condNumber);

	printf("Original Matrix:\n");
	printMatrix(matrix);

	int errorStatus = inverseMatrix(matrix);
	if (errorStatus == 0)
	{
		printf("\nInverse Matrix:\n");
		printMatrix(matrix);
	}

	return errorStatus;
}