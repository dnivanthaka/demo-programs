; -----------------------------------------------------------
; hellome.asm
;
; This program writes "Hello, Dinusha" on the console and
; then exits, It needs to be linked with a C library
; -----------------------------------------------------------

	global main
	extern printf

	section .text
main:
	push message
	call printf
	add esp, 4
	ret
message:
	db	'Hello, World', 10, 0
