import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # Access form data
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Insert data into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?)", name, month, day)

        # Go back to homepage
        return redirect("/")

    else:

        # Query for all birthdays
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render birthdays page
        return render_template("index.html", birthdays=birthdays)


# Unsuccessful delete button implementation. Error: "View function mapping is overwriting an existing endpoint function: index"
# @app.route("/delete", methods=["GET", "POST"])
# def index():
#     if request.method == "POST":
#         db.execute("DELETE FROM birthdays WHERE id = (SELECT MAX(id) FROM birthdays)")

#     # Go back to homepage
#     return render_template("index.html", birthdays=birthdays)