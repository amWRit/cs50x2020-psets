# CS50x 2020
Contains my solutions for Harvard's CS50x 2020 problem sets.
(https://cs50.harvard.edu/x/2020/)

## Week 0 Scratch 😺
Implement in Scratch any project of your choice, be it an interactive story, game, animation, or anything else, subject 

## Week 1 C
### Hello
Modify this program in such a way that it first prompts the user for their name and then prints hello, so-and-so, 
where so-and-so is their actual name.

### Mario (less)
Recreate the Mario pyramid in C, albeit in text, using hashes (#) for bricks, a la the below.
Allow the user to decide just how tall the pyramid should be by first prompting them for a positive integer between, 
say, 1 and 8, inclusive.

Here’s how the program might work if the user inputs 8 when prompted:

````
$ ./mario
Height: 8
       #
      ##
     ###
    ####
   #####
  ######
 #######
########
````

### Mario (more)
Here’s how the program might work if the user inputs 8 when prompted:

````
$ ./mario
Height: 8
       #  #
      ##  ##
     ###  ###
    ####  ####
   #####  #####
  ######  ######
 #######  #######
########  ########
````

### Cash
Implement a program that first asks the user how much change is owed and then prints the minimum number of coins with which that change can be made.

````
Your program should behave per the examples below.

$ ./cash
Change owed: 0.41
4

$ ./cash
Change owed: -0.41
Change owed: foo
Change owed: 0.41
4
````

### Credit
Write a program that prompts the user for a credit card number and then reports (via printf) whether 
it is a valid American Express, MasterCard, or Visa card number.

Most cards use an algorithm invented by Hans Peter Luhn of IBM. According to Luhn’s algorithm, you can determine if a 
credit card number is (syntactically) valid.

Consider the below representative of how your own program should behave when passed a valid credit card number (sans hyphens).
````
$ ./credit
Number: 4003600000000014
VISA

$ ./credit
Number: 4003-6000-0000-0014
Number: foo
Number: 4003600000000014
VISA

$ ./credit
Number: 6176292929
INVALID
````

## Week 2 Arrays
### Caesar
Implement a program that encrypts messages using Caesar’s cipher, per the below.
````
$ ./caesar 13
plaintext:  HELLO
ciphertext: URYYB
````
Here are a few examples of how the program might work. For example, if the user inputs a key of 1 and a plaintext of HELLO:
````
$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP
````

Here’s how the program might work if the user provides a key of 13 and a plaintext of hello, world:
````
$ ./caesar 13
plaintext:  hello, world
ciphertext: uryyb, jbeyq
````

 Here’s how the program might work if the user provides a key of 13 again, with a more complex plaintext:
````
$ ./caesar 13
plaintext:  be sure to drink your Ovaltine
ciphertext: or fher gb qevax lbhe Binygvar
````

### Readability
Implement a program that computes the approximate grade level needed to comprehend some text, per the below.
````
$ ./readability
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
````

A number of “readability tests” have been developed over the years, to give a formulaic process for computing the reading level of a text.

One such readability test is the Coleman-Liau index. The Coleman-Liau index of a text is designed to output what (U.S.) grade level is needed to understand the text. The formula is:

````index = 0.0588 * L - 0.296 * S - 15.8````

Here, __L__ is the average number of letters per 100 words in the text, and __S__ is the average number of sentences per
 100 words in the text.

Let’s write a program called readability that takes a text and determines its reading level. For example, if user types in a line from Dr. Seuss:
````
$ ./readability
Text: Congratulations! Today is your day. You're off to Great Places! You're off and away!
Grade 3
````

## Week 3 Algorithms
###Plurality
Implement a program that runs a plurality election, per the below.
````
$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice

$ ./plurality Alice Bob Charlie
Number of voters: 5
Vote: Alice
Vote: Charlie
Vote: Bob
Vote: Bob
Vote: Alice
Alice
Bob
````

### Runoff
Implement a program that runs a runoff election, per the below.
````
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
````

## Week 4 Memory
### Filter
Implement a program that applies filters to BMPs, per the below.
````
$ ./filter -r image.bmp reflected.bmp
````

Your program should behave per the examples below.
````
$ ./filter -g infile.bmp outfile.bmp
$ ./filter -s infile.bmp outfile.bmp
$ ./filter -r infile.bmp outfile.bmp
$ ./filter -b infile.bmp outfile.bmp
````

````
g = grayscale, s = sepia, r = reflection, b =blur
````

### Recover
Implement a program that recovers JPEGs from a forensic image, per the below.
````
$ ./recover card.raw
````

## Week 5 Data Structures
### Speller
Be sure to read this specification in its entirety before starting so you know what to do and how to do it!

Implement a program that spell-checks a file, a la the below, using a hash table.
````
$ ./speller texts/lalaland.txt
MISSPELLED WORDS

[...]
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT
[...]
Shangri
[...]
fianc
[...]
Sebastian's
[...]

WORDS MISSPELLED:
WORDS IN DICTIONARY:
WORDS IN TEXT:
TIME IN load:
TIME IN check:
TIME IN size:
TIME IN unload:
TIME IN TOTAL:
````

## Week 6 Python 🐍
Submit the following psets that you previously completed in Python.

- Hello
- Mario (less)
- Mario (more)
- Cash
- Credit
- Readability

### DNA
Implement a program that identifies a person based on their DNA, per the below.
````
$ python dna.py databases/large.csv sequences/5.txt
Lavender
````
Your task is to write a program that will take a sequence of DNA and a CSV file containing STR (Short Tandem Repeats) 
counts for a list of individuals and then output to whom the DNA (most likely) belongs.

## Week 7 SQL
### Movies
Write SQL queries to answer questions about a database of movies.

To test your queries on CS50 IDE, you can query the database by running
````
$ cat filename.sql | sqlite3 movies.db
where filename.sql is the file containing your SQL query.
````

For each of the following problems, you should write a single SQL query that outputs the results specified by each problem.
- In 1.sql, write a SQL query to list the titles of all movies released in 2008.
- In 2.sql, write a SQL query to determine the birth year of Emma Stone.
- In 3.sql, write a SQL query to list the titles of all movies with a release date on or after 2018, in alphabetical order.
- In 4.sql, write a SQL query to determine the number of movies with an IMDb rating of 10.0.
- In 5.sql, write a SQL query to list the titles and release years of all Harry Potter movies, in chronological order.
- In 6.sql, write a SQL query to determine the average rating of all movies released in 2012.
- In 7.sql, write a SQL query to list all movies released in 2010 and their ratings, in descending order by rating. For movies with the same rating, order them alphabetically by title.
- In 8.sql, write a SQL query to list the names of all people who starred in Toy Story.
- In 9.sql, write a SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year.
- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated.
- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.


### House
Implement a program to import student data into a database, and then produce class rosters.
````
$ python import.py characters.csv
$ python roster.py Gryffindor

Lavender Brown, born 1979
Colin Creevey, born 1981
Seamus Finnigan, born 1979
Hermione Jean Granger, born 1979
Neville Longbottom, born 1980
Parvati Patil, born 1979
Harry James Potter, born 1980
Dean Thomas, born 1980
Romilda Vane, born 1981
Ginevra Molly Weasley, born 1981
Ronald Bilius Weasley, born 1980
````

## Week 8 Information
### Web Track
Build a simple homepage using HTML, CSS, and JavaScript.

#### Homepage
Implement in your homepage directory a website that must:
- Contain at least four different .html pages, at least one of which is index.html (the main page of your website), and
 it should be possible to get from any page on your website to any other page by following one or more hyperlinks.
- Use at least ten (10) distinct HTML tags besides <html>, <head>, <body>, and <title>. Using some tag (e.g., <p>) 
multiple times still counts as just one (1) of those ten!
- Integrate one or more features from Bootstrap into your site. Bootstrap is a popular library (that comes with lots of
 CSS classes and more) via which you can beautify your site. See Bootstrap’s documentation to get started. To add Bootstrap to your site, it suffices to include

#### Finance
Implement a website via which users can “buy” and “sell” stocks, a la the below.
(https://finance.cs50.net/)

- It allows a user to register for an account via a form.
- It allows a user to look up a stock’s current price.
- It enables a user to buy stocks.
- It displays an HTML table summarizing, for the user currently logged in, which stocks the user owns, the numbers of 
shares owned, the current price of each stock, and the total value of each holding (i.e., shares times price). 
Also display the user’s current cash balance along with a grand total (i.e., stocks’ total value plus cash).
- It enables a user to sell shares of a stock (that he or she owns).
- It displays an HTML table summarizing all of a user’s transactions ever, listing row by row each and every buy and every sell.


# DISCLAIMER:
Please don't do direct copy-paste of the codes here. You are welcome 
to look at my solutions to get ideas. But I insist you try your own ideas
and write the codes yourself.
Also be mindful that you aren't violating Academic Honesty policy (https://docs.cs50.net/2016/fall/syllabus/cs50.html#academic-honesty) of the course.



