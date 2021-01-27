#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions

int main(void)
{
    string name = get_string("What is your name?\n"); // ask for the name and store in name variable
    printf("Hello, %s!\n", name); // print the name
}