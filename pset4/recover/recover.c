#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//digital cameras often initialize cards with a FAT file system whose “block size” is 512 bytes (B).
// The implication is that these cameras only write to those cards in units of 512 B
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    //check if valid command line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    // Open input file
    FILE *raw_file = fopen(infile, "r");
    if (raw_file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    typedef uint8_t BYTE;
    BYTE buffer[BLOCK_SIZE];
    size_t bytes_read;

    bool first_jpeg = false;
    bool jpeg_found = false;
    int file_count = 0;
    char current_filename[10];
    FILE *current_file;

    // fread returns 0 if the size of bytes read is different from size asked - here, BLOCK_SIZE or 512
    // equivalent to end of file reached
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) != 0)
    {
        // read jpeg signatures
        // 0xff 0xd8 0xff are the first three bytes of JPEGs
        // The fourth byte is either 0xe0, 0xe1, 0xe2, ... , 0xee, or 0xef

        // check if we run into a jpeg starting signature while reading the raw_file
        // if we find a jpeg signature and this is the first jpeg file, open a file and write onto it, set first to true
        // else close current file and open a new file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            jpeg_found = true;
            if (!first_jpeg)
            {
                first_jpeg = true;
            }
            else
            {
                fclose(current_file);
            }

            sprintf(current_filename, "%03i.jpg", file_count); //just creating filename in the format "000.jpg", "001.jpg" ...
            current_file = fopen(current_filename, "w");
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, current_file);
            file_count++;
        }

        // while reading, if we don't come across the jpeg header signature,
        // keep writing onto the current file in chunks of 512 BLOCK_SIZE
        else
        {
            if (jpeg_found)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, current_file);
            }
        }
    }

    //close all the open files
    fclose(raw_file);
    fclose(current_file);
    return 0;

}
