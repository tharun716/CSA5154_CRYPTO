#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

// DES encryption function
void des_encrypt(const char *plain_text, char *cipher_text, const DES_cblock *key) {
    DES_key_schedule schedule;
    DES_cblock block;
    DES_set_key_unchecked(key, &schedule);
    memcpy(block, plain_text, DES_BLOCK_SIZE);
    DES_ecb_encrypt(&block, (DES_cblock *)cipher_text, &schedule, DES_ENCRYPT);
}

// DES decryption function
void des_decrypt(const char *cipher_text, char *plain_text, const DES_cblock *key) {
    DES_key_schedule schedule;
    DES_cblock block;
    DES_set_key_unchecked(key, &schedule);
    memcpy(block, cipher_text, DES_BLOCK_SIZE);
    DES_ecb_encrypt((DES_cblock *)cipher_text, &block, &schedule, DES_DECRYPT);
    memcpy(plain_text, block, DES_BLOCK_SIZE);
}

int main() {
    DES_cblock key = "12345678"; // Key size is exactly 8 bytes
    char plaintext[DES_BLOCK_SIZE + 1] = "HELLO123"; // +1 for null terminator
    char ciphertext[DES_BLOCK_SIZE];
    char decryptedtext[DES_BLOCK_SIZE + 1]; // +1 for null terminator

    printf("Original plaintext: %s\n", plaintext);

    des_encrypt(plaintext, ciphertext, &key);
    printf("Encrypted ciphertext: ");
    for (int i = 0; i < DES_BLOCK_SIZE; i++)
        printf("%02X", (unsigned char)ciphertext[i]);
    printf("\n");

    des_decrypt(ciphertext, decryptedtext, &key);
    decryptedtext[DES_BLOCK_SIZE] = '\0'; // Null-terminate the decrypted string
    printf("Decrypted plaintext: %s\n", decryptedtext);

    return 0;
}

