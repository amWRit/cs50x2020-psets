import csv
from sys import argv
import cs50


def main():

    db = cs50.SQL("sqlite:///students.db")

    if len(argv) != 2:
        print("Usage: python roster.py Gryffindo")
        quit()
    else:
        house_name = argv[1]
        print(house_name)

    # as per spec, Students should be ordered by last name. For students with the same last name, they should be ordered by first name.
    # get list of students from that particular house order by the last name
    # then order them again according to first name
    # the double ordering is so as to order the students with same last name by first name

    rows = db.execute("SELECT * from (SELECT * FROM students where house = ? ORDER BY first) ORDER BY last", house_name)
    # print(rows)

    for student in rows:
        first = student["first"]
        middle = student["middle"]
        last = student["last"]
        birth = student["birth"]

        if middle != None:
            print(f"{first} {middle} {last}, born {birth}")
        else:
            print(f"{first} {last}, born {birth}")


main()