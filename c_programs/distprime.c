#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Checks if a number is prime.
 *
 * @param num The number to check.
 * @return 1 if prime, 0 otherwise.
 */
int is_prime(int num) {
    if (num <= 1) return 0; // 0 and 1 are not prime numbers
    if (num == 2) return 1; // 2 is the only even prime number
    if (num % 2 == 0) return 0; // Eliminate even numbers greater than 2
    
    int sqrt_num = (int)sqrt(num);
    for (int i = 3; i <= sqrt_num; i += 2) { // Check only odd divisors
        if (num % i == 0) return 0;
    }
    
    return 1; // The number is prime
}

/**
 * Generates prime numbers sequentially up to a given limit.
 *
 * @param limit The number of prime numbers to generate.
 */
void generate_primes(int limit) {
    int count = 0;
    int num = 2;
    
    printf("First %d prime numbers:\n", limit);
    
    while (count < limit) {
        if (is_prime(num)) {
            printf("%d ", num);
            count++;
            if (count % 10 == 0) printf("\n"); // Print a newline after every 10 primes
        }
        num++;
    }
    
    // Ensure newline at the end
    if (count % 10 != 0) printf("\n");
}

/**
 * Main program entry point.
 *
 * @return 0 on success, non-zero on error.
 */
int main() {
    int limit;

    // Prompt user for input
    printf("Enter the number of prime numbers to generate: ");
    
    // Check for valid input
    if (scanf("%d", &limit) != 1 || limit <= 0) {
        fprintf(stderr, "Error: Invalid input. Please enter a positive integer.\n");
        return EXIT_FAILURE;
    }

    // Inform the user about the input limit
    if (limit > 10000) { // Arbitrary limit for user feedback
        printf("Generating a large number of primes. This may take some time...\n");
    }
    
    generate_primes(limit);
    
    return EXIT_SUCCESS;
}
