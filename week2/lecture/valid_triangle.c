#include <cs50.h>
#include <stdio.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
    float a = get_float("Give triangle side a:\n");
    float b = get_float("Give triangle side b:\n");
    float c = get_float("Give triangle side c:\n");
    valid_triangle(a, b, c);
}

bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <= 0 || c <= 0)
    {
        printf("Triangle INVALID\n");
        return false
    }
    else if (a + b > c && b + c > a && a + c > b)
    {
        printf("Triangle VALID\n");
        return true;
    }
    else
    {
        printf("Triangle INVALID\n");
        return false;
    }
}