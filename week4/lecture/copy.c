#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Valgrind helps with memory problems, run as valgrind ./program

// Shortcut for this is funtion strcopy()
int main(void)
{
    char *s = get_string("text: ");

    char *t = malloc(strlen(s) + 1); // malloc allocates memory, output of malloc is an adress of the first byte.
    if (t == NULL) // NULL is 0 pointer a bogus address
    {
        return 1;
    }

    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    if (strlen(s) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t); // Frees up the allocated memory
}