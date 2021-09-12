#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int keylength = 26;
const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{

    // Check if argument number is correct
    if (argc != 2 || strlen(argv[1]) != 26)
    {
        printf("Type in one command line argument only.\n");
        return 1;
    }

    // Check if command line argument is valid
    int temp[keylength];
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {

        // 1) Are alphabetic characters used only?
        if (!((argv[1][i] >= 'a' && argv[1][i] <= 'z') ||
              (argv[1][i] >= 'A' && argv[1][i] <= 'Z')))
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }

        // Convert to uppercase
        else if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
        {
            argv[1][i] = toupper(argv[1][i]);
        }

        // Check for repeated letters
        for (int j = 0; j < keylength; j++)
        {
            if (argv[1][i] == temp[j])
            {
                printf("Key must not contain repeated alphabetic characters.\n");
                return 1;
            }
        }
        temp[i] = argv[1][i];
    }

    // Ask for plaintext input
    string plaintext = get_string("plaintext: ");
    int l = strlen(plaintext);
    char ciphertext[l + 1];

    // Encrypting text
    for (int i = 0; i < l; i++)
    {

        // Check if uppercase and if true alphabet tracks character's position and then key is used to assign key symbol to output
        if (isupper(plaintext[i]))
        {
            for (int j = 0; j < keylength; j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    ciphertext[i] = argv[1][j];
                    break;
                }
            }
        }

        // Same process for lowercase just coverting alphabet tolower
        else if (islower(plaintext[i]))
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                if (plaintext[i] == tolower(alphabet[j]))
                {
                    ciphertext[i] = tolower(argv[1][j]);
                    break;
                }
            }
        }

        // Non alphabetical characters are not changed
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }

    // Add null character to make ciphertext char array a string
    ciphertext[l] = '\0';

    // Print out the result and quit
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}