#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions
#include <string.h>
#include <math.h>

int get_readability_score(string);
int get_num_letters(string);
int get_num_words(string);
int get_num_sentences(string);

int main(void)
{
    string text = get_string("Text: ");

    //printf("length: %li", strlen(text));
    int score = get_readability_score(text);
    //printf("Score: %i\n", score);

    if (score > 0 && score <= 16)
    {
        printf("Grade %i\n", score);
    }
    else if (score > 16)
    {
        printf("Grade 16+\n");
    }
    else if (score < 1)
    {
        printf("Before Grade 1\n");
    }
}

int get_readability_score(string text)
{
    int score = 0;
    int num_letters = get_num_letters(text);
    int num_words = get_num_words(text);
    int num_sentences = get_num_sentences(text);

    float l = ((float)num_letters / num_words) * 100;
    float s = ((float) num_sentences / num_words) * 100;

    // printf("letters: %i\n", num_letters);
    // printf("words: %i\n", num_words);
    // printf("sentences: %i\n", num_sentences);
    // printf("l: %f\n", l);
    // printf("s: %f\n", s);

    // Coleman-Liau index computation
    score = (int) round((0.0588 * l) - (0.296 * s) - 15.8);

    return score;
}

int get_num_letters(string text)
{
    int num_letters = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        int char_val = (int) text[i];
        if ((char_val >= 65 && char_val <= 90) || (char_val >= 97 && char_val <= 122))
        {
            num_letters++;
        }
    }
    return num_letters;
}

int get_num_words(string text)
{
    int num_words = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if (text[i] == ' ' && text[ i - 1] != ' ')
        {
            num_words++;
        }
        else if ((i == n - 1) && (text[i] != '.' || text[i] != '!' || text[i] != '?' || text[i] != ' ' || text[i] != '"'))
        {
            num_words++;
        }
    }
    return num_words;
}

int get_num_sentences(string text)
{
    int num_sentences = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
    {
        if ((text[i] == '.' || text[i] == '!' || text[i] == '?') && (text[i - 1] != '.' || text[ i - 1] != '!' || text[i - 1] != '?'
                || text[i - 1] != ' '))
        {
            num_sentences++;
        }
        // else if ((i == n - 1) && (text[i] != '.' || text[i] != '!' || text[i] != '?' || text[i] != ' '))
        // {
        //     num_sentences++;
        // }
    }
    return num_sentences;
}