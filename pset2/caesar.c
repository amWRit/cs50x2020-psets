#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool isNumeric(string);
string apply_caesar(string, int);

int main(int argc, string argv[])
{

    if (argc == 2 && isNumeric(argv[1]))
    {
        //printf("Success\n");

        int key = atoi(argv[1]);

        //key = key % 25;
        //printf("key: %i\n", key);

        string input_text = get_string("plaintext: ");
        int n = strlen(input_text);
        string output_text;

        output_text = apply_caesar(input_text, key);

        //printf("ciphertext: ");

        // for (int i = 0; i < n; i++)
        // {
        //     printf("%c", output_text[i]);
        // }

        printf("ciphertext: %s\n", output_text);
        //return 0;

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool isNumeric(string input)
{
    int n = strlen(input);

    for (int i = 0; i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            //printf("not a number\n");
            return false;
        }
    }
    //printf("yes a number\n");
    return true;
}

string apply_caesar(string input_text, int key)
{
    int n = strlen(input_text);
    char output_char[n + 1];
    string output_text;
    for (int i = 0; i < n; i++)
    {
        int char_val = (int) input_text[i];
        char c = input_text[i];
        //printf("%c - ", c);


        //CAPS
        if (char_val >= 65 && char_val <= 90)
        {
            char_val += key;
            if (char_val > 90)
            {
                int diff = char_val - 90;
                diff = diff % 26;
                char_val = 64 + diff;
            }
        }

        //SMALL
        else if (char_val >= 97 && char_val <= 122)
        {
            char_val += key;
            if (char_val > 122)
            {
                int diff = char_val - 122;
                diff = diff % 26;
                char_val = 96 + diff;
            }
        }

        c = char_val;
        //printf("%c - ", c);
        //strcat(output_string, c);
        output_char[i] = c;
        //strncat(output_string, &c, 1);
    }
    output_char[n + 1] = '\0';
    output_text = output_char;
    return output_text;
}