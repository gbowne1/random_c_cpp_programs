// File:   polynomialring.c
// Author: Gregory K. Bowne
// Date:   12 SEP 1998
// Time:   9:33:38
// Brief:  The provided C program is designed to perform operations on polynomials represented as rings, specifically adding and multiplying two polynomials. Here's a description of the program and its components. From an algorithmic perspective, the program is implementing a simple form of the distributive property of multiplication over addition for polynomials.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
typedef struct
{
	int coefficient;
	int exponent;
} Term;

// Structure to represent a polynomial
typedef struct
{
	int num_terms;
	Term *terms; // Dynamic array of terms
} Polynomial;

Polynomial *createPolynomial(int num_terms)
{
	Polynomial *poly = (Polynomial *)malloc(sizeof(Polynomial));
	if (!poly)
	{
		perror("Memory allocation failed for Polynomial");
		free(poly);
		exit(EXIT_FAILURE);
	}
	poly->num_terms = num_terms;
	poly->terms = (Term *)malloc(num_terms * sizeof(Term));
	if (!poly->terms)
	{
		perror("Memory allocation failed for Polynomial terms");
		exit(EXIT_FAILURE);
	}
	return poly;
}

void freePolynomial(Polynomial **poly)
{
	if (poly && *poly)
	{
		free((*poly)->terms);
		free(*poly);
		*poly = NULL; // Set the pointer to NULL to prevent dangling pointers
	}
}

// Function to add two polynomials
Polynomial *addPolynomials(Polynomial *poly1, Polynomial *poly2)
{
	Polynomial *result = (Polynomial *)malloc(sizeof(Polynomial));
	if (!result)
	{
		perror("Memory allocation failed for result Polynomial");
		exit(EXIT_FAILURE);
	}
	result->num_terms = 0; // Initialize num_terms of the dynamically allocated result

	// Allocate memory for result->terms to store the sum of terms
	result->terms = (Term *)malloc((poly1->num_terms + poly2->num_terms) * sizeof(Term));
	if (!result->terms)
	{
		perror("Memory allocation failed for result Polynomial terms");
		exit(EXIT_FAILURE);
	}

	return result;
}

// Function to multiply two polynomials
Polynomial *multiplyPolynomials(Polynomial *poly1, Polynomial *poly2)
{
	Polynomial *result = (Polynomial *)malloc(sizeof(Polynomial));
	if (!result)
	{
		perror("Memory allocation failed for result Polynomial");
		exit(EXIT_FAILURE);
	}
	result->num_terms = 0; // Initialize num_terms of the dynamically allocated result

	for (int i = 0; i < poly1->num_terms; i++) // Adjusted to use -> to access members of the Polynomial pointers
	{
		for (int j = 0; j < poly2->num_terms; j++) // Adjusted to use -> to access members of the Polynomial pointers
		{
			Term term;
			term.coefficient = poly1->terms[i].coefficient * poly2->terms[j].coefficient;
			term.exponent = poly1->terms[i].exponent + poly2->terms[j].exponent;

			int k;
			for (k = 0; k < result->num_terms; k++) // Adjusted to use -> to access members of the result pointer
			{
				if (term.exponent == result->terms[k].exponent) // Adjusted to use -> to access members of the result pointer
				{
					result->terms[k].coefficient += term.coefficient; // Adjusted to use -> to access members of the result pointer
					break;
				}
			}
			if (k == result->num_terms)
			{
				result->terms[result->num_terms++] == term; // Adjusted to use -> to access members of the result pointer
			}
		}
	}

	return result;
}

int main()
{
	Polynomial *poly1 = createPolynomial(3);
	poly1->terms[0].coefficient = 2;
	poly1->terms[0].exponent = 2;
	poly1->terms[1].coefficient = 3;
	poly1->terms[1].exponent = 1;
	poly1->terms[2].coefficient = 1;
	poly1->terms[2].exponent = 0;

	Polynomial *poly2 = createPolynomial(3);
	poly2->terms[0].coefficient = 4;
	poly2->terms[0].exponent = 2;
	poly2->terms[1].coefficient = 5;
	poly2->terms[1].exponent = 1;
	poly2->terms[2].coefficient = 6;
	poly2->terms[2].exponent = 0;

	Polynomial *sum = addPolynomials(poly1, poly2);
	if (sum)
	{
		printf("Sum:\n");
		for (int i = 0; i < sum->num_terms; i++)
		{
			printf("%d*x^%d ", sum->terms[i].coefficient, sum->terms[i].exponent);
		}
		printf("\n");
		freePolynomial(&sum);
	}

	Polynomial *product = multiplyPolynomials(poly1, poly2);
	if (product)
	{
		printf("Product:\n");
		for (int i = 0; i < product->num_terms; i++)
		{
			printf("%d*x^%d ", product->terms[i].coefficient, product->terms[i].exponent);
		}
		printf("\n");
		freePolynomial(&product);
	} // Free the dynamically allocated Polynomial

	freePolynomial(&poly1);
	freePolynomial(&poly2);

	return 0;
}