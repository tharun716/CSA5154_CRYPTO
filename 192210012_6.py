def generate_key(message, key):
    key = list(key)
    if len(message) == len(key):
        return key
    else:
        for i in range(len(message) - len(key)):
            key.append(key[i % len(key)])
    return "".join(key)

def encrypt_vigenere(message, key):
    encrypted_message = []
    for i in range(len(message)):
        char = (ord(message[i]) + ord(key[i])) % 26
        char += ord('A')
        encrypted_message.append(chr(char))
    return "".join(encrypted_message)

def decrypt_vigenere(encrypted_message, key):
    decrypted_message = []
    for i in range(len(encrypted_message)):
        char = (ord(encrypted_message[i]) - ord(key[i]) + 26) % 26
        char += ord('A')
        decrypted_message.append(chr(char))
    return "".join(decrypted_message)

if __name__ == "__main__":
    message = "ATTACKATDAWN"
    keyword = "LEMON"
    
    key = generate_key(message, keyword)
    print("Generated Key:", key)
    
    encrypted_message = encrypt_vigenere(message, key)
    print("Encrypted Message:", encrypted_message)
    
    decrypted_message = decrypt_vigenere(encrypted_message, key)
    print("Decrypted Message:", decrypted_message)
