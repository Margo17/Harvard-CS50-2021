#include <cs50.h>
#include <stdio.h>

int startsize, endsize, years;

int main(void)
{
    // Prompt for start size

    do
    {
        startsize = get_int("What's the starting population size?\n");
    }
    while (startsize < 9);

    // Prompt for end size

    do
    {
        endsize = get_int("What's the ending population size?\n");
    }
    while (endsize < startsize);

    // Calculate number of years until we reach threshold

    while (startsize < endsize)
    {
        startsize = startsize + (startsize / 3) - (startsize / 4);
        years++;
    }

    // Print number of years

    printf("Years: %i\n", years);

}