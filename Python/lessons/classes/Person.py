#!/usr/bin/env python

class Person(object):
	name = ""

	def __init__( self, n ):
		self.name = n

	def __del__( self ):
		print "Im at del"


