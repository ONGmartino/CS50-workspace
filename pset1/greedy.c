#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void){
    float passby;
    int change;
    int q = 0;
    int d = 0;
    int n = 0;
    int p = 0;
    printf("O hai! ");
    
    do{
    printf("How much change is owed?");
    passby = GetFloat();
    change=(int)round(passby*100);
    }while (change < 0);

    if (change >= 25){
        q = change/25;
        change -= (q*25);
        }      
    if (change >= 10){
        d = change/10;
        change -= (d*10);
    }        
    if (change >= 5){
        n = change/5;
        change -= (n*5);
    }        
    if (change >= 1){
        p = change/1;
        change -= (p*1);
    }
    printf("%i\n", (q+d+n+p));
}