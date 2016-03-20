#!/usr/bin/env python

"""This is a demonstration of Bubble sort"""

print("Bubble Sort Demo")
list = [1, 10, 5, 25, 3, 33, 7];
"""print list.count(5)"""
def bubble_sort( l ):
    swapped = True
    n = 1
    """print l[:len(l) - 1]"""

    while( swapped == True ):
        #for e in l[:len(l) - 1]:
        swapped = False;
        for e in range(0, len(l) - 1):
            if( l[e] > l[e+1] ):
               print l[e] 
               tmp = l[e]
               l[e] = l[e+1]
               l[e+1] = tmp
               swapped = True

            #print e > l[n]
            #swapped = False
    return l

print bubble_sort(list)
