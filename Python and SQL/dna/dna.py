# Name: dna.py
# Author: Mubeen Padaniya
# Version: 1
# Description: Takes in a dna sequence and a csv database of gene values. Counts each gene repeat value and checks the database for matches.

#importing libraries
from sys import argv
import csv
import re

#check for correct usage
if len(argv) != 3:
    print("Error: Incorrect usage.\n Usage: python dna.py (database) (sequence)")
#initializing structures
strs = []
people = dict()
#opening database and writing it to people
with open(argv[1]) as dtbase:
    reader = csv.reader(dtbase,delimiter=",")
    head = next(reader)
    for i in range(1,len(head),1):
        strs.append(head[i])
    for row in reader:
        val = []
        for i in range(1,len(row),1):
            val.append(row[i])
        people[row[0]] = val
#opening sequence and checking each sequence value for genes. Stores the maximum repeat value for each gene
with open(argv[2]) as sequence:
    s = sequence.read()
    count = [0]*len(strs)
    for i in range(len(s)):
        for j in range(len(strs)):
            strchk = strs[j]
            c = 0
            if s[i] == strchk[0]:
                k = 0
                l = 0
                while True:
                    if (i+l) != len(s) and s[i+l] == strchk[k]:
                        if k == len(strchk)-1:
                            c += 1
                            k = -1
                    else:
                        break
                    k+=1
                    l+=1
                if c > int(count[j]):
                    count[j] = str(c)
    #checking for a match for the gene count from the database. Prints no match if no match is found.
    found = False
    for person, num in people.items():
        if num == count:
            print(person)
            found = True
    if found == False:
        print("No match.")