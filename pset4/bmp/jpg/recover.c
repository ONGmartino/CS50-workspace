#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

bool checksignature(uint8_t check[4]);

int main(void)
{
		// file init
		FILE* fp = fopen("card.raw", "r");	
		if(fp == NULL){ fclose(fp);	return 1; }
		FILE* outp = NULL;

		uint8_t buffer[512];
		uint8_t check[4];

		fread(buffer, 512, 1, fp);	
		int count = 0;

		while(fread(buffer, sizeof(buffer), 1, fp) > 0)
		{
				for(int i = 0; i < 4; i++) { check[i] = buffer[i];}
	
				if(checksignature(check)){
					
				 		if (outp != NULL) { fclose(outp); count++; }		
					
						char file[8];
						sprintf(file, "%03d.jpg", count);
						outp = fopen(file, "w");

						fwrite(buffer, sizeof(buffer), 1, outp);
				 }
				
				else{ if(outp) 
					fwrite(buffer, sizeof(buffer), 1, outp); }
		}
    
    if(outp) fclose(outp); 
	fclose(fp);
	return 0;
}

bool checksignature(uint8_t check[4]){
	uint8_t signature[4] = {0xff, 0xd8, 0xff};
	uint8_t lastOfUs[16] = { 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 
							 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef };
	//if the first 3 are mached
	if( memcmp(signature, check, 3) == 0 ){
		//check the last
		for(int i = 0; i < 16; i++){
			if(check[3] == lastOfUs[i]) return true;
		}
	}
	return false;
}
