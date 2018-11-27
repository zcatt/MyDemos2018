'''
    a sample of re.split derived from python help doc.

'''

import re

def pp():
    print("hello")
    
def pb():
    print("pb4()")
    text = """Ross McFluff: 834.345.1254 155 Elm Street
        Ronald Heathmore: 892.345.3428 436 Finley Avenue
        Frank Burger: 925.541.7625 662 South Dogwood Way
        Heather Albrecht: 548.326.4584 919 Park Place"""

    entries = re.split("\n+\s*", text)
    
    print("entries:")

    for i in range(len(entries)):
        print("{0}: {1}".format(i, entries[i]))

    t = [re.split(":? ", entry, 4) for entry in entries]
    print("name:")
    for i in range(len(t)):
        print("{0}: {1}".format(i, t[i]))


    
