#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// encrypts messages using Caesar's cipher
int main(int argc, string argv[])
{
    // if the number of total input strings is two and the second input is an integer, then continue
    if (argc == 2 && atoi(argv[1]) != 0)
    {
        // initializes the key as an integer
        int key = atoi(argv[1]);

        // gets the plain text input from the user
        string plainText = get_string("plaintext: ");

        // copies the plain text to cipher text variable
        string cipherText;
        cipherText = malloc(sizeof(char) * (strlen(plainText) + 1));
        strcpy(cipherText, plainText);

        // goes through the characters of the plain text
        for (int i = 0; i < strlen(cipherText); i++)
        {
            // checks if the character is alphabetical
            if (isalpha(cipherText[i]))
            {
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
            }
        }
        // prints the ciphered text
        printf("ciphertext: %s\n", cipherText);
        free(cipherText);
        return 0;
    }

    // else signify an error
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}

