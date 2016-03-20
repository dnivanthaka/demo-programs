#!/usr/env python

# Demonstration of Caesar Cipher and Brute force attack on a Caesar ciper encrypted message.
# Author: D.N. Amerasinghe
MAX_KEY_SIZE = 26


def getMethod():
    while True:
        print("Do you wish to encrypt or decrypt a message?")
        mode = input().lower()
        if mode in 'encrypt e decrypt d'.split():
            return mode
        else:
            print("Enter either 'encrypt' or 'e' or 'decrypt' or 'd'.")

def getMessage():
    print("Enter your message: ")
    return input()

def getKey():
    while True:
        print('Enter key value (1 - %s):' % (MAX_KEY_SIZE))
        key = int(input())
        if( key < 1 or key > MAX_KEY_SIZE ):
            print('Enter between 1 and %s inclusive' % (MAX_KEY_SIZE))
        else:
            return key

def getTranslatedMessage(mode, message, key):
    translated = ''

    if( mode == 'd'  ):
        key = -key

    for symbol in message:
        if (symbol.isalpha()):
            #translated += chr( (ord(symbol) + key) % int(MAX_KEY_SIZE) )
            #translated += str(int(ord(symbol) + key))
            num = ord( symbol )
            num += key

            if( symbol.isupper() ):
                if( num > ord('Z') ):
                    num -= 26
                elif( num < ord('A') ):
                    num += 26
            elif( symbol.islower() ):
                if( num > ord('z') ):
                    num -= 26
                elif( num < ord('a') ):
                    num += 26
            translated += chr(num)
        else:
            translated += symbol

    return translated

method = getMethod()
message = getMessage()
key = getKey()

print("The Translated Message is :")
print( getTranslatedMessage(method, message, key) )
