// This is not compatible with C89/C90. Must be compiled with C99 or later

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* decimalToBinary(int decimal) {
    if (decimal == 0) {
        return strdup("0");
    }

    int size = sizeof(long long) * 8;
    char* binary = malloc(size + 1);
    if (binary == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
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
    long long decimal;
    printf("Enter a decimal number: ");
    scanf("%lld", &decimal);

    char* binary = decimalToBinary(decimal);
    printf("Binary representation: %s\n", binary);

    free(binary);
    return 0;
}

