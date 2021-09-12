#include <cs50.h>
#include <stdio.h>
#include <math.h>

int amount, quarters, dimes, nickles, pennies;

int main(void)
{
    // Asks user how much change he is owed
    float dollars;
    do
    {
        dollars = get_float("Change owed: \n");
    }
    while (dollars < 0);

    // Rounds up the input to make calculations easier
    int cents = round(dollars * 100);

    //Calculations via if
    if (cents % 25 != 0)
    {
        quarters = cents / 25;
        if ((cents - (quarters * 25)) % 10 != 0)
        {
            dimes = (cents - (quarters * 25)) / 10;
            if ((cents - (quarters * 25 + dimes * 10)) % 5 != 0)
            {
                nickles = (cents - (quarters * 25 + dimes * 10)) / 5;
                pennies = (cents - (quarters * 25 + dimes * 10 + nickles * 5)) / 1;
            }
            else
            {
                nickles = (cents - (quarters * 25 + dimes * 10)) / 5;
            }
        }
        else
        {
            dimes = (cents - (quarters * 25)) / 10;
        }
    }
    else
    {
        quarters = cents / 25;
    }

    // Coins are summed
    amount = quarters + dimes + nickles + pennies;

    // Shows minimal number of coins with which the change can be made
    printf("%i\n", amount);
}