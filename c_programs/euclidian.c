// File:   euclidian.c
// Author: Gregory K. Bowne
// Date:   09 OCT 2015
// Time:   7:54:11
// Brief:  This program calculates This program calculates the GCD of three pairs
// of numbers: (10, 15), (35, 10), and (31, 2). You can modify the numbers as per
// your requirement. The gcd() function implements the Euclidean algorithm recursively.

#include <stdio.h>

// Function to calculate the GCD of two non-negative integers a and b
// using the iterative Euclidean algorithm.
int gcd(int a, int b)
{
	// Base case: If a is zero, then GCD is b
	if (a == 0)
		return b;
	 // Recursive case: GCD(a, b) is same as GCD(b % a, a)
	return gcd(b % a, a);
}

int main()
{
	// Pre-defined pairs of numbers for GCD calculation
	int pairs[][2] = {{10, 15}, {35, 10}, {31, 2}};

	// Loop to calculate and print GCD for each pair
	for (int i = 0; i < 3; i++)
	{
		int a = pairs[i][0];
		int b = pairs[i][1];
		printf("GCD(%d, %d) = %d\n", a, b, gcd(a, b));
	}
	return 0;
}