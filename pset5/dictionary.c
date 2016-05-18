#include <stdbool.h>
#include <ctype.h>    
#include "dictionary.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {        
    struct node *az[27];
    bool end;
} node;

node *root = NULL;
int dictlen = 0;

/*
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    node *nodo = root;
    int j = strlen(word);
    for (int i = 0; i < j; i++)
    {
        int s = word[i];
        if (s < 91 && s > 64) s -= 65;
        if (s < 123 && s > 96) s -= 97;
        if (s == '\'') s = 26;

        if (nodo->az[s] == NULL) return false;                           
        nodo = nodo->az[s];       
    }
    
    if (nodo->end) return true;
    else return false;
}

/*
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL) return false;
    int cursor = 0;
	root = malloc(sizeof(node));
    node *nodo = root;
    while (true)
    {
        cursor = fgetc(dict);
        if (cursor == EOF) break;
        else if (cursor != 10)
        {   
		    if (cursor == '\'') cursor = 26;
			else cursor -= 97;
		    if (nodo->az[cursor] == NULL) 
		    {
		        node *new = malloc(sizeof(node));   
		        *new = (node) {{NULL},false};
		        nodo->az[cursor] = new;
		        nodo = new;
			}
			else nodo = nodo->az[cursor];
        }
		else if (cursor == 10) { 
		    nodo->end = true;
			dictlen++;
			nodo = root;
		}			

    }
    fclose(dict);
    return true;
}


/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   return dictlen;
}

/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
void recursive(node* nodo) 
{
    for( int i = 0; i < 27; i++ ){
        if( nodo->az[i] != NULL )
            recursive(nodo->az[i]);             
    }
    free(nodo);
}

bool unload(void)
{
    recursive(root);
    return true;
}
