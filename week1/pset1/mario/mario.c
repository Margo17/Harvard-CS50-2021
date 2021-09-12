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
        for (int space = height - row - 1; space > 0; space--)
        {
            printf(" ");
        }

        // Creates hashes inside the row
        for (int hash = 0; hash < row + 1; hash++)
        {
            printf("#");
        }

        // Creates the inside of the pyramid
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