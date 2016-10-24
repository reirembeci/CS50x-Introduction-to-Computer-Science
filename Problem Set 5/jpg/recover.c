/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//constants
#define BLOCK_SIZE 512

int main(int argc, char* argv[])
{
    uint8_t buffer[512];   
    int counter = 0;
    FILE* image = NULL;
       
    // open memory card file
    FILE* m_card = fopen("card.raw" , "r");
    if (m_card == NULL)
    {
        printf("Could not open card.raw...");
        return 1;
    }    
    
    while(fread(buffer, BLOCK_SIZE, 1, m_card))
    {
        //check for the beginning of the JPG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            //close current file if it is not NULL
            if (image != NULL)
                fclose(image);
        
            //char array to store the resultat string
            char title[8];
        
            sprintf(title, "%03d.jpg", counter);
            
            // open a new JPG file to write
            image = fopen(title, "w");
            
            //increment counter
            counter++;
        
        }
        
        // write 512 bytes until new JPG is found
        if (image != NULL)
            fwrite(buffer, BLOCK_SIZE, 1, image);
        
    }
    
    //close memory card
    fclose(m_card);
    
    //close the new file 
    if (image != NULL)
        fclose(image);
    
    //that's all :)
    return 0;
   
}
