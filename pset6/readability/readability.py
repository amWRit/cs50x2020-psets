from cs50 import get_string
import math


def main():
    text = get_string("Text: ")
    score = get_readability_score(text)

    if score > 0 and score <= 16:
        print(f"Grade {score}")
    elif score > 16:
        print(f"Grade 16+")
    elif score < 1:
        print(f"Before Grade 1")


def get_readability_score(text):
    num_letters = get_num_letters(text)
    num_words = get_num_words(text)
    num_sentences = get_num_sentences(text)

    l = (num_letters / num_words) * 100
    s = (num_sentences / num_words) * 100

    # Coleman-Liau index computation
    score = int(round((0.0588 * l) - (0.296 * s) - 15.8))

    return score


def get_num_letters(text):
    n = len(text)
    num_letters = 0

    for i in range(n):
        char_val = ord(text[i])  # get ASCII integer val of character

        # consider char as letter only if it's ASCII value falls in the range of alphabets

        if (char_val >= 65 and char_val <= 90) or (char_val >= 97 and char_val <= 122):
            num_letters += 1

    return num_letters


def get_num_words(text):
    n = len(text)
    num_words = 0

    for i in range(n):
        # if current char is a space and there was no space before it
        # we have come across a word

        if text[i] == ' ' and text[i - 1] != ' ':
            num_words += 1

        # if it's the last character and

        elif i == n - 1 and (text[i] != '.' or text[i] != '!' or text[i] != '?' or text[i] != ' ' or text[i] != '"'):
            num_words += 1

    return num_words


def get_num_sentences(text):
    n = len(text)
    num_sentences = 0

    # if current char is a . ! or ?, we have come across completion of sentence
    # but if there was a . ! or ? before it, don't count it as a sentence

    for i in range(n):
        if (text[i] == '.' or text[i] == '!' or text[i] == '?') and (text[i - 1] != '.' or text[i - 1] != '!' or text[i - 1] != '?' or text[i - 1] != ' '):
            num_sentences += 1

    return num_sentences


main()
