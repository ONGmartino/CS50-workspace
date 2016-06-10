#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void){

    // variable initialization
    float passby;
    int change = 0;
    int pieces = 0;
    int wallet[] = {0, 0, 0, 0};
    int coins[] = {25, 10, 5, 1};

    // ask user for input
    printf("O hai! ");

    do{
    printf("How much change is owed? ");
    passby = GetFloat();
    change=(int)round(passby*100); // round the float error, and move over the comma
    }
    while (change < 0);

    // for every coin type, if the owed change is grater than the coin size,
    // find the max num of coins you can give, than keep track of it and decrease the owed change
    for (int i = 0; i < 4; i++)
    {
        if (change >= coins[i])
        {
            wallet[i] = change/coins[i];
            change -= (wallet[i]*coins[i]);
            pieces += wallet[i];
        }      
    } 
    
    // the only output, by specification, will be:
    printf("%i\n", pieces);
}