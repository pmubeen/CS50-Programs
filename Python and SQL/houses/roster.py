# Name: roster.py
# Author: Mubeen Padaniya
# Version: 1
# Description: Takes in a housename as input and executes an SQL query that outputs the students in the house

#importing required libraries
from sys import argv
from cs50 import SQL

#check for usage
if len(argv) != 2:
    print("Error: Incorrect Usage.\nUsage: python roster.py housename")
    exit()
#opening the database and running a query
db = SQL("sqlite:///students.db")
squery = db.execute(f"SELECT first, middle, last, birth FROM students WHERE house = \"{argv[1]}\" ORDER By last ASC, first ASC")
#outputs the student names
if squery == []:
    print("No student in that house. Check if spelling is correct or use valid housename.")
    exit()
for row in squery:
    if row["middle"] == None:
        print(row["first"]+" "+row["last"]+", born "+str(row["birth"]))
    else:
        print(row["first"]+" "+row["middle"]+" "+row["last"]+", born "+str(row["birth"]))