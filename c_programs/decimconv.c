#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decimalToBinary(int decimal) {
    if (decimal == 0) {
        return strdup("0");
    }

    int size = sizeof(int) * 8;
    char* binary = malloc(size + 1);
    int index = 0;

    while (decimal > 0) {
        binary[index++] = (decimal & 1) ? '1' : '0';
        decimal >>= 1;
    }

    binary[index] = '\0';

    // Reverse the string
    for (int i = 0; i < index / 2; i++) {
        char temp = binary[i];
        binary[i] = binary[index - 1 - i];
        binary[index - 1 - i] = temp;
    }

    return binary;
}

int main() {
    int decimal;
    printf("Enter a decimal number: ");
    scanf("%d", &decimal);

    char* binary = decimalToBinary(decimal);
    printf("Binary representation: %s\n", binary);

    free(binary);
    return 0;
}

