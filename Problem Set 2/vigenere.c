#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[])
{   
    string key = argv[1];
    string p;

    
    if (argc != 2) 
    {
        printf("Try again : ");
        return 1;
    }

   for (int i = 0; i < strlen(key); i++)
   {
   
    if (isalpha(key[i]) == 0)
    {
        printf("Enter a valid key: ");
        return 1;
    }
   }     
    
    p = GetString();
    
    for (int i=0, j=0, n = strlen(p);  i < n; i++, j++)

    {
        if (j > (strlen(key)) - 1)
        {
            j = 0;
        }
        
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            if (key[j] >= 'A' && key[j] <= 'Z')
            {
                int encipher = (((p[i] - 'A') + (key[j] - 'A')) % 26 + 'A');
                printf("%c", encipher);
            }
            
            else
            {
                int encipher = (((p[i] - 'A') + (key[j] - 'a')) % 26 + 'A');
                printf("%c", encipher);
            }            
        } 
        
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            if (key[j] >= 'a' && key[j] <= 'z')
            {
                int encipher = (((p[i] - 'a') + (key[j] - 'a')) % 26 + 'a');:) encrypts "world, say hello!" as "xoqmd, rby gflkp!" using "baz" as keyword

                printf("%c", encipher);    
            }
            
            else
            {
                int encipher = (((p[i] - 'a') + (key[j] - 'A')) % 26 + 'a');
                printf("%c", encipher);
            }
        }
        
        else
        {
            printf("%c", p[i]);
            j--;
        }    
    
    
    }
     printf("\n");
     return 0;
}   
