// File:   permutations.c
// Author: Gregory K. Bowne
// Date:   11 JUN 1999
// Time:   12:18:31
// Brief:  This program helps with doing all sorts of permutations. This should be C99 or later compliant.

#include <stdio.h>
#include <string.h>

// Function to swap two characters
inline void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Recursive function to generate permutations
void generatePermutations(char *str, int left, int right) {
    if (left == right) {
        printf("%s\n", str);  // Print the current permutation
    } else {
        for (int i = left; i <= right; i++) {
            swap((str + left), (str + i));  // Swap current element with the leftmost
            generatePermutations(str, left + 1, right);  // Recurse for the rest
            swap((str + left), (str + i));  // Backtrack to restore original configuration
        }
    }
}

int main() {
    char str[] = "ABC";
    int length = strlen(str);
    generatePermutations(str, 0, length - 1);
    return 0;
}
