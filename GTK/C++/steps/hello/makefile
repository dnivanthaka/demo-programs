OBJS = helloworld.o main.o
CC = g++
CFLAGS = -Wall -o -g
CLIBS = `pkg-config gtkmm-2.4 --cflags --libs`

helloworld: $(OBJS)
	$(CC) $(OBJS) $(CLIBS) -o helloworld

helloworld.o : helloworld.cc helloworld.h
main.o       : main.cc