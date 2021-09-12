#include <stdio.h>

// Prototype
void meow(void);

int main(void)
{
    // For has initialisation, condition, incrementation
    for (int i = 0; i < 5; i++)
    {
        meow(3);
    }
}

void meow(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("meow\n");
    }
}
