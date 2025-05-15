// Date: 10 SEPT 2023
// Brief: Linux x64 hangman using dictionary 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20
#define DICTIONARY_FILE "/usr/share/dict/words"

// Function prototypes
void displayWord(const char *word, const int *guessed);
void displayHangman(int tries);
const char *selectRandomWord(const char *filePath, char *wordBuffer);

int main() {
    char word[MAX_WORD_LENGTH];
    if (!selectRandomWord(DICTIONARY_FILE, word)) {
        fprintf(stderr, "Error: Could not load a word from the dictionary file.\n");
        return 1;
    }

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
        while (getchar() != '\n'); // Clear input buffer

        if (!isalpha(guess)) {
            printf("Invalid input. Please guess a letter.\n");
            continue;
        }

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

// Select a random word from the dictionary file
const char *selectRandomWord(const char *filePath, char *wordBuffer) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        return NULL;
    }

    char **words = malloc(100000 * sizeof(char *));
    char line[MAX_WORD_LENGTH]; // Declare the line variable
    if (!words) {
        fclose(file);
        return NULL;
    }
    int wordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (strlen(line) >= MAX_WORD_LENGTH) {
            continue; // Skip overly long words
        }
        words[wordCount++] = strdup(line);
    }
    fclose(file);

    if (wordCount == 0) {
        free(words);  // Ensure that you free the words array even if no words are read
        return NULL;
    }

    srand(time(NULL));
    strcpy(wordBuffer, words[rand() % wordCount]);

    // Free the memory for each word before freeing the array itself
    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }
    free(words);  // Free the words array after freeing individual words
    return wordBuffer;
}