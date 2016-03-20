kangaroo: kangaroo.o
	ld -o kangaroo kangaroo.o -melf_i386
kangaroo.o: kangaroo.asm
	nasm -f elf -g -F stabs kangaroo.asm -l kangaroo.lst
