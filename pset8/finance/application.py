import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, check_username_exists, register_user, is_positive_integer

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
    # Query database
    rows = db.execute("SELECT symbol, name, shares from (SELECT symbol, name, SUM(shares) as shares FROM transactions WHERE user_id = :user_id GROUP BY symbol) WHERE shares > 0", user_id = session["user_id"])

    data = []
    grand_total = 0
    balance = 0
    for row in rows:
        hash = {}
        symbol = row["symbol"]
        hash["symbol"] = symbol
        hash["name"] = row["name"]
        hash["shares"] = row["shares"]
        quote = lookup(symbol)
        hash["curr_price"] = quote["price"]
        hash["total"]  = float(quote["price"]) * hash["shares"]
        grand_total += hash["total"]
        data.append(hash)

    # Query database for cash balance
    rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
    balance = rows[0]["cash"]
    grand_total += balance

    return render_template("index.html", data = data, balance = balance, grand_total = grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # lookup symbol and get price
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # if the symbol doesn't exist with iex
        if quote == None:
            return apology("Symbol incorrect")

        symbol = quote["symbol"]
        num_shares = request.form.get("shares")

        if not is_positive_integer(num_shares):
            return apology("Incorrect input")

        price = quote["price"]
        name = quote["name"]
        total_cost = float(price) * int(num_shares)

        # check for current balance

        # Query database for cash balance
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
        available_cash = rows[0]["cash"]

        if total_cost > available_cash:
            #can't buy
            return apology("Not enough cash")
        else:
            # insert into transactions
            available_cash = available_cash - total_cost
            status = "buy"
            rows = db.execute("INSERT INTO transactions (symbol, shares, status, price, name, user_id) \
            VALUES (:symbol, :num_shares, :status, :price, :name, :user_id)", \
            symbol = symbol, num_shares = num_shares, status = status, price = price, name = name, user_id = session["user_id"])

            # decrease balance
            db.execute("UPDATE users SET cash = :available_cash where id = :user_id", available_cash = available_cash, user_id = session["user_id"])

            return index()

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Query database
    rows = db.execute("SELECT symbol, shares, price, date_time FROM transactions WHERE user_id = :user_id ", user_id = session["user_id"])

    data = []
    for row in rows:
        hash = {}
        hash["symbol"] = row["symbol"]
        hash["shares"] = row["shares"]
        hash["price"] = row["price"]
        hash["date_time"] = row["date_time"]

        data.append(hash)

    return render_template("history.html", data = data)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # if the symbol doesn't exist with iex
        if quote == None:
            return apology("Symbol incorrect")

        symbol = quote["symbol"]
        return render_template("quoted.html", name = quote["name"], price = usd(quote["price"]), symbol = symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # register
        username = request.form.get("username")
        pwd1 = request.form.get("password1")
        pwd2 = request.form.get("password2")
        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not pwd1 or not pwd2:
            return apology("must provide password", 403)

        # Ensure two passwords match
        elif pwd1 != pwd2:
            return apology("Passwords do not match", 403)

        elif check_username_exists(username):
            # check if username exists
            return apology("Username already exists.", 403)
        else:
            pwd_hash = generate_password_hash(pwd1, method='pbkdf2:sha256', salt_length=8)

            if register_user(username, pwd_hash):
                return render_template("login.html")
            else:
                return apology("Could not register.", 403)

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        rows = db.execute("SELECT symbol from (SELECT symbol, SUM(shares) as shares FROM transactions WHERE user_id = :user_id GROUP BY symbol) WHERE shares > 0", user_id = session["user_id"])
        return render_template("sell.html", rows = rows)
    else:
        # lookup symbol and get price
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # if the symbol doesn't exist with iex
        if quote == None:
            return apology("Symbol incorrect")

        symbol = quote["symbol"]
        num_shares = request.form.get("shares")

        if not is_positive_integer(num_shares):
            return apology("Incorrect input")

        rows = db.execute("SELECT SUM(shares) as shares FROM transactions WHERE user_id = :user_id and symbol = :symbol GROUP BY symbol", user_id = session["user_id"], symbol = symbol)
        available_shares = rows[0]["shares"]

        if int(num_shares) > available_shares:
            return apology("Not enough shares to sell")

        price = quote["price"]
        name = quote["name"]
        total_cost = float(price) * int(num_shares)

        # Query database for cash balance
        rows = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
        available_cash = rows[0]["cash"]

        # insert into transactions
        available_cash = available_cash + total_cost
        status = "sell"
        rows = db.execute("INSERT INTO transactions (symbol, shares, status, price, name, user_id) \
        VALUES (:symbol, :num_shares, :status, :price, :name, :user_id)", \
        symbol = symbol, num_shares = - int(num_shares), status = status, price = price, name = name, user_id = session["user_id"])

        # decrease balance
        db.execute("UPDATE users SET cash = :available_cash where id = :user_id", available_cash = available_cash, user_id = session["user_id"])

        return index()


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
