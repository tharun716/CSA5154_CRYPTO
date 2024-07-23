import math

def create_grid(message, key):
    num_rows = math.ceil(len(message) / len(key))
    grid = [['' for _ in range(len(key))] for _ in range(num_rows)]
    
    k = 0
    for i in range(num_rows):
        for j in range(len(key)):
            if k < len(message):
                grid[i][j] = message[k]
                k += 1
    
    return grid

def encrypt_transposition(message, key):
    key_order = sorted(list(key))
    grid = create_grid(message, key)
    
    cipher_text = ''
    for k in key_order:
        col_idx = key.index(k)
        for row in grid:
            if row[col_idx] != '':
                cipher_text += row[col_idx]
                
    return cipher_text

def decrypt_transposition(cipher, key):
    num_cols = len(key)
    num_rows = math.ceil(len(cipher) / num_cols)
    num_shaded_boxes = (num_cols * num_rows) - len(cipher)
    
    key_order = sorted(list(key))
    col_lengths = {k: num_rows for k in key}
    for i in range(num_shaded_boxes):
        col_lengths[key_order[num_cols - 1 - i]] -= 1

    index = 0
    grid = [['' for _ in range(num_cols)] for _ in range(num_rows)]
    for k in key_order:
        col_idx = key.index(k)
        for row in range(col_lengths[k]):
            if index < len(cipher):
                grid[row][col_idx] = cipher[index]
                index += 1
    
    plain_text = ''
    for row in grid:
        plain_text += ''.join(row)
    
    return plain_text.strip()

if __name__ == "__main__":
    message = "WEAREDISCOVEREDFLEEATONCE"
    key = "ZEBRAS"
    
    encrypted_message = encrypt_transposition(message, key)
    print("Encrypted Message:", encrypted_message)
    
    decrypted_message = decrypt_transposition(encrypted_message, key)
    print("Decrypted Message:", decrypted_message)
