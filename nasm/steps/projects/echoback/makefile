echoback: echoback.o
	ld -o echoback echoback.o -melf_i386
echoback.o: echoback.asm
	nasm -f elf -g -F stabs echoback.asm -l echoback.lst
