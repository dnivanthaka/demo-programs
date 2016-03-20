#!/usr/bin/env python

"""This is a demonstration of fibonacci algorithm"""


print("Fibonacci Algorithm Demo")

def fib(n):
    if n > 1:
        return fib( n - 1 ) + fib( n - 2 )
        """return n * fib( n - 1 )"""
    elif n == 1:
        return 1
    else:
        return 0
print fib(6)
