// Recovers JPEGs from a forensic image

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define the constant for the FAT block size so there are no magic numbers
#define BLOCKSIZE 512

// create a custom variable byte, size of one byte
typedef unsigned char byte;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }

    // read the memory card filename
    char *cardname = argv[1];

    // open the input card file for reading
    FILE *card_in = fopen(cardname, "r");

    // check if the card file was successfully opened
    if (card_in == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", cardname);
        return 2;
    }

    // set the counter for image names
    int imagecounter = 0;

    // initialize the array of characters where to keep the temporary image names
    char *imagename = malloc(sizeof(char) * 8);

    // initialize the image file for output
    FILE *image_out = NULL;

    // initialize temporary buffer array
    byte buffer[BLOCKSIZE];

    // while not the end of the card file
    while(fread(&buffer, BLOCKSIZE, 1, card_in) == 1)
    {

        // check if it is the beginning of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 &&
            buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if not the first image, close the old image file
            if (imagecounter > 0)
            {
                fclose(image_out);
            }

            // write the name dependent on counter to the image name array
            sprintf(imagename, "%03i.jpg", imagecounter);

            // open a new image file for writing
            image_out = fopen(imagename, "w");

            // check if the opening of the output image file was successful
            if (image_out == NULL)
            {
                fclose(card_in);
                fprintf(stderr, "Could not create %s.\n", imagename);
                return 3;
            }

            // write the buffer to the image file and increase the image counter
            fwrite(&buffer, sizeof(buffer), 1, image_out);
            imagecounter++;
        }

        // if not the beginning of a JPEG and not the first image, then just write from buffer to image file
        else if (imagecounter > 0)
        {
            fwrite(&buffer, sizeof(buffer), 1, image_out);
        }
    }

    // close card file
    fclose(card_in);

    // close image file
    fclose(image_out);

    // free the memory
    free(imagename);

    // return success
    return 0;
}
