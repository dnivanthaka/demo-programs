#!/usr/bin/env python

""" Demonstration of Euclid's Algorithm """

def gcd(a, b):
    if( b == 0 ):
        return a
    else:
        return gcd( b, a % b )

print gcd(1071, 462)
