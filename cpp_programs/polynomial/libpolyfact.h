#ifndef POLYNOMIAL_FACTORIZATION_H
#define POLYNOMIAL_FACTORIZATION_H

#include <vector>

// Structure to represent a polynomial
struct Polynomial {
    std::vector<double> coefficients;
};

// Function to factorize a polynomial using the Greatest Common Divisor (GCD) method
Polynomial factorizeByGCD(const Polynomial& poly);

// Function to factorize a polynomial by grouping
Polynomial factorizeByGrouping(const Polynomial& poly);

// Function to factorize a polynomial with special forms (e.g., difference of squares, perfect square trinomials)
Polynomial factorizeSpecialForms(const Polynomial& poly);

// Function to factorize a polynomial by substitution
Polynomial factorizeBySubstitution(const Polynomial& poly);

#endif