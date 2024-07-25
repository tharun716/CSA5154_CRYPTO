#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
#define ALPHABET_SIZE 26

void createMatrix(char key[], char matrix[SIZE][SIZE]);
void preprocessMessage(char message[], char preprocessed[]);
void encryptMessage(char preprocessed[], char encrypted[], char matrix[SIZE][SIZE]);
void findPosition(char ch, char matrix[SIZE][SIZE], int *row, int *col);
void printMatrix(char matrix[SIZE][SIZE]);

int main() {
    char key[] = "MFHIKUNOPQZVWXYLEARGDSTBC";
    char matrix[SIZE][SIZE];
    char message[] = "Must see you over Cadogan West. Coming at once";
    char preprocessed[256];
    char encrypted[256];

    createMatrix(key, matrix);

    printf("Playfair Matrix:\n");
    printMatrix(matrix);

    preprocessMessage(message, preprocessed);

    encryptMessage(preprocessed, encrypted, matrix);

    printf("Original message: %s\n", message);
    printf("Preprocessed message: %s\n", preprocessed);
    printf("Encrypted message: %s\n", encrypted);

    return 0;
}

void createMatrix(char key[], char matrix[SIZE][SIZE]) {
    int used[ALPHABET_SIZE] = {0};
    int k = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (key[k] == 'J') {
                key[k] = 'I'; // Treat 'I' and 'J' as the same letter
            }
            if (!used[key[k] - 'A']) {
                matrix[i][j] = key[k];
                used[key[k] - 'A'] = 1;
            }
            k++;
        }
    }
}

void preprocessMessage(char message[], char preprocessed[]) {
    int length = strlen(message);
    int k = 0;

    for (int i = 0; i < length; i++) {
        if (isalpha(message[i])) {
            preprocessed[k++] = toupper(message[i]);
        }
    }

    preprocessed[k] = '\0';

    // Insert 'X' between duplicate letters in pairs and at the end if needed
    char temp[256];
    int j = 0;
    for (int i = 0; i < k; i++) {
        temp[j++] = preprocessed[i];
        if (i < k - 1 && preprocessed[i] == preprocessed[i + 1]) {
            temp[j++] = 'X';
        }
    }
    temp[j] = '\0';

    if (strlen(temp) % 2 != 0) {
        temp[j++] = 'X';
        temp[j] = '\0';
    }

    strcpy(preprocessed, temp);
}

void encryptMessage(char preprocessed[], char encrypted[], char matrix[SIZE][SIZE]) {
    int length = strlen(preprocessed);
    int row1, col1, row2, col2;

    for (int i = 0; i < length; i += 2) {
        findPosition(preprocessed[i], matrix, &row1, &col1);
        findPosition(preprocessed[i + 1], matrix, &row2, &col2);

        if (row1 == row2) {
            encrypted[i] = matrix[row1][(col1 + 1) % SIZE];
            encrypted[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encrypted[i] = matrix[(row1 + 1) % SIZE][col1];
            encrypted[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            encrypted[i] = matrix[row1][col2];
            encrypted[i + 1] = matrix[row2][col1];
        }
    }

    encrypted[length] = '\0';
}

void findPosition(char ch, char matrix[SIZE][SIZE], int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void printMatrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

