import csv

houses = {
    "Gryffindor": 0,
    "Hufflepuff": 0,
    "Ravenclaw": 0,
    "Slytherin": 0
}

# With as closes the file automatically after ending work
with open("Sorting Hat (Responses) - Form Responses 1.csv", "r") as file:
    # Wrap file in reading functionality
    reader = csv.reader(file)

    # Skip the next row
    next(reader)

    # Iterate over all of the rows in the spreadsheet
    for row in reader:
        house = row[1]
        houses[house] += 1