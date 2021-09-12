from csv import reader, DictReader
from sys import argv, exit


def main():

    # Check if command is called correctly
    if len(argv) != 3:
        exit("USAGE: python dna.py data.csv sequence.txt")

    # Open csv file and read it into memory as a dictionary
    with open(argv[1], "r") as dbfile:
        reader = DictReader(dbfile)
        dict_list = list(reader)

    # Open sequence file and read it into memory as a list
    with open(argv[2], "r") as seqfile:
        sequence = seqfile.read()

    # Takes DNA sequence, STR (short tandem repeats) as inputs and calculates max time an STR repeats
    max_counts = []

    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        max_counts.append(0)
        # Loop through sequence to find STR
        for j in range(len(sequence)):
            STR_count = 0
            # If match found, start counting repeats
            if sequence[j:(j + len(STR))] == STR:
                k = 0
                while sequence[(j + k):(j + k + len(STR))] == STR:
                    STR_count += 1
                    k += len(STR)
                # If new maximum of repeats, update max_counts
                if STR_count > max_counts[i - 1]:
                    max_counts[i - 1] = STR_count

    # Compare against data
    for i in range(len(dict_list)):
        matches = 0
        for j in range(1, len(reader.fieldnames)):
            if int(max_counts[j - 1]) == int(dict_list[i][reader.fieldnames[j]]):
                matches += 1
            if matches == (len(reader.fieldnames) - 1):
                print(dict_list[i]['name'])
                exit(0)

    print("No match")


# Script guard
if __name__ == "__main__":
    main()