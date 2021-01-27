import csv
from sys import argv
import cs50


def main():

    db = cs50.SQL("sqlite:///students.db")  # connect to the db

    db.execute(" DELETE from students")
    characters_file = ""

    if len(argv) != 2:
        print("Usage: python import.py data.csv")
        quit()
    else:
        characters_file = argv[1]

    with open(characters_file, "r") as characters:
        reader = csv.DictReader(characters)

        for row in reader:
            house = row["house"]
            birth = row["birth"]

            # split names into first, middle, last

            first, middle, last = get_full_name(row["name"])
            db.execute("INSERT into students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       first, middle, last, house, birth)


# function whose purpose in life is just to get a string of full name and
# split them into first, middle and last
# if no middle name, returns middle as empty
# e.g. "Lavender NULL Brown" -> ["Lavender", "", "Brown"]
# e.g "Colin Creevey" --> ["Colin", "", "Creevey"]


def get_full_name(name):
    splitted_name = name.split()
    # print(splitted_name)

    first = splitted_name[0]
    middle = ""
    last = ""

    if len(splitted_name) == 3:
        middle = splitted_name[1]
        last = splitted_name[2]
    elif len(splitted_name) == 2:
        middle = None
        last = splitted_name[1]

    return first, middle, last


main()
