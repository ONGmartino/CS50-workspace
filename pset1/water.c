#include <stdio.h>
#include <cs50.h>

int main (void){

	int min; // var initialization

	printf("minutes: "); // ask user for input

    min = GetInt(); // recive input

	printf("bottles: %i", (min*12)); // output
}