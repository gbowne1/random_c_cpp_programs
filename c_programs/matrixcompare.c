#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Helper macro to access 2D matrix using 1D array
#define IDX(i, j, n) ((i) * (n) + (j))

// Function prototypes
float determinant(int n, float *matrix);
void getCofactor(int n, float *matrix, float *temp, int p, int q);
void inverseMatrix(int n, float *matrix, float *inverse);
void addMatrices(int n, float *a, float *b, float *result);
bool compareMatrices(int n, float *a, float *b);
bool doMatricesCommute(int n, float *a, float *b);

// Function to calculate determinant using recursion
float determinant(int n, float *matrix) {
    if (n == 1) return matrix[0];

    float det = 0.0f;
    float *temp = (float *)malloc(n * n * sizeof(float));
    if (!temp) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int sign = 1;
    for (int f = 0; f < n; f++) {
        getCofactor(n, matrix, temp, 0, f);
        det += sign * matrix[IDX(0, f, n)] * determinant(n - 1, temp);
        sign = -sign;
    }

    free(temp);
    return det;
}

// Function to get cofactor of matrix[p][q]
void getCofactor(int n, float *matrix, float *temp, int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[IDX(i, j++, n - 1)] = matrix[IDX(row, col, n)];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Function to compute inverse matrix
void inverseMatrix(int n, float *matrix, float *inverse) {
    float det = determinant(n, matrix);
    if (det == 0) {
        printf("Matrix is singular and cannot be inverted.\n");
        return;
    }

    float *adjugate = (float *)malloc(n * n * sizeof(float));
    float *temp = (float *)malloc((n - 1) * (n - 1) * sizeof(float));

    if (!adjugate || !temp) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getCofactor(n, matrix, temp, i, j);
            float sign = ((i + j) % 2 == 0) ? 1.0f : -1.0f;
            adjugate[IDX(j, i, n)] = sign * determinant(n - 1, temp);
        }
    }

    for (int i = 0; i < n * n; i++) {
        inverse[i] = adjugate[i] / det;
    }

    free(adjugate);
    free(temp);
}

// Add two matrices
void addMatrices(int n, float *a, float *b, float *result) {
    for (int i = 0; i < n * n; i++) {
        result[i] = a[i] + b[i];
    }
}

// Compare matrices for equality
bool compareMatrices(int n, float *a, float *b) {
    for (int i = 0; i < n * n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

// Check if AB == BA
bool doMatricesCommute(int n, float *a, float *b) {
    float *ab = (float *)calloc(n * n, sizeof(float));
    float *ba = (float *)calloc(n * n, sizeof(float));

    if (!ab || !ba) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ab[IDX(i, j, n)] += a[IDX(i, k, n)] * b[IDX(k, j, n)];
                ba[IDX(i, j, n)] += b[IDX(i, k, n)] * a[IDX(k, j, n)];
            }
        }
    }

    bool result = compareMatrices(n, ab, ba);
    free(ab); free(ba);
    return result;
}

// Main function
int main() {
    const int n = 3;
    float a[9] = {
        2, -1, 0,
        1, 2, 1,
        1, -1, 2
    };

    float b[9] = {
        3, 0, 2,
        0, 1, -1,
        1, 1, 0
    };

    float a_inv[9], b_inv[9], sum[9], sum_inv[9], inv_sum[9];

    inverseMatrix(n, a, a_inv);
    inverseMatrix(n, b, b_inv);

    if (doMatricesCommute(n, a, b)) {
        addMatrices(n, a_inv, b_inv, sum_inv);
        addMatrices(n, a, b, sum);
        inverseMatrix(n, sum, inv_sum);

        if (compareMatrices(n, sum_inv, inv_sum)) {
            printf("The matrices satisfy the condition: (A⁻¹ + B⁻¹) == (A + B)⁻¹\n");
        } else {
            printf("The matrices do not satisfy the condition: (A⁻¹ + B⁻¹) != (A + B)⁻¹\n");
        }
    } else {
        printf("Matrices A and B do not commute and therefore do not satisfy the condition.\n");
    }

    return 0;
}
