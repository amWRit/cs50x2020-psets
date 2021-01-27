from cs50 import get_int


def main():
    height = get_int("Enter a height between 1 and 8: ")
    while True:
        if height < 1 or height > 8:
            height = get_int("Enter a height between 1 and 8: ")
        else:
            hash_pyramid(height)

# function that takes a integer paramter
# and builds a right pushed pyramid of height (between 1 and 8) of that paramter
#e.g. height = 3
          #
         ##
        ###


def hash_pyramid(height):
    for i in range(height):
        for j in range(height - i - 1):
            print(" ", end="")
        for k in range(i+1):
            print("#", end="")
        print()
    exit(0)


main()
