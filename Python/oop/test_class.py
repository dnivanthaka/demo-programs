#!/bin/env python

print 'Class Demo'

class test:
    number_one = 0
    number_two = 0
    result = 0

    def add(self):
        self.result = self.number_one + self.number_two
    def print_result(self):
        '''print self.result'''
        print "My result is %s " % self.result

t = test()
t.number_one = 1
t.number_two = 2
t.add()
t.print_result()

