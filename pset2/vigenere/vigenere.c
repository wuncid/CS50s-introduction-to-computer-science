#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

string vigenere_cipher(string text, string keyword);
// encrypts messages using Vigenere's cipher
int main(int argc, string argv[])
{
    // if the number of total input strings is two then continue
    if (argc == 2)
    {
        // initializes the key as a string
        string keyword = argv[1];

        // checks if all characters in the input string are alphabetic
        bool isCorrect = true;
        for (int i = 0; i < strlen(keyword); i++)
        {
            if (!isalpha(keyword[i]))
            {
                isCorrect = false;
            }
        }

        // exit the program if the key is not alphabetic
        if (!isCorrect)
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }

        // else continue
        else
        {
            // converts the keyword to lowercase
            for (int i = 0; i < strlen(keyword); i++)
            {
                keyword[i] = tolower(keyword[i]);
            }

            // gets the plain text input from the user
            string plainText = get_string("plaintext: ");
            string cipherText = vigenere_cipher(plainText, keyword);

            // prints the ciphered text
            printf("plaintext: %s\n", plainText);
            printf("ciphertext: %s\n", cipherText);
            free(cipherText);
            return 0;
        }
    }

    // else signify an error
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}

// function that ciphers the text
string vigenere_cipher(string text, string keyword)
{
    // copies the plain text to the cipher text variable
    string cipherText;
    cipherText = malloc(sizeof(char) * (strlen(text) + 1));
    strcpy(cipherText, text);

    int j = 0;
    for (int i = 0; i < strlen(cipherText); i++)
    {
        // checks if the character is alphabetical
        if (isalpha(cipherText[i]))
        {
            //calculates the key
            int key = keyword[j % strlen(keyword)] - 'a';
            // checks if the character is lowercase and if yes, then ciphers the character preserving the lowercase
            if (islower(cipherText[i]))
            {
                int alphaIndex = cipherText[i] - 'a';
                cipherText[i] = 'a' + (alphaIndex + key) % 26;
            }
            // checks if the character is uppercase and if yes, then ciphers the character preserving the Uppercase
            else if (isupper(cipherText[i]))
            {
                int alphaIndex = cipherText[i] - 'A';
                cipherText[i] = 'A' + (alphaIndex + key) % 26;
            }
            j++;
        }
    }
    // returns the ciphered text
    return cipherText;
}