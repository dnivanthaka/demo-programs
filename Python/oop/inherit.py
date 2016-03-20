#!/bin/env python

class super:
    var1 = 5
    def super_meth1(self):
        print 'Im at super meth1'
    def print_vars(self):
        print self.var1

class child(super):
    var2 = 6
    def child_meth1(self):
        print 'Im at child meth1'


t = child()
t.var2 = 10
t.child_meth1()
t.super_meth1()
