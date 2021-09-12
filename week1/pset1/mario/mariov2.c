#include <cs50.h>
#include <stdio.h>

int height;

int main(void)
{
    // Asks for an input from the user
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Creates pyramid rows
    for (int row = 0; row < height; row++)
    {

        // Creates spaces inside the row
        for (int line = 0; line < height; line++)
        {
            if (row + line < height - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }

        printf("  ");

        // Creates a second line of hashes inside the row
        for (int hash2 = 0; hash2 < row + 1; hash2++)
        {
            printf("#");
        }

        // Jumps to a new row
        printf("\n");
    }
}