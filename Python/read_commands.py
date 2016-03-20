#!/usr/bin/env python

alpha = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'];

reader = open('most_used_commands.txt', 'r')
'''data = reader.read()'''
line = reader.readline()

'''while line != '':
    line = reader.readline()
    print line'''
for line in reader:
    line = line.rstrip('\n')
    line_len = len(line)
    i = 0
    while line_len > 0:
        print ord(line[i])
        line_len -= 1
        i += 1

reader.close()
'''print len(data)'''
