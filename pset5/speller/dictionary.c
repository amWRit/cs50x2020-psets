// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>
#include <string.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 100000; // random value

// Hash table
node *table[N];
int word_count;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the word using hash func to get index for the table
    int index = hash(word);

    // access linked list at that index in the table
    node *cursor = table[index]; // cursor set to first item in the table at that index

    if (cursor == NULL)
    {
        return false;
    }

    // traverse the linked list looking for the word until end of linked list
    while (cursor != NULL)
    {
        // case insensitive comparing - returns 0 if strings are equal
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // move cursor to the next node
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
// String folding hash function || https://opendsa-server.cs.vt.edu/ODSA/Books/Everything/html/HashFuncExamp.html
// This function takes a string as input. It processes the string four bytes at a time,
// and interprets each of the four-byte chunks as a single long integer value.
// The integer values for the four-byte chunks are added together.

// For example, if the string "aaaabbbb" is passed to sfold, then the first four bytes ("aaaa")
// will be interpreted as the integer value 1,633,771,873, and the next four bytes ("bbbb") will be
// interpreted as the integer value 1,650,614,882. Their sum is 3,284,386,755 (when treated as an unsigned integer).
// If the table size is 101 then the modulus function will cause this key to hash to slot 75 in the table.

unsigned int hash(const char *word)
{
    int index = 0;

    // traverse through the whole word of the word to be hashed
    // for(int i = 0; word[i] != '\0'; i++)
    // {
    //     // add up the index per char of the word
    //     // toupper just to make sure it is not case sensitive
    //     index += toupper(word[i]);
    // }

    // to limit within the table size N
    // return index % N;

    long sum = 0, mul = 1;
    for (int i = 0; word[i] != '\0'; i++)
    {
        mul = (i % 4 == 0) ? 1 : mul * 256;
        index += tolower(word[i]) * mul;
    }

    // to limit within the table size N
    return (int)(abs(index) % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read strings from file one word at a time
    char word[LENGTH + 1];
    word_count = 0;

    while (fscanf(file, "%s", word) != EOF)
    {
        // create a new node for each word and copy word into node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            unload();
            return false;
        }
        else
        {
            // copy the word into the new node
            strcpy(n->word, word);
            n->next = NULL;

            // use hash func to get index number for that node
            int index = hash(word);

            // insert the node into hash table at that index
            n->next = table[index];
            table[index] = n;

            word_count++;
        }

    }

    fclose(file);
    return true;;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // traverse through all the contents in hash table - until N

    for (int i = 0; i < N; i++)
    {
        // create a node pointer to current hash table index
        node *cursor = table[i];

        //traverse through the linked lists of that index
        while (cursor != NULL)
        {
            node *temp_cur = cursor; //set temp to current cursor, so as not to orphan current cursor pointees
            cursor = cursor->next; //set current cursor to the next node
            free(temp_cur); //free temp cursor so that it frees the node it is pointing at
        }
    }

    return true;
}
