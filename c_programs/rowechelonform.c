#include <stdio.h>

void toRowEchelonForm(float M[20][20], int rowCount, int colCount) {
    int lead = 0;
    for (int r = 0; r < rowCount; r++) {
        if (colCount <= lead) {
            return;
        }
        int i = r;
        while (M[i][lead] == 0) {
            i++;
            if (rowCount == i) {
                i = r;
                lead++;
                if (colCount == lead) {
                    return;
                }
            }
        }
        for (int j = 0; j < colCount; j++) {
            float temp = M[r][j];
            M[r][j] = M[i][j];
            M[i][j] = temp;
        }
        float div = M[r][lead];
        for (int j = 0; j < colCount; j++) {
            M[r][j] /= div;
        }
        for (int j = 0; j < rowCount; j++) {
            if (j != r) {
                float sub = M[j][lead];
                for (int k = 0; k < colCount; k++) {
                    M[j][k] -= (sub * M[r][k]);
                }
            }
        }
        lead++;
    }
}

int main() {
    float M[20][20];
    int rowCount, colCount;

    // Read the matrix from the user
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rowCount, &colCount);
    printf("Enter the elements of the matrix:\n");
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            scanf("%f", &M[i][j]);
        }
    }

    // Convert the matrix to row-echelon form
    toRowEchelonForm(M, rowCount, colCount);

    // Print the matrix in row-echelon form
    printf("The matrix in row-echelon form is:\n");
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            printf("%.2f\t", M[i][j]);
        }
        printf("\n");
    }

    return 0;
}