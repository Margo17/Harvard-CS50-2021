# Prints popularity of titles in CSV, sorted by popularity

import csv
from cs50 import SQL

# Create an empty file to interact with
open("shows.db", "w").close()
db = SQL("sqlite:///shows.db")

db.execute("CREATE TABLE shows (id INTEGER, title TEXT, PRIMARY KEY(id))")
db.execute("CREATE TABLE genres (show_id INTEGER, genre TEXT, FOREIGN KEY(show_id) REFERENCES shows(id))")

# For accumulating (and later sorting) titles
titles = {}

# Open CSV file
with open("Favorite TV Shows - Form Responses 1.csv", "r") as file:

    # Create DictReader
    reader = csv.DictReader(file)

    # Iterate over CSV file, adding each (uppercased) title to dictionary
    for row in reader:

        # Canoncalize title
        title = row["title"].strip().upper()

        # Count title
        if title not in titles:
            titles[title] = 1
        titles[title] += 1

# Print titles in sorted order
for title in sorted(titles, key=lambda title: titles[title], reverse=True):
    print(title, titles[title])