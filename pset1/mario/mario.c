#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions

void hash_pyramid(int); // function declaration

int main(void)
{
    int height;
    printf("### HASH PYRAMID ### \n");
    do
    {
        height = get_int("Enter a height between 1 and 8?\n"); // ask for the height and store in height variable
    }
    while (height < 1 || height > 8);  // prompt until height input is between 1 and 8
    hash_pyramid(height);
}

// function that takes a integer paramter and builds a right pushed pyramid of height of that paramter
void hash_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}