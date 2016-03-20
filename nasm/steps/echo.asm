; -----------------------------------------------------------------------
; echo.asm
;
; NASM implementation of a program that displays its commandline arguments
; one per line.
;
; -----------------------------------------------------------------------

	global main
	extern printf

	section .text

main:
	mov ecx, [esp+4]
	mov edx, [esp+8]

top:
	push ecx
	push edx

	push dword [edx]
	push format
	call printf
	add esp, 8

	pop edx
	pop ecx

	add edx, 4
	dec ecx
	jnz top

	ret

format:
	db	'%s', 10, 0
