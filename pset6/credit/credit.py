from cs50 import get_string
import math


# 369421438430814 invalid
# 5673598276138003 invalid
# 371449635398431 AMEX
# 378282246310005 AMEX
# 5105105105105100 MASTERCARD
# 4012888888881881 VISA

def main():
    card_num = get_string("Number: \n")
    check_card(card_num)


def check_card(card_num):
    first = int(card_num[0])

    if valid_digits(card_num) and check_sum(card_num) and check_prefix(card_num):

        if first == 3:
            print("AMEX")
        if first == 4:
            print("VISA")
        if first == 5:
            print("MASTERCARD")

    else:
        print("INVALID")


def valid_digits(card_num):
    n = len(card_num)
    # convert string number value to integer
    # e.g. '23' -> 23

    first = int(card_num[0])

    if (n == 13 or n == 15 or n == 16) and (first == 3 or first == 4 or first == 5):
        return True
    else:
        return False


def check_sum(card_num):
    n = len(card_num)
    check_sum = 0

    reversed_card_num = card_num[::-1]

    # from the last, multiply digits in even position by 2
    # if product > 9, add the two digit as well

    for i in range(1, n, 2):

        add_val = int(reversed_card_num[i]) * 2

        if int(add_val) > 9:
            check_sum += get_sum_digits(str(add_val))
        else:
            check_sum += int(add_val)

    # add digits in odd position

    for i in range(0, n, 2):
        check_sum += int(reversed_card_num[i])

    if check_sum % 10 == 0:
        return True
    else:
        return False


def check_prefix(card_num):
    n = len(card_num)
    first = int(card_num[0])
    second = int(card_num[1])
    valid = False

    # American Express numbers start with 34 or 37

    if first == 3:
        if second == 4 or second == 7:
            return True
        else:
            return False

    # MasterCard numbers start with 51, 52, 53, 54, or 55

    elif first == 5:
        if second > 0 and second < 6:
            return True
        else:
            return False

    # All visa numbers start with 4

    elif first == 4:
        return True

    else:
        return False

# digits 0 - 9 multiplied by 2 <= 18, so always 2 digits
# num is always two length -- add those two digits


def get_sum_digits(num):
    return int(num[0]) + int(num[1])


main()
