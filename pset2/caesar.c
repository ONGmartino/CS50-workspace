#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[]){
	
	if (argc != 2 || atoi(argv[1]) == 0 ){
		printf("retry\n");
		return 1;
	}
	
	string s = GetString();
	int l = strlen(s);
	int k = atoi(argv[1]);	
	
	for (int i = 0; i < l; i++){
		if (s[i] > 96 && s[i] <123){
			printf("%c", ((s[i] - 97 + k) % 26) + 97);
		}
		else if (s[i]>64 && s[i]<91){
			printf("%c", ((s[i] - 65 + k) % 26) + 65);
		}
		else{
			printf("%c", s[i]);
		}
	} //chiusura for
	printf("\n");
	return 0;
}
