// File:   euclidian.c
// Author: Gregory K. Bowne
// Date:   09 OCT 2015
// Time:   7:54:11
// Brief:  This program calculates This program calculates the GCD of three pairs
// of numbers: (10, 15), (35, 10), and (31, 2). You can modify the numbers as per
// your requirement. The gcd() function implements the Euclidean algorithm recursively.

#include <stdio.h>
#include <math.h>

// Recursive function to return gcd of a and b
int gcd(int a, int b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

int main() {
    int a = 10, b = 15;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));

    a = 35, b = 10;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));

    a = 31, b = 2;
    printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));

    return 0;
}