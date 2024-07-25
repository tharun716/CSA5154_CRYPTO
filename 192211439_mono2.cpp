#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherSequence(char *keyword, char *cipher);
void encrypt(char *plaintext, char *ciphertext, char *cipher);
void decrypt(char *ciphertext, char *plaintext, char *cipher);

int main() {
    char keyword[] = "CIPHER";
    char cipher[ALPHABET_SIZE + 1];
    char plaintext[256], ciphertext[256];

    // Generate the cipher sequence from the keyword
    generateCipherSequence(keyword, cipher);

    // Display the cipher sequence
    printf("Generated cipher sequence:\n");
    printf("plain:  ");
    for (char ch = 'a'; ch <= 'z'; ch++) {
        printf("%c ", ch);
    }
    printf("\ncipher: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipher[i]);
    }
    printf("\n");

    // Get the plaintext input from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Encrypt the plaintext
    encrypt(plaintext, ciphertext, cipher);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, plaintext, cipher);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

void generateCipherSequence(char *keyword, char *cipher) {
    int i, j;
    int used[ALPHABET_SIZE] = {0}; // Track used letters
    int keyword_len = strlen(keyword);

    // Add keyword to cipher sequence
    for (i = 0, j = 0; i < keyword_len; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipher[j++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    // Add remaining letters to cipher sequence
    for (i = 0; i < ALPHABET_SIZE; i++) {
        if (!used[i]) {
            cipher[j++] = 'A' + i;
        }
    }
    cipher[j] = '\0';
}

void encrypt(char *plaintext, char *ciphertext, char *cipher) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int is_upper = isupper(plaintext[i]);
            int index = toupper(plaintext[i]) - 'A';
            ciphertext[i] = is_upper ? cipher[index] : tolower(cipher[index]);
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain the same
        }
    }
    ciphertext[i] = '\0';
}

void decrypt(char *ciphertext, char *plaintext, char *cipher) {
    int i, j;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int is_upper = isupper(ciphertext[i]);
            char ch = toupper(ciphertext[i]);
            for (j = 0; j < ALPHABET_SIZE; j++) {
                if (cipher[j] == ch) {
                    plaintext[i] = is_upper ? 'A' + j : 'a' + j;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain the same
        }
    }
    plaintext[i] = '\0';
}

