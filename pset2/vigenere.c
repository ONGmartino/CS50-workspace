#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[]){
	if (argc != 2){
		printf("retry\n");
		return 1;
	}

	int j = strlen(argv[1]);
	for (int i = 0; i<j; i++){
		if (! isalpha (argv[1][i])){
			printf("retry\n");
			return 1;
		}
		if (isupper(argv[1][i])){
			argv[1][i] = tolower(argv[1][i]);
		}
	}
	string v = argv[1];
	string s = GetString();
	int l = strlen(s);
	int i = 0;
	
	LOOP:for (int z = 0; i < l; i++, z++){
		if (s[i] > 96 && s[i] <123){
			printf("%c", ((s[i] - 97 + v[z] -97) % 26) + 97);
		}
		else if (s[i]>64 && s[i]<91){
			printf("%c", ((s[i] - 65 + v[z] - 97) % 26) + 65);
		}
		else{
			printf("%c", s[i]);
			z--;
		}
		if (z > (j-2)){
			i++;
			goto LOOP;
		}
	} // chiusura for

	printf("\n");
	return 0;
}
