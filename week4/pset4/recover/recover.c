#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Remember filename
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Initialise variables
    BYTE buffer[512];
    int count = 0;
    FILE *outptr = NULL;
    char filename[8];

    // Repeat until end of card:
    while (fread(&buffer, 512, 1, inptr) == 1)
    {

        // If start of a new JPEG (0xff 0xd8 0xff 0xe*), bitwise arithmetic is used for the last bit:
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            // If not first JPEG, close previous
            if (!(count == 0))
            {
                fclose(outptr);
            }

            // Initialise file
            sprintf(filename, "%03i.jpg", count);
            outptr = fopen(filename, "w");
            count++;
        }

        // If JPEG has been found, write to file
        if (!(count == 0))
        {
            fwrite(&buffer, 512, 1, outptr);
        }
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}