#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count, digit, sum1, sum2;
long n, number, temp;

int main(void)
{
    // Prompt for input
    do
    {
        number = get_long("Type in credit card number\n");
    }
    while (number < 0);

    // Calculate the checksum
    // Checksum is the card authentication algorithm
    temp = number;
    while (temp > 0)
    {
        sum2 += temp % 10;
        temp /= 10;
        digit = temp % 10;
        if (digit >= 5)
        {
            sum1 += (digit * 2) % 10;
            sum1 += (digit * 2) / 10;
        }
        else
        {
            sum1 += digit * 2;
        }
        temp /= 10;
    }

    // Check for card lenght and starting digits
    // If above checks out print AMEX, VISA, MASTERCARD or INVALID
    if ((sum1 + sum2) % 10 == 0)
    {

        // Lenght check
        n = number;
        while (n > 0)
        {
            n = n / 10;
            count++;
        }

        // Sorting if AMEX, VISA, MASTERCARD or INVALID
        if (count == 15 && (number / 10000000000000 == 34 || number / 10000000000000 == 37))
        {
            printf("AMEX\n");
        }
        else if (count == 16 && (number / 100000000000000 == 51 || number / 100000000000000 == 52 || number / 100000000000000 == 53
                                 || number / 100000000000000 == 54 || number / 100000000000000 == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((count == 13 || count == 16) && (number / 1000000000000 == 4 || number / 1000000000000000 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}