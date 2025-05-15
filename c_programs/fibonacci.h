#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <limits.h>

// Maximum value that can be stored in an integer
#define MAX_INT (INT_MAX)

// Function prototype for calculating Fibonacci numbers
unsigned long long* calculate_fibonacci(int max_terms);

// Function prototype for verifying Fibonacci sequence correctness
int verify_fibonacci_sequence(unsigned long long* fib_sequence, int terms);

#endif //FIBONACCI_H
