#!/usr/bin/python

import sqlite3

conn = sqlite3.connect('test.db');
conn.execute('''CREATE TABLE Category(
ID INTEGER PRIMARY KEY,
CAT_HOME VARCHAR(3),
CAT_NAME VARCHAR(20)
)''')
conn.commit()
conn.execute('''INSERT INTO CATEGORY VALUES(
NULL, 'GRO', 'GROCERIES')''')
conn.commit()

for row in conn.execute('SELECT * FROM Category'):
    print row
