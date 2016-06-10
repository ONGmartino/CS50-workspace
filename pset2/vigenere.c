#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[]){
	
	// ensure proper input, first argc,
	if (argc != 2)
	{
		printf("Bad input, retry\n");
		return 1;
	}

	// then the argv passphrase, and pass it to lowercase
	int j = strlen(argv[1]);
	for (int i = 0; i<j; i++)
	{
		if (! isalpha (argv[1][i]))
		{
			printf("Bad passphrase, retry\n");
			return 1;
		}
		if (isupper(argv[1][i])) argv[1][i] = tolower(argv[1][i]);
	}
	
	// var init and ask for CLI input to convert 
	string v = argv[1];
	string s = GetString();
	int l = strlen(s);
	int i = 0;
	
	
	// for every char, handle differently upper, lower and special char
	// by subracting the base ASCII number, then re-add the ASCII base value
	// i track the position in the phrase to cifer, z the index in the passphrase

	LOOP:for (int z = 0; i < l; i++, z++){
	
		if (s[i] > 96 && s[i] <123)
			printf("%c", ((s[i] - 97 + v[z] -97) % 26) + 97);
		
		else if (s[i]>64 && s[i]<91)
			printf("%c", ((s[i] - 65 + v[z] - 97) % 26) + 65);
		
		else{
			printf("%c", s[i]);
			z--;
		}
		
		// at the (corrected) end of the passphrase, restart the loop
		if (z > (j-2)){
			i++;
			goto LOOP;
		}
	} 

	// aaaand bye.
	printf("\n");
	return 0;
}
