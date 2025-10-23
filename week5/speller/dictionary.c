// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_val = hash(word);

    for(node *temp = table[hash_val]; temp != NULL; temp = temp->next)
    {
        if(strcasecmp(temp->word, word) == 0){
            return true;
        };
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        printf("Error opening dict\n");
        return false;
    };

    char buffer[LENGTH + 1];

    while(fscanf(dict, "%s", buffer) != EOF){
        node *new_word = malloc(sizeof(node));

        int hash_val = hash(buffer);

        strcpy(new_word->word, buffer);
        new_word->next = table[hash_val];
        table[hash_val] = new_word;

        word_count++;
    };
    
    fclose(dict);
 
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while(cursor != NULL)
        {
            node *temp = cursor->next;
            free(cursor);
            cursor = temp;
        };
    };
      
    return true;
}
