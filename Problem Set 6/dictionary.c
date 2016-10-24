/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

node* root;

// number of words loaded
int n = 0;

// prototype
bool free_node(node* help);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* curr = root;
    int i = 0; 
    
    // for each letter in input word
    while (word[i] != '\0')
    {
        char ch = word[i];
        int num;
        
        // check for apostrophes
        if (word[i] == '\'')
        {
            ch = 'z' + 1;
        }
        
        // case insensitivity 
        num = tolower(ch) - 'a';
        
        // if null word is mispelled 
        if (curr->children[num] == NULL)
        {
            return false;
        }
        else
        {
            // move to the next letter
            curr = curr->children[num];
            i++;
        }        
    }
    
    //after we reached the end of word check if it is correct or mispelled 
    if (curr->is_word == true)
    {
        //the word is correct
        return true;
    }
    else
    {
        //word is mispelled
        return false;
    }    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open dictionary 
    FILE* dict = fopen(dictionary, "r"); 
    
    // check for errors 
    if (dict == NULL) 
    {
        printf("Could not open\n");
        return false;
    }
    
    // calloc space for a root
    root = calloc(1, sizeof(node));
    node* curr = NULL;

    
    //while we haven't reached the end of file
    while (fgetc(dict) != EOF)
    {
      fseek(dict, -1, SEEK_CUR);
         
      // set current to root
      curr = root;  
      
      // interate through the trie, for every dictionary word
      for (int i = fgetc(dict); i != '\n'; i = fgetc(dict))
      {
      
        //set apostrophes right after "z" in the trie 
        if (i == '\'')
        {
            i = 'z' + 1;
        }
      
        if (curr->children[i - 'a'] == NULL)
        {
            // calloc a new node
            curr->children[i - 'a'] = calloc(1, sizeof(node));
            curr = curr->children[i - 'a'];
        }
        else 
        {
            // move to a new node
            curr = curr->children[i - 'a'];
        }
         
      }
    
    curr->is_word = true;
    n++;
    }
    
    fclose(dict); 
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return n;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

// helper function to unload 
bool free_node(node* help)
{
    // iterate through the trie
    for (int k = 0; k < 27; k++)
    {
        if (help->children[k] != NULL)
        {
            // recursion
            free_node(help->children[k]);
        }    
    }
    free(help);
    return true;
}
 
bool unload(void)
{
    return free_node(root);
}
