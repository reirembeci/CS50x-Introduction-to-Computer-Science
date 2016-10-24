#include <cs50.h>
#include <stdio.h>

int main(void)
{
   int height;
   int spaces;
   int hashes;
   
   do 
   {
       printf("Choose the height of the pyramind between 0 and 23.\n");
       height = GetInt();
   }
   while (height < 0 || height > 23);
   
   for (int i = 0; i < height; i++)
   {
       for (spaces = 0; spaces < height - (i+1) ; spaces++)
       {
           printf(" ");
       }
       
       for (hashes = 0; hashes <=  height - spaces  ; hashes++)
       {
           printf("#");
       }
       
       printf("\n");
   }
}
