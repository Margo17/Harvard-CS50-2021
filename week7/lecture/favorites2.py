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

        # Insert values into SQLite database
        id = db.execute("INSERT INTO shows(title) VALUES(?)", title)
        for genre in row["genres"].split(", "):
            db.execute("INSERT INTO genres (show_id, genre) VALUES(?, ?)", id, genre)