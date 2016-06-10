#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// main funtion does not take any arguments
int main(void){

    string name = GetString(); //ask user for the name 
    
    printf("%c", toupper(name[0])); // print the first char as upper
   
    // then a loop: if preceeded by a space, print it uppercase
    // it almost look like python *-*
    for ( int i = 0, n = strlen(name); i < n; i++)
        if ( name[i-1] == ' ') 
            printf("%c", toupper(name[i]));      
    
    // then close the line
    printf("\n"); 
}

