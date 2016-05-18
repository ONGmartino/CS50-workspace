#include <cs50.h>

#include "helpers.h"

bool rec(int value, int values[], int n, int s);

void sort(int values[], int n)
{
	int hand;
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			if (values[j] < values[i]){
				hand = values[i];
				values[i] = values[j];
				values[j] = hand;
			}
		} 
	}
    return;
}

bool search(int value, int values[], int n)
{	
	bool vf = rec(value, values, (n-1), 0);
	return vf;
}

bool rec(int value, int values[], int n, int s)
{
	if ( s > n ) {return false; }
	if (n==s){ if (values[n]==value) return true; else return false; }
	if(value == values[((n+s)/2)]) { return true; }

	else{
		int mid = (n+s)/2;
		if(value > values[mid]) { return rec(value, values, n, mid+1 ); }
		else { return rec(value, values, mid-1, s); }
	}
}
