# use "gcc" to compile source files.
CC = gcc
# the linker is also "gcc". It might be something else with other compilers.
LD = gcc
# Compiler flags go here.
CFLAGS = -g -Wall
# Linker flags go here. Currently there aren't any, but if we'll switch to
# code optimization, we might add "-s" here to strip debug info and symbols.
LDFLAGS =
# use this command to erase files.
RM = /bin/rm -f
# list of generated object files.
OBJS = main.o file1.o file2.o
# program executable file name.
PROG = prog

# top-level rule, to compile everything.
all: $(PROG)

# rule to link the program
$(PROG): $(OBJS)
        $(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

# rule for file "main.o".
main.o: main.c file1.h file2.h
        $(CC) $(CFLAGS) -c main.c

# rule for file "file1.o".
file1.o: file1.c file1.h
        $(CC) $(CFLAGS) -c file1.c

# rule for file "file2.o".
file2.o: file2.c file2.h
        $(CC) $(CFLAGS) -c file2.c

# rule for cleaning re-compilable files.
clean:
        $(RM) $(PROG) $(OBJS)
