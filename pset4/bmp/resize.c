/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
	
	if (atoi(argv[1]) < 1 || atoi(argv[1])>100){
		return 1;
	}
	int n = atoi(argv[1]);

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

	// does in/output contain padding?
    int inpad =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outpad =  (4 - (bi.biWidth * sizeof(RGBTRIPLE) * n) % 4) % 4;

	BITMAPFILEHEADER new_bf = bf;
	BITMAPINFOHEADER new_bi = bi;

	// change bitmap width/height data
	new_bi.biWidth *= n;
	new_bi.biHeight *= n;

	// change Size in file header
	new_bi.biSizeImage = ( new_bi.biWidth * sizeof(RGBTRIPLE) + outpad ) * abs(new_bi.biHeight);
    new_bf.bfSize = new_bf.bfOffBits + new_bi.biSizeImage;

    // write outfile's BITMAP HEADER
    fwrite(&new_bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&new_bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // reconnect outpad and padding
	// int padding = outpad;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

		//multiple row for copy
		for ( int rowcopy = 0; rowcopy < n; rowcopy++){

		    // iterate over pixels in scanline
		    for (int j = 0; j < bi.biWidth; j++)
		    {
		        // temporary storage
		        RGBTRIPLE triple;

		        // read RGB triple from infile
		        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

		        // write RGB 
				for (int linecopy = 0; linecopy < n; linecopy++)
				        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		    }

		    // skip over padding, if any
		    fseek(inptr, inpad, SEEK_CUR);

		    // then add it back (to demonstrate how)
		    for (int k = 0; k < outpad; k++)
		    {
		        fputc(0x00, outptr);
		    }
		//reset input-file cursor for the same line
		fseek(inptr, -(bi.biWidth * 3 + inpad ), SEEK_CUR);
		}
	//and restore the progress after the cursor restore in the inner for.
	fseek(inptr, bi.biWidth*3+inpad, SEEK_CUR);
	}

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
