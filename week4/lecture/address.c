#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char *s = "Hi!";
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));
}