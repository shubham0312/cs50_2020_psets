// Implements a dictionary's functionality
// Read the given question first and the walkthrough video thoroughly.
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table. 
// Here we are using assuming the worst case scenario if all the 45 character are 'z' then the total ascii value
// will be 'z' = 122 . N = 122 * 45. For more info - https://www.youtube.com/watch?v=HsnjdbHMZO8
const unsigned int N = (LENGTH + 1) * 'z';

/*  Declaring a global variable to find the total number of words in the dictionary.
* While we are loading the dictionary with the words in the load function we will keep on incrementing this variable
* to find the total word count.
*/
int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // To check if the word is present or not. Firstly we will find the index of the hash function.
    int index = hash(word);
    // Then assign that hash table to the node cursor.
    node *cursor = table[index];
    while(cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            // If the word is found then return true or else move the cursor to the next location.
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
        
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Finding the sum of the ascii value of the given word
    int sum = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        // Adding the ASCII values of the words
        sum += tolower(word[i]);
    }
    return (sum % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // opening a new file to read the dictionary file.
    FILE *dict= fopen(dictionary,"r");
    // if the file is empty then return false and come out of the function.
    if (dict == NULL)
    {
        return false;
    }
   
    char *w = malloc(sizeof(char) * (LENGTH + 1));
    // now loading the dict file until a new line is not seen and then copying it in the w pointer.
    while(fscanf(dict, "%s\n", w) != EOF)
    {
        // Creating a new node to store the given word in the dictionary file
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        //Copying the word in the node inside word variable.
        strcpy(n->word, w);
        //Assigning the value of the new node to be NULL
        n->next = NULL;
        // Obtain hashing index 
        int index = hash(w);
        
        // If the hash table is NULL then assign the new node to it else insert the new node in the front.
        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else 
        {
            n->next  = table[index];
            table[index] = n;
        }
      
        word_count++;
    }
    
    free(w);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Running a loop to unload all the linked list in the hash table
    for (int i = 0; i < N; i++)
    {
        // declaring a node and storing the location of the first linked list.
        node *head = table[i];
        // cursor and temp pointer also points to that first node which contains the word. 
        node *cursor = head;
        node *temp = head;
        // Running a loop until cursor encounters a NULL
        while(cursor != NULL)
        {
            // Moving the cursor location to the nrxt linked list and freeing the previous linked list
            cursor = cursor->next;
            free(temp);
            //Again assigning the location of new linked list to the temp pointer. 
            temp = cursor;
        }
    }
    return true;
}
