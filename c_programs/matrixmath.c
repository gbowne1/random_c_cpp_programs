// File:   tempconvert.c
// Author: Gregory K. Bowne
// Date:   11 JUN 1999
// Time:   12:18:31
// Brief:  This program that can convert C to F and F to C

// Ignoring clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
// IntelliSense warning as the default compiler already uses C11
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>

// Function to get matrix elements entered by the user
void getMatrixElements(int matrix[][10], int row, int column) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            printf("Enter element a%d%d: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
	}
}

// Function to multiply two matrices
bool multiplyMatrices(int firstMatrix[][10], int secondMatrix[][10], int result[][10], int r1, int c1, int r2, int c2) {
    if(c1 != r2) {
        printf("Error! Column of the first matrix not equal to row of the second.\n");
        return false;
    }

    for(int i = 0; i < r1; ++i) {
        for(int j = 0; j < c2; ++j) {
            result[i][j] = 0;
            for(int k = 0; k < c1; ++k) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
				}
		}
	}
	return true;
}

// Function to display the resultant matrix after multiplication
void display(int result[][10], int row, int column) {
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < column; ++j) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int r1, c1, r2, c2;

    printf("Enter rows and columns for the first matrix: ");
    scanf("%d %d", &r1, &c1);

    printf("Enter rows and columns for the second matrix: ");
    scanf("%d %d", &r2, &c2);

	if (r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0) {
        printf("Error! Number of rows and columns should be positive.\n");
        return 1;
    }

    int firstMatrix[r1][c1], secondMatrix[r2][c2], result[r1][c2];
	printf("Enter elements for the first matrix:\n");
	getMatrixElements(firstMatrix, r1, c1);


    printf("Enter elements for the second matrix:\n");
    getMatrixElements(secondMatrix, r2, c2);

    if (multiplyMatrices(firstMatrix, secondMatrix, result, r1, c1, r2, c2)) {

    	printf("Resultant matrix:\n");
    	display(result, r1, c2);
	}
    return 0;
}