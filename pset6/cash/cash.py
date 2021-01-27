from cs50 import get_float
import math


def main():
    dollars = get_float("Change Owed: ")
    while True:
        if dollars < 0:
            dollars = get_float("Change Owed: ")
        else:
            get_change(dollars)

# takes in dollars value and returns number of coins required in change
# assuming 4 different coins
# quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)


def get_change(dollars):
    cents = round(dollars * 100)
    num_coins = 0

    while (cents != 0):

        # https://stackoverflow.com/questions/6681743/splitting-a-number-into-the-integer-and-decimal-parts
        # a = 147.234
        # a % 1 >> 0.23400000000000887
        # a // 1 >> 147.0
        # int(a//1) >> 147

        if int((cents / 25) // 1) > 0:
            num_coins, cents = calculate(cents, num_coins, 25)
        elif int((cents / 10) // 1) > 0:
            num_coins, cents = calculate(cents, num_coins, 10)
        elif int((cents / 5) // 1) > 0:
            num_coins, cents = calculate(cents, num_coins, 5)
        else:
            num_coins += cents
            cents = 0

    print(num_coins)
    exit(0)

# function to return number of coins and remaining cents based on the coin_val passed
# quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)


def calculate(cents, num_coins, coin_val):
    factor = (int)(cents / coin_val) // 1
    num_coins += factor
    cents = cents - (coin_val * factor)
    return num_coins, cents


main()
