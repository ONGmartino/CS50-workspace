#include <cs50.h>

#include "helpers.h"

bool rec(int value, int values[], int n, int s);

void sort(int values[], int n){
	
	// Selection sort, the simplest (even if not the best, by computational time)
	// search the array for the lowest value, then swap it with the first one non-sorted
	// repeat. (cannot find an inline swap in any library!)
	
	int hand;
	
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			if (values[j] < values[i])
			{
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
	//essentially, require a recursive function
	return rec(value, values, (n-1), 0);
}

bool rec(int value, int values[], int n, int s)
{
	// if 1-element array, and values does not match, return false
	if (n==s) 
		if (values[n] != value)
			return false;

	// if the median value is what I need, return true
	if(value == values[(n+s)/2])
		return true;

	// else repeat in the correct half of the array 
	else{
		int mid = (n+s)/2;
		
		if(value > values[mid])
			return rec(value, values, n, mid+1); 
		else 
			return rec(value, values, mid-1, s); 
	}
}
