#include <stdio.h>
#include <cs50.h>

int main(void){
	
    int n; // var init

    // ask user for a correct input
    do{
        printf("Height: ");
        n = GetInt() ; 
    }
    while( n < 0 || n > 23 );

	// elab: for every row, for every column, 
	// first print n-1 spaces than print the complementary num of #

    for (int i = 0; i < n; i++){
        for (int k = i; k < (n - 1) ; k++) printf(" ");	
        for (int j = (n - i - 2); j < n; j++) printf("#");
        printf("\n");									
	}
}