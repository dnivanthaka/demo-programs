#!/usr/bin/env python

def str1(some_string):
    answer = some_string + " test"
    return answer

def str2(some_string):
    some_string += "Modified"


test = "This is a test"
str2(test)
print test
res = str1("Im a string ")
print res
