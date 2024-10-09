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
void getCofactor(int n, float a[n][n], float temp[n][n], int p, int q);

float determinant(int n, float a[n][n]) {
    if (n == 1) {
        return a[0][0];
    }

    float det = 0.0;
    float temp[n][n];
    int sign = 1;

    for (int f = 0; f < n; f++) {
        getCofactor(n, a, temp, 0, f);
        det += sign * a[0][f] * determinant(n - 1, temp);
        sign = -sign;
    }

    return det;
}

void getCofactor(int n, float a[n][n], float temp[n][n], int p, int q) {
    int i = 0, j = 0;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (row != p && col != q) {
                temp[i][j++] = a[row][col];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

void inverseMatrix(int n, float a[n][n], float inverse[n][n]) {
    float det = determinant(n, a);
    if (det == 0) {
        printf("Matrix is singular and cannot be inverted.\n");
        return;
    }

    float adjugate[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            float temp[n][n];
            getCofactor(n, a, temp, i, j);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            adjugate[j][i] = sign * determinant(n - 1, temp);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = adjugate[i][j] / det;
        }
    }
}

bool doMatricesCommute(int n, float a[n][n], float b[n][n]) {
    float result_ab[n][n], result_ba[n][n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result_ab[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result_ab[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result_ba[i][j] = 0;
            for (int k = 0; k < n; k++) {
                result_ba[i][j] += b[i][k] * a[k][j];
            }
        }
    }

    return compareMatrices(n, result_ab, result_ba);
}

void addMatrices(int n, float a[n][n], float b[n][n], float result[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

bool compareMatrices(int n, float a[n][n], float b[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    const int n = 3;
    float a[3][3] = {
        {2, -1, 0},
        {1, 2, 1},
        {1, -1, 2}
    };
    float b[3][3] = {
        {3, 0, 2},
        {0, 1, -1},
        {1, 1, 0}
    };

    float a_inv[n][n], b_inv[n][n], sum_inv[n][n], sum[n][n], inv_sum[n][n];

    inverseMatrix(n, a, a_inv);
    inverseMatrix(n, b, b_inv);

    if (doMatricesCommute(n, a, b)) {
        addMatrices(n, a_inv, b_inv, sum_inv);
        addMatrices(n, a, b, sum);
        inverseMatrix(n, sum, inv_sum);

        if (compareMatrices(n, sum_inv, inv_sum)) {
            printf("The matrices satisfy the condition.\n");
        } else {
            printf("The matrices do not satisfy the condition.\n");
        }
    } else {
        printf("Matrices A and B do not commute and therefore do not satisfy the condition.\n");
    }

    return 0;
}
