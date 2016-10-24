#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;
    int count = 0;
    int change;
    //int quarter;
    //int dime;
    //int nickel;
    //int penny;
    
   do 
   {
       printf("How much change is owed?\n");
       dollars  = GetFloat();
       change = round(dollars*100);
   }
   while (change == 0 ||change < 0);
   
   while (change >= 25)
   {
       count++;
       change = change - 25;
   } 
   
   while (change >= 10)
   {
       count++;
       change = change - 10;
   }  

   while (change >= 5)
   {
       count++;
       change = change - 5;
   }   
   

   while (change >= 1)
   {
       count++;
       change = change - 1;
   }     
   
   printf("%d\n", count);
}
