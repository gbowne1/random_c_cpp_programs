// File:   rowechelonform.c
// Author: Gregory K. Bowne
// Date:   11 MAY 2003
// Time:   11:18:24
// Brief:  This program uses the Gaussian elimination algorithm to  to convert a matrix to its row-echelon form

#include <stdio.h>
#include <stdlib.h>

// Function to swap two rows of the matrix
void swapRows(float **matrix, int row1, int row2, int colCount) {
    for (int col = 0; col < colCount; col++) {
        float temp = matrix[row1][col];
        matrix[row1][col] = matrix[row2][col];
        matrix[row2][col] = temp;
    }
}

// Function to convert matrix to row-echelon form
void toRowEchelonForm(float **matrix, int rowCount, int colCount) {
    int lead = 0;
    for (int r = 0; r < rowCount; r++) {
        if (lead >= colCount) return;
        int i = r;
        while (matrix[i][lead] == 0) {
            i++;
            if (i == rowCount) {
                i = r;
                lead++;
                if (lead == colCount) return;
            }
        }
        if (i != r) {
            swapRows(matrix, r, i, colCount);
        }
        float leadValue = matrix[r][lead];
        if (leadValue != 0) {
            for (int col = 0; col < colCount; col++) {
                matrix[r][col] /= leadValue;
            }
        }
        for (int row = 0; row < rowCount; row++) {
            if (row != r) {
                float factor = matrix[row][lead];
                for (int col = 0; col < colCount; col++) {
                    matrix[row][col] -= factor * matrix[r][col];
                }
            }
        }
        lead++;
    }
}

// Function to deallocate the matrix
void deallocateMatrix(float **matrix, int rowCount) {
    for (int i = 0; i < rowCount; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rowCount, colCount;
    printf("Enter the number of rows and columns: ");
    if (scanf("%d %d", &rowCount, &colCount) != 2 || rowCount <= 0 || colCount <= 0) {
        fprintf(stderr, "Invalid input. Please enter positive integers for rows and columns.\n");
        return EXIT_FAILURE;
    }

    // Allocate memory for the matrix
    float **matrix = (float **)malloc(rowCount * sizeof(float *));
    if (!matrix) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < rowCount; i++) {
        matrix[i] = (float *)malloc(colCount * sizeof(float));
        if (!matrix[i]) {
            fprintf(stderr, "Memory allocation failed.\n");
            deallocateMatrix(matrix, i);
            return EXIT_FAILURE;
        }
    }

    // Read matrix elements
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (scanf("%f", &matrix[i][j]) != 1) {
                fprintf(stderr, "Invalid input. Please enter valid floating-point numbers.\n");
                deallocateMatrix(matrix, rowCount);
                return EXIT_FAILURE;
            }
        }
    }

    // Convert to row-echelon form
    toRowEchelonForm(matrix, rowCount, colCount);

    // Print the matrix in row-echelon form
    printf("The matrix in row-echelon form is:\n");
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }

    // Deallocate matrix
    deallocateMatrix(matrix, rowCount);

    return EXIT_SUCCESS;
}
