#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Asks for name
    string name = get_string("What's your name?\n");
    
    // Prints the name
    printf("hello, %s\n", name);
}