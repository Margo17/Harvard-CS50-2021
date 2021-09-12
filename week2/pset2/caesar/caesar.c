#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char uppercase[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char lowercase[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int main(int argc, string argv[])
{
    // Check if comand line argument was just one
    if (argc == 2)
    {
        // Checking if all characters are digits
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        // Convert cmd line argument to an in
        int k = atoi(argv[1]);

        // Prompt for plain text
        string plaintext = get_string("plaintext: ");
        char ciphertext[strlen(plaintext)];

        // Cyphering text
        int i = 0;
        for (int len = strlen(plaintext); i < len; i++)
        {
            if (isalpha(plaintext[i]))
            {
                if (isupper(plaintext[i]))
                {
                    ciphertext[i] = uppercase[(plaintext[i] - 'A' + k) % 26];
                }
                if (islower(plaintext[i]))
                {
                    ciphertext[i] = lowercase[(plaintext[i] - 'a' + k) % 26];
                }
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
        }
        // When building a string from chars \0 indicates the word ending
        ciphertext[i] = '\0';

        // Print out cyphertext
        printf("ciphertext: %s\n", ciphertext);

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}