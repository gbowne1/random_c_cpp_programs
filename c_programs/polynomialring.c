// File:   polynomialring.c
// Author: Gregory K. Bowne
// Date:   12 SEP 1998
// Time:   9:33:38
// Brief:  This program does Polynomial Rings in C

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

void freePolynomial(Polynomial *poly)
{
	free(poly->terms);
	free(poly);
}

// Function to add two polynomials
Polynomial addPolynomials(Polynomial poly1, Polynomial poly2)
{
	Polynomial result;
	result.num_terms = 0;

	for (int i = 0; i < poly1.num_terms; i++)
	{
		result.terms[result.num_terms++] = poly1.terms[i];
	}

	for (int i = 0; i < poly2.num_terms; i++)
	{
		int j;
		for (j = 0; j < result.num_terms; j++)
		{
			if (poly2.terms[i].exponent == result.terms[j].exponent)
			{
				result.terms[j].coefficient += poly2.terms[i].coefficient;
				break;
			}
		}
		if (j == result.num_terms)
		{
			result.terms[result.num_terms++] = poly2.terms[i];
		}
	}

	return result;
}

// Function to multiply two polynomials
Polynomial multiplyPolynomials(Polynomial poly1, Polynomial poly2)
{
	Polynomial result;
	result.num_terms = 0;

	for (int i = 0; i < poly1.num_terms; i++)
	{
		for (int j = 0; j < poly2.num_terms; j++)
		{
			Term term;
			term.coefficient = poly1.terms[i].coefficient * poly2.terms[j].coefficient;
			term.exponent = poly1.terms[i].exponent + poly2.terms[j].exponent;

			int k;
			for (k = 0; k < result.num_terms; k++)
			{
				if (term.exponent == result.terms[k].exponent)
				{
					result.terms[k].coefficient += term.coefficient;
					break;
				}
			}
			if (k == result.num_terms)
			{
				result.terms[result.num_terms++] = term;
			}
		}
	}

	return result;
}

int main()
{
	Polynomial poly1 = {{2, 2}, {3, 1}, {1, 0}};
	poly1.num_terms = 3;

	Polynomial poly2 = {{4, 2}, {5, 1}, {6, 0}};
	poly2.num_terms = 3;

	Polynomial sum = addPolynomials(poly1, poly2);
	printf("Sum:\n");
	for (int i = 0; i < sum.num_terms; i++)
	{
		printf("%d*x^%d ", sum.terms[i].coefficient, sum.terms[i].exponent);
	}
	printf("\n");

	Polynomial product = multiplyPolynomials(poly1, poly2);
	printf("Product:\n");
	for (int i = 0; i < product.num_terms; i++)
	{
		printf("%d*x^%d ", product.terms[i].coefficient, product.terms[i].exponent);
	}
	printf("\n");

	freePolynomial(poly1);
	freePolynomial(poly2);
	freePolynomial(sum);
	freePolynomial(product);

	return 0;
}