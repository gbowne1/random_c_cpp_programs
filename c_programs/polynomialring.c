// File:   polynomialring.c
// Author: Gregory K. Bowne
// Date:   12 SEP 1998
// Time:   9:33:38
// Brief:  The provided C program is designed to perform operations on polynomials represented as rings, specifically adding and multiplying two polynomials. Here's a description of the program and its components. From an algorithmic perspective, the program is implementing a simple form of the distributive property of multiplication over addition for polynomials.

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a term in a polynomial
typedef struct Term
{
	int coefficient;
	int exponent;
} Term;

// Structure to represent a polynomial
typedef struct Polynomial
{
	int degree;
	int capacity;
	int num_terms;
	Term *terms; // Dynamic array of terms
} Polynomial;

Polynomial *createPolynomial(int num_terms) {
    Polynomial *poly = malloc(sizeof(Polynomial));
    if (!poly) {
        perror("Memory allocation failed for Polynomial");
        return NULL;
    }
    
    poly->num_terms = num_terms;
    poly->terms = malloc(num_terms * sizeof(Term));
    if (!poly->terms) {
        perror("Memory allocation failed for Polynomial terms");
        free(poly);
        return NULL;
    }
    
    return poly;
}


void freePolynomial(Polynomial *poly) {
    if (poly) {
        free(poly->terms);
        free(poly);
    }
}

// Function to add two polynomials
Polynomial *addPolynomials(Polynomial *poly1, Polynomial *poly2) {
    int total_terms = poly1->num_terms + poly2->num_terms;
    
    Polynomial *result = createPolynomial(total_terms);
    if (!result) {
        perror("Memory allocation failed for result Polynomial");
        return NULL;
    }

    int i = 0, j = 0, k = 0;

    while (i < poly1->num_terms && j < poly2->num_terms) {
        if (poly1->terms[i].exponent > poly2->terms[j].exponent) {
            result->terms[k++] = poly1->terms[i++];
        } else if (poly1->terms[i].exponent < poly2->terms[j].exponent) {
            result->terms[k++] = poly2->terms[j++];
        } else {
            result->terms[k].coefficient = poly1->terms[i].coefficient + poly2->terms[j].coefficient;
            if (result->terms[k].coefficient != 0) {
                k++;
            }
            i++;
            j++;
        }
    }

    while (i < poly1->num_terms) result->terms[k++] = poly1->terms[i++];
    while (j < poly2->num_terms) result->terms[k++] = poly2->terms[j++];

    result->num_terms = k;
    return result;
}


// Function to multiply two polynomials
Polynomial* multiplyPolynomials(Polynomial* poly1, Polynomial* poly2) {
    Polynomial* result = createPolynomial(poly1->degree + poly2->degree);
    if (!result) {
        return NULL;
    }

    for (int i = 0; i < poly1->degree; i++) {
        for (int j = 0; j < poly2->degree; j++) {
            Term term;
            term.coefficient = poly1->terms[i].coefficient * poly2->terms[j].coefficient;
            term.exponent = poly1->terms[i].exponent + poly2->terms[j].exponent;

            addTerm(result, &term);
        }
    }

    return result;
}

void addTerm(Polynomial* poly, Term* term) {
    int index = poly->degree;
    while (index > 0 && poly->terms[index-1].exponent >= term->exponent) {
        index--;
    }

    memmove(&poly->terms[index+1], &poly->terms[index], (poly->degree-index)*sizeof(Term));
    poly->terms[index] = *term;
    poly->degree++;
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