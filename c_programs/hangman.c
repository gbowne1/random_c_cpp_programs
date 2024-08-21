#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

// Function prototypes
void displayWord(const char *word, const int *guessed);
void displayHangman(int tries);
const char *selectRandomWord(const char *words[], int wordCount);

int main() {
    const char *words[] = {"programming", "hangman", "computer", "algorithm", "software", "python", "java", "javascript", "c", "c++"};
    const int wordCount = sizeof(words) / sizeof(words[0]);

    srand(time(NULL));
    const char *word = selectRandomWord(words, wordCount);
    int wordLength = strlen(word);

    int guessed[MAX_WORD_LENGTH] = {0};
    int tries = 0;
    int correctGuesses = 0;

    printf("Welcome to Hangman!\n");

    while (tries < MAX_TRIES && correctGuesses < wordLength) {
        displayHangman(tries);
        displayWord(word, guessed);

        printf("Guess a letter: ");
        char guess = tolower(getchar());
        getchar(); // Consume newline character

        int found = 0;
        for (int i = 0; i < wordLength; i++) {
            if (word[i] == guess && !guessed[i]) {
                guessed[i] = 1;
                correctGuesses++;
                found = 1;
            }
        }

        if (!found) {
            tries++;
            printf("Incorrect guess!\n");
        }
    }

    displayHangman(tries);
    displayWord(word, guessed);

    if (correctGuesses == wordLength) {
        printf("Congratulations! You guessed the word: %s\n", word);
    } else {
        printf("Game over! The word was: %s\n", word);
    }

    return 0;
}

// Display the current state of the word
void displayWord(const char *word, const int *guessed) {
    for (int i = 0; word[i] != '\0'; i++) {
        printf("%c ", guessed[i] ? word[i] : '_');
    }
    printf("\n");
}

// Display the hangman drawing based on the number of incorrect guesses
void displayHangman(int tries) {
    const char *hangman[] = {
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /     |\n      |\n=========",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\   |\n      |\n========="
    };
    printf("%s\n", hangman[tries]);
}

// Select a random word from the given array
const char *selectRandomWord(const char *words[], int wordCount) {
    return words[rand() % wordCount];
}
