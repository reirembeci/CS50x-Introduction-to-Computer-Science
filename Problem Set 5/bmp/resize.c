/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile");
        return 1;
    }

    // remember filenames and size factor
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if (n < 1 || n > 100)
    {
        printf("Try again.\n");
        return 1;
    }

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
    BITMAPFILEHEADER bf, bf_new;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_new = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_new;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_new = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    //update header info for outfile
    bi_new.biWidth = bi.biWidth * n;
    bi_new.biHeight = bi.biHeight * n;
    
    // determine padding for scanlines
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding =  (4 - (bi_new.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    bi_new.biSizeImage = (bi_new.biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(bi_new.biHeight);
    bf_new.bfSize = bf.bfSize + bi_new.biSizeImage - bi.biSizeImage ;
        
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
    
        for (int m = 0; m < n; m++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int i = 0; i < n; i++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);            
                    
            }

            //add new padding
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
        
            // return to the beginning 
            if (m < n - 1)
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR); 
         
        }
        
        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);        
   
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
