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
    unsigned long long* fib_sequence = NULL;
    
    /* Allocate memory for the Fibonacci sequence */
    fib_sequence = (unsigned long long*)malloc((max_terms + 1) * sizeof(unsigned long long));
    
    if (!fib_sequence) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    /* Initialize first two terms */
    fib_sequence[0] = 0;
    fib_sequence[1] = 1;
    
    /* Generate Fibonacci sequence */
    for (int i = 2; i <= max_terms; i++) {
        fib_sequence[i] = fib_sequence[i-1] + fib_sequence[i-2];
        
        /*
         * Check for potential overflow
         * We use the fact that the sum of two even numbers is always even,
         * and the sum of two odd numbers is always even.
         */
        if ((fib_sequence[i-1] & 1) && (fib_sequence[i-2] & 1)) {
            fprintf(stderr, "Potential overflow detected\n");
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
    unsigned long long prev = 0, curr = 1;
    
    for (int i = 2; i <= terms; i++) {
        if (fib_sequence[i] != prev + curr) {
            return 0; /* Incorrect sequence */
        }
        prev = curr;
        curr = fib_sequence[i];
    }
    
    return 1; /* Sequence is correct */
}

/*
 * Main function to test the Fibonacci program.
 */
int main(void) {
    const int MAX_TERMS = 93; /* Maximum number of terms (92nd term exceeds INT_MAX) */
    const int TEST_RUNS = 5;
    
    srand(time(NULL)); /* Seed random number generator */
    
    printf("Fibonacci Program Test\n");
    printf("----------------------\n\n");
    
    /* Run multiple test cases */
    for (int i = 0; i < TEST_RUNS; i++) {
        int max_terms = rand() % MAX_TERMS + 1;
        
        printf("\nTest Case %d:\n", i+1);
        printf("Generating Fibonacci sequence up to term %d...\n", max_terms);
        
        unsigned long long* fib_sequence = calculate_fibonacci(max_terms);
        
        if (fib_sequence) {
            printf("Sequence generated successfully.\n");
            
            int is_correct = verify_fibonacci_sequence(fib_sequence, max_terms);
            
            if (is_correct) {
                printf("Verification successful!\n");
                
                /*
                 * Print first few terms for verification
                 */
                printf("First few terms: ");
                for (int j = 0; j < 10 && j < max_terms; j++) {
                    printf("%llu ", fib_sequence[j]);
                }
                printf("\n");
            } else {
                fprintf(stderr, "Verification failed!\n");
            }
            
            free(fib_sequence);
        } else {
            fprintf(stderr, "Memory allocation failed.\n");
        }
        
        printf("\n");
    }
    
    return 0;
}
