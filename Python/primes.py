#!/usr/bin/env python

num = 2
while num <= 1000:
    is_prime = True
    trial = 2
    #while trial < num:
    while trial ** 2 <= num:
        if (num % trial) == 0:
            is_prime = False
            break
        trial += 1
    if is_prime:
        print num
    num += 1

