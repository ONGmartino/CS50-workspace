#include <stdbool.h>
#include <ctype.h>    
#include "dictionary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// typedef, for a tries structure.
typedef struct node {        
    struct node *az[27];
    bool end;
} node;

//cannot malloc outside of a function! 
node *root = NULL;
int dictlen = 0;

/*
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // set the "environment" to the root node, ask for lenght of string
    node *nodo = root;
    int j = strlen(word);

    // then, for every char, 
    for (int i = 0; i < j; i++)
    {
        // pass it to a shorter variable name, do ASCII manipulation,
        int s = word[i];
        if (s < 91 && s > 64) s -= 65;
        if (s < 123 && s > 96) s -= 97;
        if (s == '\'') s = 26;

        // and check if exist. If so, set the pointer
        if (nodo->az[s] == NULL) return false;                           
        nodo = nodo->az[s];       
    }
    
    // at the end, if the word can end here, return true.
    if (nodo->end) return true;
    else return false;
}

/*
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open file, check it, initialize a cursor
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL) return false;
    int cursor = 0;

    // malloc the root node, than point the first node to the root structure
	root = malloc(sizeof(node));
    node *nodo = root;

    // while the cursor is not EOF
    while (true)
    {
        // get a char, than act if is an EOF, a normal char, or a NewLine ASCII char
        cursor = fgetc(dict);

        if (cursor == EOF) break;
        
        else if (cursor != 10)
        { 
            // ASCII manipulation before storage  
		    if (cursor == '\'') cursor = 26;
			else cursor -= 97;

            // if the subnode does not exist yet, malloc a new node,
            // set it to safe NULL+false variables, and set the pointer 
		    if (nodo->az[cursor] == NULL) 
		    {
		        node *new = malloc(sizeof(node));   
		        *new = (node) {{NULL},false};
		        nodo->az[cursor] = new;
		        nodo = new;
			}

            // else, just pick up the right pointer
			else nodo = nodo->az[cursor];
        }

        // if a NewLine ASCII char, set the word end, update the counter and return to the root. 
		else if (cursor == 10) { 
		    nodo->end = true;
			dictlen++;
			nodo = root;
		}			
    }

    // safely say goodbye
    fclose(dict);
    return true;
}


/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // anything suspicious, just return the counter
    return dictlen;
}

/*
 * Unloads dictionary from memory.  Returns true if successful else false
 */
void recursive(node* nodo) 
{
    //for any sub.node, if not empty, call the recursive unloading function there
    for( int i = 0; i < 27; i++ ){
        if( nodo->az[i] != NULL )
            recursive(nodo->az[i]);             
    }
    // if every sub.node is empty, free the node.
    free(nodo);
}

bool unload(void)
{
    // just call a recursive unloading function on the root node
    recursive(root);
    return true;
}
