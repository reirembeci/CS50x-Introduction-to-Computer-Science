#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    int k;
    string text;
    
    if (argc == 2)
        k = atoi(argv[1]);
    else
    {
        printf("Try again : ");
        return 1;
    }        
    
    
    text = GetString(); 
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 65 && text[i] <= 90)
        {
            int encipher = (((text[i] - 65) + k) % 26) + 65;
            printf("%c", encipher);
        }
        
        else if (text[i] >= 97 && text[i] <= 122)
        {
            int encipher = (((text[i] - 97) + k) % 26) + 97;
            printf("%c", encipher);        
        }
                
        else
            printf("%c", text[i]);
    }
     
    printf("\n"); 

}
