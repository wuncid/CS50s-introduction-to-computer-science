// Resizes a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember the resize factor
    char *ininteger = argv[1];

    // check if the user entered an integer
    if (atoi(ininteger) == 0)
    {
        fprintf(stderr, "Could not read %s.\n", ininteger);
        return 2;
    }

    // convert the resize factor to an integer
    int n = atoi(ininteger);

    if (n < 1 || n > 100)
    {
        fprintf(stderr, "The value of %s is not between 1 and 100.\n", ininteger);
        return 3;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 4;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 5;
    }

    // read infile's BITMAPFILEHEADER and outfile's initial BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_res;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_res = bf;
    //fseek(inptr, sizeof(BITMAPFILEHEADER), SEEK_CUR);
    //fread(&bf_res, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER and outfile's initial BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_res;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_res = bi;
    //fseek(inptr, sizeof(BITMAPINFOHEADER), SEEK_CUR);
    //fread(&bi_res, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 6;
    }

    // change the outfile's BITMAPINFOHEADER
    bi_res.biWidth *= n;
    bi_res.biHeight *= n;

    // determine padding for outfile's scanlines
    int padding_res = (4 - (bi_res.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi_res.biSizeImage = ((sizeof(RGBTRIPLE) * bi_res.biWidth) + padding_res) * abs(bi_res.biHeight);

    // change the outfile's BITMAPFILEHEADER
    bf_res.bfSize = bi_res.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_res, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_res, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for infile's scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int line = 0, biHeight = abs(bi.biHeight); line < biHeight; line++)
    {
        // repeat the process of writing a line to outfile n times
        int i = 0;
        while (i < n)
        {
            // iterate over pixels in scanline
            for (int pixel = 0; pixel < bi.biWidth; pixel++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write each RGB triple to a line of outfile n times
                for (int j = 0; j < n; j++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // add padding to the outfile, if any
            for (int k = 0; k < padding_res; k++)
            {
                fputc(0x00, outptr);
            }

            // increment i
            i++;

            // go back to the beginning of the scanline if needed
            if (i < n)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
