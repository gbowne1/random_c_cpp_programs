// File:   orthagonmatrix.c
// Author: Gregory K. Bowne
// Date:   12 SEP 1998
// Time:   8:54:08
// Brief:  This program defines functions to transpose a matrix, multiply two matrices,
// and check if a matrix is an identity matrix. It uses these functions to determine if
// the given square matrix is orthogonal by checking if the product of the matrix and
// its transpose results in an identity matrix

#include <stdio.h>
#include <stdlib.h>

void transposeMatrix(int size, int matrix[][size], int transpose[][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			transpose[j][i] = matrix[i][j];
		}
	}
}

int isIdentityMatrix(int size, int matrix[][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j && matrix[i][j] != 1)
				return 0;
			if (i != j && matrix[i][j] != 0)
				return 0;
		}
	}
	return 1;
}

void multiplyMatrices(int size, int matrix1[][size], int matrix2[][size], int result[][size])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < size; k++)
			{
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}
}

int main()
{
	int size;
	printf("Enter size of square matrix (e.g., 3 for 3x3): ");
	scanf_s("%d", &size);

	int matrix[size][size], transpose[size][size], product[size][size];

	printf("Enter elements of the matrix:\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			scanf_s("%d", &matrix[i][j]);
		}
	}

	transposeMatrix(size, matrix, transpose);
	multiplyMatrices(size, matrix, transpose, product);

	if (isIdentityMatrix(size, product))
	{
		printf("The matrix is orthogonal.\n");
	}
	else
	{
		printf("The matrix is not orthogonal.\n");
	}

	return 0;
}