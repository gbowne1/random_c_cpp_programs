// File:   rowechelongform.c
// Author: Gregory K. Bowne
// Date:   11 MAY 2003
// Time:   11:18:24
// Brief:  This program uses the Gaussian elimination algorithm to  to convert a matrix to its row-echelon form

#include <stdio.h>
#include <stdlib.h>

void swapRows(float **M, int row1, int row2, int colCount)
{
	for (int j = 0; j < colCount; j++)
	{
		float temp = M[row1][j];
		M[row1][j] = M[row2][j];
		M[row2][j] = temp;
	}
}

void toRowEchelonForm(float **M, int rowCount, int colCount)
{
	int lead = 0;
	for (int r = 0; r < rowCount; r++)
	{
		if (colCount <= lead)
		{
			return;
		}
		int i = r;
		while (M[i][lead] == 0)
		{
			i++;
			if (rowCount == i)
			{
				i = r;
				lead++;
				if (colCount == lead)
				{
					return;
				}
			}
		}
		for (int j = 0; j < colCount; j++)
		{
			float temp = M[r][j];
			M[r][j] = M[i][j];
			M[i][j] = temp;
		}
		float div = M[r][lead];

		// Handle division by zero
		if (div != 0)
		{
			for (int j = 0; j < colCount; j++)
			{
				M[r][j] /= div;
			}
		}
		else
		{
			// Handle division by zero
			for (int j = 0; j < colCount; j++)
			{
				M[r][j] = 0; // Set entire row to zero
			}
		}

		for (int j = 0; j < rowCount; j++)
		{
			if (j != r)
			{
				float sub = M[j][lead];
				for (int k = 0; k < colCount; k++)
				{
					M[j][k] -= (sub * M[r][k]);
				}
			}
		}
		lead++;
	}
}

int main()
{
	int rowCount, colCount;

	// Read the matrix from the user
	printf("Enter the number of rows and columns: ");
	scanf("%d %d", &rowCount, &colCount);

	float **M = (float **)malloc(rowCount * sizeof(float *));
	for (int i = 0; i < rowCount; i++)
	{
		M[i] = (float *)malloc(colCount * sizeof(float));
	}

	printf("Enter the elements of the matrix:\n");
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			scanf("%f", &M[i][j]);
		}
	}

	// Convert the matrix to row-echelon form
	toRowEchelonForm(M, rowCount, colCount);

	// Print the matrix in row-echelon form
	printf("The matrix in row-echelon form is:\n");
	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < colCount; j++)
		{
			printf("%.2f\t", M[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < rowCount; i++)
	{
		free(M[i]);
	}
	free(M);

	return 0;
}