#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE64_CHAR_COUNT 64
#define BLOCK_SIZE 3
#define PADDING_BYTE '='

// Pre-calculate base64 character indices for faster lookup
static int base64_index(char c) {
    static int indices[BASE64_CHAR_COUNT];
    if (indices[c] != -1) return indices[c];
    indices[c] = strchr(base64_chars, c) - base64_chars;
    return indices[c];
}

static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char padding_char = PADDING_BYTE;

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

    for (size_t i = 0; i < (BLOCK_SIZE - length % BLOCK_SIZE); i++)
        encoded[output_length - 1 - i] = padding_char;

    encoded[output_length] = '\0';
    return encoded;
}

static unsigned char *base64_decode(const char *input, size_t *output_length) {
    size_t input_length = strlen(input);
    if (input_length % 4 != 0 || strchr(input, padding_char) > 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (input[input_length - 1] == padding_char) (*output_length)--;
    if (input[input_length - 2] == padding_char) (*output_length)--;

    unsigned char *decoded = malloc(*output_length);
    if (!decoded) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = input[i] == padding_char ? 0 : base64_index(input[i++]);
        uint32_t sextet_b = input[i] == padding_char ? 0 : base64_index(input[i++]);
        uint32_t sextet_c = input[i] == padding_char ? 0 : base64_index(input[i++]);
        uint32_t sextet_d = input[i] == padding_char ? 0 : base64_index(input[i++]);

        uint32_t triple = (sextet_a << 18) + (sextet_b << 12) + (sextet_c << 6) + sextet_d;

        if (j < *output_length) decoded[j++] = (triple >> 16) & 0xFF;
        if (j < *output_length) decoded[j++] = (triple >> 8) & 0xFF;
        if (j < *output_length) decoded[j++] = triple & 0xFF;
    }

    return decoded;
}

int main() {
    const char *original = "Hello, Base64!";
    char *encoded = base64_encode((const unsigned char *)original, strlen(original));
    printf("Encoded: %s\n", encoded);

    size_t decoded_length;
    unsigned char *decoded = base64_decode(encoded, &decoded_length);
    printf("Decoded: %.*s\n", (int)decoded_length, decoded);

    free(encoded);
    free(decoded);
    return 0;
}