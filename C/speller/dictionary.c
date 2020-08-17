/*
    Name: dictionary.c
    Authors: Mubeen Padaniya, CS50
    Description: Implements dictionary functions.
    Version: 1.0
*/
// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// The number of words
int noofwords = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int i = hash(word);
    node *cursor;
    cursor = table[i];
    while (cursor != NULL) {
        if (!strcasecmp(cursor->word,word)) {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    //using the ascii value of the first character to determine index
    int charword = (int)word[0];
    int index = 0;
    if (charword >= 65 && charword <= 90) {
        index = charword-65;
    }
    else if (charword >= 97 && charword <= 122) {
        index = charword-97;
    }
    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    char *word = malloc(50);
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL) {
        printf("Error: File cannot be opened.\n");
        return false;
    }
    int size = 0;
    int i = 0;
    node *n;
    while ((fscanf(dict,"%s",word)) != EOF) {
        noofwords++;
        n = malloc(sizeof(node));
        if(n == NULL) { printf("Error: Memory cannot be allocated."); return false; }
        strcpy(n->word, word);
        i = hash(n->word);
        if (table[i] == NULL) {
            n->next = NULL;
            table[i] = n;
        }
        else {
            n->next = table[i];
            table[i] = n;
        }
    }
    free(word);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return noofwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    for(int i = 0; i < N; i++) {
        cursor = table[i];
        while(cursor != NULL) {
            node *tmp;
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
