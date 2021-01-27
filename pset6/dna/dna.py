from sys import argv
import csv

# TODO - this could be generated from the headers of database file itself
# STRS = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]
# STRS = ["AGATC", "AATG", "TATC"] # For tests on small csv

# STRS = []


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    else:
        database_file = argv[1]
        sequence_file = argv[2]

    # lazy hack for now
    global STRS

    if database_file == "databases/small.csv":
        STRS = ["AGATC", "AATG", "TATC"]
    elif database_file == "databases/large.csv":
        STRS = ["AGATC", "TTTTTTCT", "AATG", "TCTAG", "GATA", "TATC", "GAAA", "TCTG"]

    # print(STRS)

    people_str_dict = load_database(database_file)
    sequence = load_sequence(sequence_file)
    str_count_dict = dict()
    str_count_dict = compute_str_count(sequence)
    check_str_match(str_count_dict, people_str_dict)

# loads the csv of people with their respective STR count and store in dic in following format
# Alice {'AGATC': '2', 'AATG': '8', 'GATA': '3'}
# Bob {'AGATC': '4', 'AATG': '1', 'GATA': '5'}
# Charlie {'AGATC': '3', 'AATG': '2', 'GATA': '5'}


def load_database(database_file):
    people_str_dict = dict()
    with open(database_file, newline='') as csvfile:
        reader = csv.DictReader(csvfile)
        # STRS = reader.fieldnames

        for row in reader:
            #print(row['name'], row['AGATC'])

            people_str_dict[row['name']] = {}  # e.g. Alice = {}
            for i in range(len(STRS)):
                people_str_dict[row['name']][STRS[i]] = row[STRS[i]]  # e.g. Alice = {'AGATC': '2', ...}

        # STRS.pop(0)
        # print(STRS)
    # for k, v in people_str_dict.items():
        # print(k, v)

        # for i in range(len(STRS)):
            # print(v[STRS[i]])

    return people_str_dict


def load_sequence(sequence_file):
    with open(sequence_file, 'r') as file:
        sequence = file.read().replace('\n', '')

    # print(sequence)
    return sequence

# compute the longest run of consecutive repeats of the STR in the DNA sequence from the sequence txt file
# traverse from 0 to last of the sequence and keep count of consecutive STRs found
# again traverse from 1 to last and keep count
# and so on
# store max count in the dict into respective STR key
# e.g. {"AAATG" : '2'


def compute_str_count(sequence):
    str_count_dict = dict()
    n = len(sequence)
    # print(n)
    max = 0
    count = 0
    for str in STRS:
        max = 0
        count = 0
        for cursor in range(n):
            max = max if max > count else count
            # print(f"max: {max}")
            # print(f"str len: {len(str)}")
            for j in range(cursor, n, len(str)):  # cursor keeps on increasing
                if j + len(str) > n:  # if end remaining chunk is smaller than the required chunk lenght of STR, end
                    # print(j)
                    max = max if max > count else count
                    count = 0
                    break
                else:
                    if sequence[j:j+len(str)] == str:  # take STR size chunk or substring and compare
                        # until the same STR is found consecutively, increment count
                        # if there is break in the consecutive repititon, count is reset
                        count += 1
                        # print(f"found at {j} {sequence[j:j+len(str)]}")
                    else:
                        max = max if max > count else count
                        count = 0
                        break

        str_count_dict[str] = max

        # print(f"{str} : {str_count_dict[str]}")
        # check_str_repitition(STRS[i],)

    return str_count_dict

# compare str_count_dict based on sequence.txt file with the
# str count of people loaded into people_str_dict


def check_str_match(str_count_dict, people_str_dict):
    for name, values in people_str_dict.items():
        # print(name, values)
        count = 0
        for str in STRS:
            if int(values[str]) == int(str_count_dict[str]):
                count += 1
            else:
                break
        if count == len(STRS):
            # print("MATCH")
            print(name)
            return 0

    print("No Match")


main()
