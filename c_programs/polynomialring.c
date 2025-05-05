// File:   polynomialring.c
// Author: Gregory K. Bowne
// Date:   12 SEP 1998
// Time:   9:33:38
// Brief:  This program performs addition and multiplication of polynomials represented as arrays of terms.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a term in a polynomial
typedef struct Term {
    int coefficient;
    int exponent;
} Term;

// Structure to represent a polynomial
typedef struct Polynomial {
    int num_terms;   // Number of terms currently stored
    int capacity;    // Maximum number of terms allocated
    Term *terms;     // Dynamic array of terms
} Polynomial;

// Forward declaration
void addTerm(Polynomial* poly, Term* term);

Polynomial *createPolynomial(int capacity) {
    Polynomial *poly = malloc(sizeof(Polynomial));
    if (!poly) {
        perror("Memory allocation failed for Polynomial");
        return NULL;
    }

    poly->num_terms = 0;
    poly->capacity = capacity;
    poly->terms = malloc(capacity * sizeof(Term));
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

// Add a term in order, combining like terms if needed
void addTerm(Polynomial* poly, Term* term) {
    for (int i = 0; i < poly->num_terms; ++i) {
        if (poly->terms[i].exponent == term->exponent) {
            poly->terms[i].coefficient += term->coefficient;
            return;
        }
    }

    // New term; insert at the end
    if (poly->num_terms >= poly->capacity) {
        poly->capacity *= 2;
        poly->terms = realloc(poly->terms, poly->capacity * sizeof(Term));
    }

    poly->terms[poly->num_terms++] = *term;
}

// Function to add two polynomials
Polynomial *addPolynomials(Polynomial *poly1, Polynomial *poly2) {
    Polynomial *result = createPolynomial(poly1->num_terms + poly2->num_terms);
    if (!result) return NULL;

    for (int i = 0; i < poly1->num_terms; i++) {
        addTerm(result, &poly1->terms[i]);
    }
    for (int i = 0; i < poly2->num_terms; i++) {
        addTerm(result, &poly2->terms[i]);
    }

    return result;
}

// Function to multiply two polynomials
Polynomial* multiplyPolynomials(Polynomial* poly1, Polynomial* poly2) {
    Polynomial* result = createPolynomial(poly1->num_terms * poly2->num_terms);
    if (!result) return NULL;

    for (int i = 0; i < poly1->num_terms; i++) {
        for (int j = 0; j < poly2->num_terms; j++) {
            Term term;
            term.coefficient = poly1->terms[i].coefficient * poly2->terms[j].coefficient;
            term.exponent = poly1->terms[i].exponent + poly2->terms[j].exponent;
            addTerm(result, &term);
        }
    }

    return result;
}

// Function to print a polynomial
void printPolynomial(Polynomial *poly) {
    for (int i = 0; i < poly->num_terms; i++) {
        printf("%d*x^%d", poly->terms[i].coefficient, poly->terms[i].exponent);
        if (i != poly->num_terms - 1)
            printf(" + ");
    }
    printf("\n");
}

int main() {
    Polynomial *poly1 = createPolynomial(3);
    poly1->terms[0].coefficient = 2; poly1->terms[0].exponent = 2;
    poly1->terms[1].coefficient = 3; poly1->terms[1].exponent = 1;
    poly1->terms[2].coefficient = 1; poly1->terms[2].exponent = 0;
    poly1->num_terms = 3;

    Polynomial *poly2 = createPolynomial(3);
    poly2->terms[0].coefficient = 4; poly2->terms[0].exponent = 2;
    poly2->terms[1].coefficient = 5; poly2->terms[1].exponent = 1;
    poly2->terms[2].coefficient = 6; poly2->terms[2].exponent = 0;
    poly2->num_terms = 3;

    Polynomial *sum = addPolynomials(poly1, poly2);
    if (sum) {
        printf("Sum:\n");
        printPolynomial(sum);
        freePolynomial(sum);
    }

    Polynomial *product = multiplyPolynomials(poly1, poly2);
    if (product) {
        printf("Product:\n");
        printPolynomial(product);
        freePolynomial(product);
    }

    freePolynomial(poly1);
    freePolynomial(poly2);

    return 0;
}
