OBJS = base.o
CC = g++
CFLAGS = -Wall -o -g
CLIBS = `pkg-config gtkmm-2.4 --cflags --libs`

simple1: $(OBJS)
	$(CC) $(OBJS) -o simple1

base.o: base.cc
	$(CC) $(CFLAGS) -c base.cc -o base.o $(CLIBS)