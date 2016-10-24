/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    /*for (int i = 0; i < n; i++)
        if (values[i] == value)
            return true;
    
    return false; */
    
    int upper = n - 1;
    int lower = 0;
    
    while (lower <= upper)
    {
        int middle = (upper + lower) / 2;
        
        if (value == values[middle])
        {
            return true;
        }
        
        else if (value < values[middle])
        {
            upper = middle - 1;
        }
        
        else if (value > values[middle])
        {
            lower = middle + 1;
        }
        
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    int i;
    int j;
    int min;
    
    for (i = 0; i < n ; i++)
    {
        for (j = i + 1; j <= n; j++)
        {
            if (values[i] > values[j])
            {
                min = values[j];
                values[j] = values[i];
                values[i] = min;
            }
            
            else 
            {
                min = values[i];
            }
        }
        
    }
    return;
}



