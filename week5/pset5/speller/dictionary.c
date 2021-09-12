// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table, N coefficient found by trial and error as 27000 gives the fastest check function speed (0.1s).
const unsigned int N = 27000;

// Hash table
node *table[N] = { NULL };

// Word count initialisation
unsigned int dictionary_words;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Obtain hash value
    int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }

    // Access linked list at the obtained index in the hash table
    node *cursor = table[index];

    // Traverse linked list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // DJB2 hash function algorithm from: http://www.cse.yorku.ca/~oz/hash.html, C++ example translated into C language.
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        // (hash * 2^5 + hash) + c
        hash = ((hash << 5) + hash) + tolower(c);
    }

    // Modulo of N to not exceed the number of buckets in the hash table
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file, check if not NULL
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read words one at a time
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // New node, check if not NULL
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy word into the node
        strcpy(n->word, word);
        n->next = NULL;

        // Use hash function to obtain a hash value
        int index = hash(word);

        // Insert the node into a hash table
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        // Increment word amount
        dictionary_words++;
    }

    // Close file
    fclose(file);

    // True - if dictionary is loaded
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the hash table
    for (int i = 0; i < N; i++)
    {
        // Initialize nodes for deleting a chain
        node *cursor = table[i], *tmp = table[i];

        // Deleting nodes
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}