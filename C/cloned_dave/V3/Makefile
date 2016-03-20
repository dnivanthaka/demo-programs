# use "gcc" to compile source files.
CC = g++
# the linker is also "gcc". It might be something else with other compilers.
LD = g++
# Compiler flags go here.
CFLAGS = -g -Wall 
# Linker flags go here. Currently there aren't any, but if we'll switch to
# code optimization, we might add "-s" here to strip debug info and symbols.
LDFLAGS = -lSDL -lSDL_image
# use this command to erase files.
RM = /bin/rm -f
# list of generated object files.
OBJS = main.o level.o graphics.o player.o entities.o events.o
# program executable file name.
PROG = dave

# top-level rule, to compile everything.
all: $(PROG)

# linking rule remains the same as before.
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

# rule for file "main.o".
main.o: main.cpp level.h graphics.h player.h entities.h events.h
	$(CC) $(CFLAGS) -c main.cpp

# rule for file "file1.o".
level.o: level.cpp level.h
	$(CC) $(CFLAGS) -c level.cpp

# rule for file "file2.o".
graphics.o: graphics.cpp graphics.h
	$(CC) $(CFLAGS) -c graphics.cpp

# rule for file "file2.o".
player.o: player.cpp player.h
	$(CC) $(CFLAGS) -c player.cpp

# rule for file "file2.o".
entities.o: entities.cpp entities.h
	$(CC) $(CFLAGS) -c entities.cpp

events.o: events.cpp events.h
	$(CC) $(CFLAGS) -c events.cpp

# rule for cleaning re-compilable files.
clean:
	$(RM) $(PROG) $(OBJS)
