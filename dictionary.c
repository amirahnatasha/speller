// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 150000;

// Hash table
node *table[N];

//Dictionary size or number of nodes
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //change word to lowercase
    size_t len = strlen(word);
    char *lower = calloc(len+1, sizeof(char));

    for (size_t i = 0; i < len; ++i) {
        lower[i] = tolower((unsigned char)word[i]);
    }


    int index = hash(lower);
    node *tmp = table[index];
    while (tmp != NULL && strcasecmp(tmp->word, lower) != 0) {
        tmp = tmp->next;
    }
    free(lower);

    if (tmp == NULL) {
        return false;
    } else {
        return true;
    }

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //Function takes a string and returns an index
    int length = strlen(word);

    unsigned int hash_value = 0;

    for (int i = 0; i < length; i++) {
        hash_value += word[i];
        hash_value = hash_value *word[i];
    }

    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open dictionary file
    FILE *f = fopen(dictionary, "r");
    if(f == NULL)
    {
        return false;
    }

    //Initialize caharcter array
    char word[LENGTH + 1];

    //Read strings from file
    while (fscanf(f, "%s", word) != EOF)
    {
        //Create new node for each word
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
            return false;
        }

        //Copy word into node
        strcpy(n->word, word);

        //Insert node into hash table
        int hash_value = hash(word);

        n->next = table[hash_value];
        table[hash_value] = n;
        dict_size++;
    }

    //Close file
    fclose(f);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) {
        node *nxt;
        for (node *cur = table[i];  cur != NULL;  cur = nxt) {
            nxt = cur->next;
            free(cur);
        }
        table[i] = NULL;
    }

    // freed successfully
    return true;
}







