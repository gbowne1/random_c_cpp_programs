#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fibonacci.h"

/*
 * Function to calculate Fibonacci series up to 'max_terms'.
 *
 * @param max_terms The maximum number of terms to generate.
 * @return An array containing the Fibonacci sequence.
 */
unsigned long long* calculate_fibonacci(int max_terms) {
    if (max_terms < 1) return NULL;

    unsigned long long* fib_sequence = malloc((max_terms + 1) * sizeof(unsigned long long));
    if (!fib_sequence) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fib_sequence[0] = 0;
    if (max_terms >= 1) fib_sequence[1] = 1;

    for (int i = 2; i <= max_terms; i++) {
        fib_sequence[i] = fib_sequence[i-1] + fib_sequence[i-2];

        // Proper overflow detection
        if (fib_sequence[i] < fib_sequence[i-1]) {
            fprintf(stderr, "Overflow detected at term %d\n", i);
            break;
        }
    }

    return fib_sequence;
}

/*
 * Function to verify Fibonacci sequence correctness.
 *
 * @param fib_sequence Array containing the Fibonacci sequence.
 * @param terms Number of terms in the sequence.
 * @return 1 if the sequence is correct, 0 otherwise.
 */
int verify_fibonacci_sequence(unsigned long long* fib_sequence, int terms) {
    if (terms >= 1 && fib_sequence[0] != 0) return 0;
    if (terms >= 2 && fib_sequence[1] != 1) return 0;

    for (int i = 2; i <= terms; i++) {
        if (fib_sequence[i] != fib_sequence[i-1] + fib_sequence[i-2]) {
            return 0; // Incorrect sequence
        }
    }

    return 1; // Sequence is correct
}

/*
 * Function to print first few terms of the Fibonacci sequence.
 */
void print_fibonacci(unsigned long long* sequence, int terms_to_print) {
    for (int i = 0; i < terms_to_print; i++) {
        printf("%llu ", sequence[i]);
    }
    printf("\n");
}

/*
 * Main function to test the Fibonacci program.
 */
int main(void) {
    const int MAX_TERMS = 93; // 94th Fibonacci number exceeds unsigned long long
    const int TEST_RUNS = 5;

    srand((unsigned int)time(NULL)); // Seed random number generator

    printf("Fibonacci Program Test\n");
    printf("----------------------\n\n");

    for (int i = 0; i < TEST_RUNS; i++) {
        int max_terms = rand() % MAX_TERMS + 1;

        printf("Test Case %d:\n", i + 1);
        printf("Generating Fibonacci sequence up to term %d...\n", max_terms);

        unsigned long long* fib_sequence = calculate_fibonacci(max_terms);

        int is_correct = verify_fibonacci_sequence(fib_sequence, max_terms);
        if (is_correct) {
            printf("Verification successful!\n");

            int print_count = (max_terms < 10) ? max_terms : 10;
            printf("First %d terms: ", print_count);
            print_fibonacci(fib_sequence, print_count);
        } else {
            fprintf(stderr, "Verification failed!\n");
        }

        free(fib_sequence);
        printf("\n");
    }

    return 0;
}