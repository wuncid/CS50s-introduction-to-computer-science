// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// number of linked lists in the hash table
#define MAX_HASH_INDEX 150000

// introduce the hash function
unsigned int hash(const char* string);

// define the node struct
typedef struct node
{
	char word[LENGTH + 1];
	struct node *next;
}
node;

// create the hash table and set elements to NULL
node *hashtable[MAX_HASH_INDEX] = {NULL};

// initialize the dictionary counter variable
unsigned int dict_counter = 0;

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the dictionary text file for reading
    FILE *dictionary_in = fopen(dictionary, "r");

    // check if the dictionary file was successfully opened
    if (dictionary_in == NULL)
    {
        return false;
    }

    // initialize the buffer
    char buffer[LENGTH + 1];

    // scan dictionary word by word
    while (fscanf(dictionary_in, "%s", buffer) != EOF)
    {
    	// malloc a node * for a new word
        node *new_node = malloc(sizeof(node));

        // check if computer has memory for a new node
    	if (new_node == NULL)
    	{
    		// unload all the nodes from the memory
    		unload();
    		// close the dictionary file
            fclose(dictionary_in);
    		return false;
    	}

    	// set the node pointer to NULL
    	new_node->next = NULL;

    	// copy word into node, use strcpy because there is no lowercase conversion
    	strcpy(new_node->word, buffer);

        // calculate the hash index with the hash function
        unsigned int hash_index = hash(new_node->word) % MAX_HASH_INDEX;

        // if the array index is NULL (there is no linked-list yet), save the node into the index
        if (hashtable[hash_index] == NULL)
        {
            hashtable[hash_index] = new_node;
        }

        // else save the word into another node and point it to index, change head
        else
        {
            new_node->next = hashtable[hash_index];
            hashtable[hash_index] = new_node;
        }

        // increment the loaded words counter
        dict_counter++;
    }

    // close the dictionary file
    fclose(dictionary_in);

    return true;
}

// the djb2 string hash function from: https://github.com/fragglet/c-algorithms/blob/master/src/hash-string.c
unsigned int hash(const char *string)
{
	unsigned int result = 5381;
	const char *p;

	p = (const char *) string;

	while (*p != '\0') {
		result = (result << 5) + result + *p;
		++p;
	}

	return result;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    char word_lowercase[strlen(word) + 1];

    for (int i = 0; i < strlen(word); i++)
    {
        word_lowercase[i] = tolower(word[i]);
    }

    word_lowercase[strlen(word)] = '\0';

    /* alternative way to convert the word to lowercase, slower because goes through each character twice*/
    // char *word_lowercase = malloc(sizeof(char) * (strlen(word) + 1));
    // strcpy(word_lowercase, word);

    // for (int i = 0; i < strlen(word_lowercase); i++)
    // {
    //    word_lowercase[i] = tolower(word_lowercase[i]);
    // }

    // calculate the hash index with the hash function
    int hash_index = hash(word_lowercase) % MAX_HASH_INDEX;

    // point the cursor to the hash index in the hash table
    node *cursor = hashtable[hash_index];

    // initial check if there is a linked list at the index in the hash table,
    // if yes, then repeat loop until node pointer points to NULL
    while (cursor != NULL)
    {
        // compare strings
        if (strcmp(word_lowercase, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // set the unload counter to 0
    int counter = 0;

    // iterate over the linked-list indexes in hash table
    for (int i = 0; i < MAX_HASH_INDEX; i++)
    {
        node *cursor = hashtable[i];

        // free each node in the linked-list
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        counter++;
    }

    if (counter == MAX_HASH_INDEX)
    {
        return true;
    }

    else
    {
        return false;
    }
}
