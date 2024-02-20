// File:   orthagonmatrix.c
// Author: Gregory K. Bowne
// Date:   12 SEP 1998
// Time:   8:54:08
// Brief:  This program defines functions to transpose a matrix, multiply two matrices,
// and check if a matrix is an identity matrix. It uses these functions to determine if
// the given square matrix is orthogonal by checking if the product of the matrix and
// its transpose results in an identity matrix

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void transposeMatrix(int size, int **matrix, int **transpose)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			transpose[j][i] = matrix[i][j];
		}
	}
}

int isIdentityMatrix(int size, int **matrix)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((i == j && matrix[i][j] != 1) || (i != j && matrix[i][j] != 0))
			{
				return 0;
			}
		}
	}
	return 1;
}

void multiplyMatrices(int size, int **matrix1, int **matrix2, int **result)
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

int main() {
    int size;
    printf("Enter size of square matrix (e.g., 3 for 3x3): ");
    scanf("%d", &size);

    // Allocate memory for the matrices
    int **matrix = (int **)malloc(size * sizeof(int *));
    int **transpose = (int **)malloc(size * sizeof(int *));
    int **product = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
        transpose[i] = (int *)malloc(size * sizeof(int));
        product[i] = (int *)malloc(size * sizeof(int));
        if (!matrix[i] || !transpose[i] || !product[i]) {
            perror("Failed to allocate memory for matrices");
            // Free already allocated memory before exiting
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
                free(transpose[j]);
                free(product[j]);
            }
            free(matrix);
            free(transpose);
            free(product);
            exit(EXIT_FAILURE);
        }
    }

    // Input loop with validation
    printf("Enter elements of the matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (scanf("%d", &matrix[i][j]) != 1) {
                printf("Invalid input. Please enter integers only.\n");
                // Consider adding logic to clean up and exit or to retry input
            }
        }
    }

    // Perform matrix operations
    transposeMatrix(size, matrix, transpose);
    multiplyMatrices(size, matrix, transpose, product);

    // Check if the matrix is orthogonal
    if (isIdentityMatrix(size, product)) {
        printf("The matrix is orthogonal.\n");
    } else {
        printf("The matrix is not orthogonal.\n");
    }

    // Free the allocated memory
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
        free(transpose[i]);
        free(product[i]);
    }
    free(matrix);
    free(transpose);
    free(product);

    return 0;
}