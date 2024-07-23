def create_matrix_from(key):
    m = [[0] * 3 for _ in range(3)]
    for i in range(3):
        for j in range(3):
            m[i][j] = ord(key[3 * i + j]) % 65
    return m

def matrix_determinant_2x2(matrix):
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]

def matrix_determinant(matrix):
    return (matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1])
          - matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0])
          + matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]))

def matrix_minor(matrix, i, j):
    return [[matrix[x][y] for y in range(3) if y != j] for x in range(3) if x != i]

def matrix_cofactor(matrix):
    cofactor_matrix = [[0] * 3 for _ in range(3)]
    for i in range(3):
        for j in range(3):
            minor = matrix_minor(matrix, i, j)
            cofactor_matrix[i][j] = ((-1) ** (i + j)) * matrix_determinant_2x2(minor)
    return cofactor_matrix

def matrix_transpose(matrix):
    return [[matrix[j][i] for j in range(3)] for i in range(3)]

def matrix_mod_inverse(matrix, modulus):
    determinant = matrix_determinant(matrix)
    determinant_inv = pow(determinant, -1, modulus)
    cofactor_matrix = matrix_cofactor(matrix)
    adjugate_matrix = matrix_transpose(cofactor_matrix)
    inverse_matrix = [[(determinant_inv * adjugate_matrix[i][j]) % modulus for j in range(3)] for i in range(3)]
    return inverse_matrix

def encrypt(P, K):
    C = [0, 0, 0]
    C[0] = (K[0][0] * P[0] + K[0][1] * P[1] + K[0][2] * P[2]) % 26
    C[1] = (K[1][0] * P[0] + K[1][1] * P[1] + K[1][2] * P[2]) % 26
    C[2] = (K[2][0] * P[0] + K[2][1] * P[1] + K[2][2] * P[2]) % 26
    return C

def Hill(message, K):
    cipher_text = []
    for i in range(0, len(message), 3):
        P = [ord(message[i + j]) % 65 for j in range(3)]
        C = encrypt(P, K)
        cipher_text.extend([chr(c + 65) for c in C])
    return "".join(cipher_text)

if __name__ == "__main__":
    message = "MYSECRETMESSAGE"
    key = "RRFVSVCCT"
    K = create_matrix_from(key)
    print("Key matrix:")
    for row in K:
        print(row)
    
    cipher_text = Hill(message, K)
    print('Cipher text:', cipher_text)
    
    K_inv = matrix_mod_inverse(K, 26)
    print("Inverse key matrix:")
    for row in K_inv:
        print(row)
    
    plain_text = Hill(cipher_text, K_inv)
    print('Plain text:', plain_text)
    
    M = [[sum(a * b for a, b in zip(K_row, K_inv_col)) % 26 for K_inv_col in zip(*K_inv)] for K_row in K]
    print("Verification matrix (should be identity matrix):")
    for row in M:
        print(row)
