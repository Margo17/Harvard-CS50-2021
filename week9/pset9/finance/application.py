import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Initialise variables
    user_id = session["user_id"]

    # Obtain information from database
    stocks = db.execute("SELECT symbol, name, price, SUM(shares) as totalShares FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    total = cash

    for stock in stocks:
        total += stock["price"] * stock["totalShares"]

    return render_template("index.html", stocks=stocks, cash=cash, usd_function=usd, total=total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialising values to variables from buy.html
        symbol = request.form.get("symbol").upper()

        # Obtain data via cs50 written function lookup
        stock = lookup(symbol)

        # Check if stock ticker is valid/not blank
        if not symbol:
            return apology("Please enter a symbol")
        elif not stock:
            return apology("Invalid symbol")

        # Check if share input is a positive integer
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be positive integer numbers")
        if shares <= 0:
            return apology("Shares must be positive integer numbers")

        # Initialise user id, cash, name, price
        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        stock_name = stock["name"]
        stock_price = stock["price"]
        total_price = stock_price * shares

        # Check if user has sufficient funds
        if cash < total_price:
            return apology("Insufficient funds")

        # Update database with new information
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash - total_price, user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, stock_name, shares, stock_price, "BUY", symbol)

        # Redirect user to homepage
        return redirect('/')

     # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Initialise user_id to be used in POST and GET
    user_id = session["user_id"]

    # Extract information from the database
    transactions = db.execute("SELECT type, symbol, price, shares, time FROM transactions WHERE user_id = ?", user_id)

    # Display history.html
    return render_template("history.html", transactions=transactions, usd_function=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialising values to variable from quote.html
        symbol = request.form.get("symbol")

        # Check if user typed in a ticker symbol
        if not symbol:
            return apology("Please enter a symbol")

        # Obtain data via cs50 written function lookup
        stock = lookup(symbol)

        # Check if user typed in a correct ticker symbol
        if not stock:
            return apology(" Invalid stock ticker symbol")

        # Display quoted.html
        return render_template("quoted.html", stock=stock, usd_function=usd)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Initialising values from register.html
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Check if input is blank
        if not username:
            return apology("Please enter a username")
        elif not password:
            return apology("Please enter a password")
        elif not confirmation:
            return apology("Please enter the password confirmation")

        # Check if confirmation password match
        if password != confirmation:
            return apology("Passwords do not match")

        '''
        # Check username duplication
        elif db.execute("SELECT * FROM users WHERE username = (?)", username):
            return apology("username already taken", 403)

        # Check password validity
        elif len(password) < 8 or not password.isalnum():
            return apology("password must contain 8 alphabet characters or numbers", 403)
        '''

        # Hash password
        hash = generate_password_hash(password)

        # Try to register the user and if username exists render and apology
        try:

            # Update database with new user information
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

            # Redirect user to homepage
            return redirect("/")
        except:
            return apology("Username exists")


    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Initialise user_id to be used in POST and GET
    user_id = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Variable initialisation
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares <= 0:
            return apology("Shares must be a positive number")

        # Variable initialisation
        stock_price = lookup(symbol)["price"]
        stock_name = lookup(symbol)["name"]
        price = shares * stock_price

        # Obtain owned share amount
        shares_owned = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]

        # Check if user has enough shares to sell
        if shares_owned < shares:
            return apology("Not enough shares in portfolio")

        # Obtain owned cash amount
        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        # Update users cash and transaction table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash + price, user_id)
        db.execute("INSERT INTO transactions (user_id, name, shares, price, type, symbol) VALUES (?, ?, ?, ?, ?, ?)", user_id, stock_name, -shares, stock_price, "SELL", symbol)

        # Redirect user to homepage
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Acquire symbol and display sell.html
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
