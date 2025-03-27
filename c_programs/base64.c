// File:   base64.c
// Author: Gregory K. Bowne
// Date:   9 AUG 2024// Time:   1:31 
// Brief:  This program does base64 with no particular algorithm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BASE64_CHAR_COUNT 64
#define BLOCK_SIZE 3
#define PADDING_CHAR '='

static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int8_t base64_index[256];

// Pre-calculate base64 character indices for faster lookup
static void init_base64_index() {
    memset(base64_index, -1, sizeof(base64_index));
    for (int i = 0; i < BASE64_CHAR_COUNT; i++) {
        base64_index[(unsigned char)base64_chars[i]] = i;
    }
}

static char *base64_encode(const unsigned char *input, size_t length) {
    size_t output_length = 4 * ((length + 2) / 3);
    char *encoded = malloc(output_length + 1);
    if (!encoded) return NULL;

    for (size_t i = 0, j = 0; i < length;) {
        uint32_t octet_a = i < length ? input[i++] : 0;
        uint32_t octet_b = i < length ? input[i++] : 0;
        uint32_t octet_c = i < length ? input[i++] : 0;

        uint32_t triple = (octet_a << 16) + (octet_b << 8) + octet_c;

        encoded[j++] = base64_chars[(triple >> 18) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 12) & 0x3F];
        encoded[j++] = base64_chars[(triple >> 6) & 0x3F];
        encoded[j++] = base64_chars[triple & 0x3F];
    }

    for (size_t i = 0; i < (3 - length % 3) % 3; i++)
        encoded[output_length - 1 - i] = PADDING_CHAR;

    encoded[output_length] = '\0';
    return encoded;
}

static unsigned char *base64_decode(const char *input, size_t *output_length) {
    size_t input_length = strlen(input);
    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (input[input_length - 1] == PADDING_CHAR) (*output_length)--;
    if (input[input_length - 2] == PADDING_CHAR) (*output_length)--;

    unsigned char *decoded = malloc(*output_length);
    if (!decoded) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        int sextet_a = base64_index[(unsigned char)input[i++]];
        int sextet_b = base64_index[(unsigned char)input[i++]];
        int sextet_c = (i < input_length) ? base64_index[(unsigned char)input[i++]] : 0;
        int sextet_d = (i < input_length) ? base64_index[(unsigned char)input[i++]] : 0;

        if (sextet_a == -1 || sextet_b == -1 || 
            (sextet_c == -1 && input[i-1] != PADDING_CHAR) || 
            (sextet_d == -1 && input[i-1] != PADDING_CHAR)) {
            free(decoded);
            return NULL;
        }

        uint32_t triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

        if (j < *output_length) decoded[j++] = (triple >> 16) & 0xFF;
        if (j < *output_length) decoded[j++] = (triple >> 8) & 0xFF;
        if (j < *output_length) decoded[j++] = triple & 0xFF;
    }

    return decoded;
}

int main() {
    init_base64_index();
    char choice;
    char input[1024];
    
    printf("Choose operation (e for encode, d for decode): ");
    scanf(" %c", &choice);
    getchar();  // Consume newline character left by scanf

    if (choice == 'e') {
        printf("Enter string to encode: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline character from input

        char *encoded = base64_encode((const unsigned char *)input, strlen(input));
        if (!encoded) {
            fprintf(stderr, "Failed to encode\n");
            return 1;
        }
        printf("Encoded: %s\n", encoded);
        free(encoded);
    } else if (choice == 'd') {
        printf("Enter base64 string to decode: ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove newline character from input

        size_t decoded_length;
        unsigned char *decoded = base64_decode(input, &decoded_length);
        if (!decoded) {
            fprintf(stderr, "Failed to decode\n");
            return 1;
        }
        printf("Decoded: %.*s\n", (int)decoded_length, decoded);
        free(decoded);
    } else {
        fprintf(stderr, "Invalid choice\n");
        return 1;
    }

    return 0;
}
