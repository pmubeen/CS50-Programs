# Name: import.py
# Author: Mubeen Padaniya
# Version: 1
# Description: Takes a csv file as an input. Processes the entries in the file and saves it in a database under respective column.

#importing required libraries
from sys import argv
from cs50 import SQL
import csv

#check for correct usage
if len(argv) != 2:
    print("Error: Incorrect Usage.\nUsage: python import.py file.csv")
    exit()

#copying csv data in the database
with open(argv[1]) as students:
    db = SQL("sqlite:///students.db")
    reader = csv.reader(students, delimiter=",")
    s_id = -1
    for row in reader:
        if s_id >= 0:
            #db.execute(f"INSERT INTO students (id) VALUES (?)",(s_id))
            name = row[0].split()
            if len(name) == 3:
                db.execute(f"INSERT INTO students (first, middle, last, house, birth) VALUES (?,?,?,?,?)",name[0],name[1],name[2],row[1],row[2])
            elif len(name) == 2:
                db.execute(f"INSERT INTO students (first, last, house, birth) VALUES (?,?,?,?)",name[0],name[1],row[1],row[2])
            elif len(name) == 1:
                db.execute(f"INSERT INTO students (first, house, birth) VALUES (?,?,?)",name[0],row[1],row[2])
        s_id += 1