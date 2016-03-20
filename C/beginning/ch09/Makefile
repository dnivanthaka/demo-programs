# This is a Makefile comment
# MACRONAME=value
# BlankMACRO=
# $(MACRONAME) or ${MACRONAME}
# $? List of prerequisites (files the target depends on) changed more recently than the current target
# $@ Name of the current target
# $< Name of the current prerequisite
# $* Name of the current prerequisite, without any suffix


myapp: main.o 2.o 3.o
	gcc -o myapp main.o 2.o 3.o

main.o: main.c a.h
	gcc -c main.c

2.o: 2.c a.h b.h
	gcc -c 2.c

3.o: 3.c b.h c.h
	gcc -c 3.c
