import os
import requests
import urllib.parse
from cs50 import SQL

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        response = requests.get(f"https://cloud-sse.iexapis.com/stable/stock/{urllib.parse.quote_plus(symbol)}/quote?token={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"

def check_username_exists(name):
    # Query database for username
    db = SQL("sqlite:///finance.db")
    rows = db.execute("SELECT * FROM users WHERE username = :username", username = name)

    # Ensure username exists and password is correct
    if len(rows) == 1:
        return True
    else:
        return False

def register_user(name, pwd_hash):

    db = SQL("sqlite:///finance.db")
    # insert user name and password hash into db
    rows = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = name, hash = pwd_hash)

    if rows == None:
        return False
    else:
        return True


# https://note.nkmk.me/en/python-check-int-float/
# https://stackoverflow.com/questions/26198131/check-if-input-is-positive-integer

def is_positive_integer(n):
    try:
        val = int(n)
        if val < 0:
            return False
    except ValueError:
        return False
    else:
        return True
