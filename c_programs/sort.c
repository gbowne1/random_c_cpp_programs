// File:   sort.c
// Author: Gregory K. Bowne
// Date:   15 DEC 2020
// Time:   13:56:21
// Brief:  This program sorts a set of numbers entered by the user

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENTS 10

// Function prototypes
int how_many();
void getnums(int n, int v[]);
void sort(int n, int v[]);
void output(int n, int v[]);
void swap(int *a, int *b);

int how_many()
{
	int n = 0;
	n = MAX_ELEMENTS + 1;
	do
	{
		printf("How many numbers? (1-%d): ", MAX_ELEMENTS);
		if (scanf("%d", &n) != 1)
		{
			printf("Invalid input. Please enter an integer.\n");
			// Clear the input buffer
			while (getchar() != '\n')
				;
			n = 0; // Reset n to ensure the loop continues
		}
		else if (n < 1 || n > MAX_ELEMENTS)
		{
			printf("Please enter a number between 1 and %d.\n", MAX_ELEMENTS);
		}
	} while (n < 1 || n > MAX_ELEMENTS);
	return n;
}

void getnums(int n, int v[])
{
	int x, num;

	for (x = 0; x < n; ++x)
	{
		printf("Enter number %d: ", x + 1);
		scanf("%d", &num);
		v[x] = num;
		printf("\n");
	}
}

void sort(int n, int v[])
{
	bool didSwap;
	do
	{
		didSwap = false;
		for (int x = 0; x < n - 1; ++x)
		{
			if (v[x] > v[x + 1])
			{
				swap(&v[x], &v[x + 1]);
				didSwap = true;
			}
		}
	} while (didSwap);
}

void output(int n, int v[])
{
	int x;

	printf("Sort complete!\n\n");
	for (x = 0; x < n; ++x)
		printf("%d ", v[x]);
	printf("\n\n");
}

int main()
{
	int num;
	int *val;

	num = how_many();
	val = (int *)malloc(num * sizeof(int));
	if (val == NULL)
	{
		perror("Failed to allocate memory");
		return EXIT_FAILURE;
	}

	getnums(num, val);
	sort(num, val);
	output(num, val);

	free(val);
	return 0;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}