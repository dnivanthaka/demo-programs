#!/usr/bin/env python

gases = [ "He", "Ne", "Ar", "Kr" ]
print gases
print gases[1]
print len(gases)
print gases[-1]

for gas in gases:
    print gas

del gases[0]
print gases

gases.append("He")
print gases

print gases.count("He")

print gases.index("He")

print gases.sort()

print gases

print gases.reverse()

print gases

print "He" in gases

print range(5)

print range(2, 5)

print range(0, 10, 3)

