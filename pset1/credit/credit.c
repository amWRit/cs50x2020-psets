#include <stdio.h>
#include <cs50.h> //header file to use specific cs50 functions

// 369421438430814 invalid
// 5673598276138003 invalid
// 371449635398431 valid
void check_card(long);
int check_digits_validity(long);
int get_digits_number(long);
int get_first_digit(long);
bool check_sum(long);
// int * make_digits_array(long);
int get_sum_of_digits(int);
bool check_prefix(int, long);

int main(void)
{
    long card_num;

    card_num = get_long("Number: \n"); // ask for the number and store in card_num variable

    //printf("%s\n", check_card(card_num));
    check_card(card_num);
}

void check_card(long card_num)
{
    int first = check_digits_validity(card_num);
    if (first > 0 && check_sum(card_num) && check_prefix(first, card_num))
    {
        if (first == 3)
        {
            printf("AMEX\n");
        }

        if (first == 4)
        {
            printf("VISA\n");
        }

        if (first == 5)
        {
            printf("MASTERCARD\n");
        }

    }
    else
    {
        printf("INVALID\n");
    }
}

int check_digits_validity(long card_num)
{
    int n = get_digits_number(card_num);
    int first = get_first_digit(card_num);

    if ((n == 13 || n == 15 || n == 16) && (first == 3 || first == 4 || first == 5))
    {
        return first;
    }
    else
    {
        return 0;
    }
}

int get_digits_number(long card_num)
{
    int count = 0;
    while (card_num != 0)
    {
        card_num /= 10;
        ++count;
    }
    //printf("%i\n", count);
    return count;
}

int get_first_digit(long card_num)
{
    long first = card_num;
    while (first >= 10)
    {
        first = first / 10;
    }
    //printf("%li\n", first);
    return (int) first;
}

bool check_sum(long card_num)
{
    int n = get_digits_number(card_num);
    int arr[n];
    int check_sum = 0;
    int j = 0;

    while (card_num > 0)
    {
        arr[j] = card_num % 10;
        //printf("%i", arr[j]);
        card_num /= 10;
        ++j;
    }

    // for(int i = 0; i < n; i ++)
    // {
    //     printf("%i", arr[i]);
    // }

    printf("\n");
    for (int i = 1; i < n; i += 2)
    {
        int add = arr[i] * 2;
        if (add > 9)
        {
            check_sum += get_sum_of_digits(add);
        }
        else
        {
            check_sum += add;
        }
        //printf("%i\n", check_sum);
    }

    for (int i = 0; i < n; i += 2)
    {
        check_sum += arr[i];
        //printf("%i\n", check_sum);
    }
    //printf("%i\n", check_sum);

    if (check_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// int * make_digits_array(long card_num)
// {
//     int n = get_digits_number(card_num);

//     return arr[];
// }

int get_sum_of_digits(int value)
{
    int sum = 0;
    while (value > 0)
    {
        int digit = value % 10;
        sum += digit;
        value /= 10;
    }
    return sum;
}

bool check_prefix(int first, long card_num)
{
    int n = get_digits_number(card_num);
    int a[n];
    int check_sum = 0;
    int j = 0;
    bool valid = false;

    while (card_num > 0)
    {
        a[j] = card_num % 10;
        //printf("%i", a[j]);
        card_num /= 10;
        ++j;
    }

    if (first == 3)
    {
        if (a[n - 2] == 4 || a[n - 2] == 7)
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else if (first == 5)
    {
        if (a[n - 2] > 0 && a[n - 2] < 6)
        {
            valid = true;
        }
        else
        {
            valid = false;
        }
    }
    else if (first == 4)
    {
        valid = true;
    }

    return valid;
}