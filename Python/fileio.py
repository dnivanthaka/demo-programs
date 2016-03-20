#!/usr/bin/env python

reader = open( 'haiku.txt', 'r' )
data = reader.read()
reader.close()
print len(data)

reader = open( 'haiku.txt', 'r' )
data = reader.read(64)
while data != '':
    print len(data)
    data = reader.read(64)
print len(data)
reader.close()

reader = open( 'haiku.txt', 'r' )
contents = reader.readlines()
reader.close()
total = 0
count = 0

for line in contents
    count += 1
    total += len(line)

print 'Average ', float(total) / float(count)

writer = open( 'temp.txt', 'w' )
print >> writer, 'elements'
for gas in ['He', 'Ne', 'Ar', 'Kr']:
    print >> writer, gas
writer.close()
