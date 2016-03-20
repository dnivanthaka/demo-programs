partmaker: main.o io.o part_table.o
	gcc main.o io.o part_table.o -o partmaker

io.o: io.c io.h
main.o: main.c part_table.h io.h
part_table.o: part_table.c part_table.h

