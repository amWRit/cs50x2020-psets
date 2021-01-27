#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    int i = 65;
    char c = i;
    printf("Before: %c \n", c);

    int char_val = (int) c;
     printf("value: %i \n", char_val);

    i = 66;
    c = (int) (char_val + 1) % 26;
    //c=  char_val + 1;
    printf("After: %c \n", c);
}