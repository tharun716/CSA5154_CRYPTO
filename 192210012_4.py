def create_matrix(key):
    key = key.upper().replace("J", "I")
    matrix = [[0 for _ in range(5)] for _ in range(5)]
    letters_added = []
    row, col = 0, 0
    
    for letter in key:
        if letter not in letters_added:
            matrix[row][col] = letter
            letters_added.append(letter)
            if col == 4:
                col = 0
                row += 1
            else:
                col += 1

    for letter in range(65, 91):  # ASCII values for A-Z
        if letter == 74:  # Skip J
            continue
        if chr(letter) not in letters_added:
            letters_added.append(chr(letter))

    index = 0
    for i in range(5):
        for j in range(5):
            matrix[i][j] = letters_added[index]
            index += 1
            
    return matrix

def separate_same_letters(message):
    index = 0
    while index < len(message):
        l1 = message[index]
        if index == len(message) - 1:
            message += 'X'
            index += 2
            continue
        l2 = message[index + 1]
        if l1 == l2:
            message = message[:index + 1] + "X" + message[index + 1:]
        index += 2
    return message

def indexOf(letter, matrix):
    for i in range(5):
        try:
            index = matrix[i].index(letter)
            return i, index
        except ValueError:
            continue
    return None

def playfair(key, message, encrypt=True):
    inc = 1 if encrypt else -1
    matrix = create_matrix(key)
    message = message.upper().replace(' ', '')
    message = separate_same_letters(message)
    cipher_text = ''
    
    for (l1, l2) in zip(message[0::2], message[1::2]):
        row1, col1 = indexOf(l1, matrix)
        row2, col2 = indexOf(l2, matrix)
        
        if row1 == row2:
            cipher_text += matrix[row1][(col1 + inc) % 5] + matrix[row2][(col2 + inc) % 5]
        elif col1 == col2:
            cipher_text += matrix[(row1 + inc) % 5][col1] + matrix[(row2 + inc) % 5][col2]
        else:
            cipher_text += matrix[row1][col2] + matrix[row2][col1]
    
    return cipher_text

if __name__ == '__main__':
    print('Encrypting')
    print(playfair('secret', 'my secret message'))
    print('Decrypting')
    print(playfair('secret', 'LZECRTCSITCVAHBT', False))
