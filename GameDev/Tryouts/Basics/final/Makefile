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
OBJS = main.o video.o input.o
# program executable file name.
PROG = tryout01

# top-level rule, to compile everything.
all: $(PROG)

# linking rule remains the same as before.
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

# now comes a meta-rule for compiling any "C" source file.
%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o 
