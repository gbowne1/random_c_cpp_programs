#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 46 // Adjusted to accommodate words up to 45 characters plus null terminator
#define MAX_WORDS 100000   // Maximum number of words to read from the dictionary
#define DEFAULT_DICTIONARY_FILE "words.txt" // Fallback dictionary file

// Function prototypes
void displayWord(const char *word, const int *guessed);
void displayHangman(int tries);
const char *selectRandomWord(const char *filePath, char *wordBuffer);

// Function to get the dictionary file path based on the OS
const char *getDictionaryFilePath() {
#ifdef _WIN32
    return "C:\\path\\to\\your\\custom\\dictionary.txt"; // Windows custom path
#elif __linux__
    return "/usr/share/dict/words"; // Common Linux dictionary path
#elif __APPLE__
    return "/usr/share/dict/words"; // Common macOS dictionary path
#elif __FreeBSD__ || __NetBSD__ || __OpenBSD__
    return "/usr/share/dict/words"; // Common BSD dictionary path
#else
    return DEFAULT_DICTIONARY_FILE; // Fallback for other systems
#endif
}

int main(int argc, char *argv[]) {
    char word[MAX_WORD_LENGTH];
    const char *dictionaryFile = (argc > 1) ? argv[1] : DEFAULT_DICTIONARY_FILE;

    if (!selectRandomWord(dictionaryFile, word)) {
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
        fprintf(stderr, "Error: Could not open dictionary file: %s\n", filePath);
        return NULL;
    }

    char **words = malloc(MAX_WORDS * sizeof(char *));
    if (!words) {
        fclose(file);
        fprintf(stderr, "Error: Memory allocation failed for words array.\n");
        return NULL;
    }

    char line[46]; // Adjusted to 46 to accommodate words up to 45 characters plus null terminator
    int wordCount = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline character
        if (strlen(line) >= 45) {
            continue; // Skip overly long words
        }
        char *wordCopy = strdup(line); // Duplicate the line
        if (!wordCopy) {
            // Free previously allocated words before returning NULL
            for (int i = 0; i < wordCount; i++) {
                free(words[i]);
            }
            free(words);
            fclose(file);
            fprintf(stderr, "Error: Memory allocation failed for word: %s\n", line);
            return NULL;
        }
        words[wordCount++] = wordCopy; // Store the duplicated word
    }
    fclose(file);

    if (wordCount == 0) {
        free(words);  // Free the words array if no words are read
        fprintf(stderr, "Error: No valid words found in the dictionary file.\n");
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



