#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;  // using stdint library to define an integer with 8 bits named as BYTE

int main(int argc, char *argv[])
{
    //Ensure user only inputs 2 arguments while running the program
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //opening the card to read
    FILE *card = fopen(argv[1], "r");
    // If there is nothing in the card then return 1
    if (card == NULL)
    {
        printf("File cannot be read");
        return 1;
    }
    /* Declaring a array to read the file. As the digital camera cards follow the FAT file(FILE allocation table) system whose "block size" is 512 bytes.
    So for a 1 MB(1,048,576 B) image it takes 1048576 / 512 = 2048 blocks.  */
    BYTE buffer[512];                   // Here we are reading 512 bytes of memory at a time.
    int num = 0;   
    char *new_file = malloc(sizeof(char) * 10); 
    // declaring a string to store the name of the image. ALlot as much space as much you like to keep the name length of the image file
    FILE *image;  // declaring a file name as image to store new images

    while (1)  
    {
        int k = fread(buffer, 512, 1, card);  // reading the 512 bytes block from the card and storing it in the buffer. 
        for (int i = 0; i < 509; i++)  // running a loop to check the starting of an jpeg image header
        {
label:
            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff) 
            // the jpeg image header  is 0xff 0xd8 0xff and the fourth bytes first 4 bits are 0xe
            {
                if ((buffer[i + 3] & 0xf0) == 0xe0)
                {
                    sprintf(new_file, "%03i.jpg", num); 
                    // sprintf is used to store the name of the image file  sprintf(new file address, new file name, new file number) )
                    image = fopen(new_file, "w"); // opening the image file to write
                    fwrite(buffer, 512, 1, image); // using fwrite funtion to write on the new file opened
                    while (1)   // This loop is used to keep on writing the image until we find a new image
                    {
                        int l = fread(buffer, 512, 1, card);  
                        for (int j = 0; j < 511; j++)  // loop to check if there is a new image in the block which we have read
                        {
                            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff)
                            {
                                if ((buffer[i + 3] & 0xf0) == 0xe0)  // if there is a new image then we will close the file and increase the image counter by 1 
                                {
                                    fclose(image);
                                    num++;
                                    goto label; //then again we will go back to the label to check further if there is any new image in the block
                                }

                            }
                        }
                        if (l < 1)   // Here we are checking the condition first so that when the file reaches at the end then we should not write it and just come out of the program 
                        {
                            fclose(image);  // close the image file where we are writing
                            free(new_file); // free the pointer
                            return 0;
                        }
                        fwrite(buffer, 512, 1, image); 
                        // if there is no new file in the block then simply write that block and again keep on reading the card
                    }
                }
            }
        }
        if (k < 1)  // When we use fread then it will return the 3 number which we wrote while reading  fread(buffer, 512, 1, card);. In this case
        {      
            // We wrote 1 so the fread will return everytime and whenever it reaches the end of the card it will return a value less than 1. 
            fclose(image);
            free(new_file);
            return 0;
        }

    }
}
