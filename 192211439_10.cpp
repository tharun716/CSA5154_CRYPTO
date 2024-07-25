#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RSA_KEY_SIZE 512

// Function to calculate (base^exponent) % modulus
long long mod_exp(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to find greatest common divisor (GCD)
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find modular inverse
long long mod_inv(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to check if a number is prime
int is_prime(long long num) {
    if (num <= 1)
        return 0;
    if (num <= 3)
        return 1;
    if (num % 2 == 0 || num % 3 == 0)
        return 0;
    for (long long i = 5; i * i <= num; i += 6)
        if (num % i == 0 || num % (i + 2) == 0)
            return 0;
    return 1;
}

// Function to generate RSA keys
void generate_keys(long long *n, long long *e, long long *d) {
    long long p = 61;  // Example prime number
    long long q = 53;  // Example prime number
    long long phi, k;

    // Compute n = p * q
    *n = p * q;

    // Compute phi(n) = (p - 1) * (q - 1)
    phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    *e = 17;  // Example value of e

    // Compute d such that (d * e) % phi = 1
    *d = mod_inv(*e, phi);
}

// RSA encryption
long long rsa_encrypt(long long plaintext, long long e, long long n) {
    return mod_exp(plaintext, e, n);
}

// RSA decryption
long long rsa_decrypt(long long ciphertext, long long d, long long n) {
    return mod_exp(ciphertext, d, n);
}

int main() {
    long long n, e, d;
    long long plaintext = 65; // Example plaintext
    long long ciphertext, decryptedtext;

    generate_keys(&n, &e, &d);

    printf("Public Key: (e: %lld, n: %lld)\n", e, n);
    printf("Private Key: (d: %lld, n: %lld)\n", d, n);

    // Encrypt the plaintext
    ciphertext = rsa_encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %lld\n", ciphertext);

    // Decrypt the ciphertext
    decryptedtext = rsa_decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %lld\n", decryptedtext);

    return 0;
}

