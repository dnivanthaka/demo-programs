; -------------------------------------------------------------
; fib.asm
;
; This is a colosle program that writes the first 40 Fibonacci numbers.
; It needs to be linked with a C library.
; -------------------------------------------------------------

	global main
	extern printf

	section .text
main:
	push ebx

	mov ecx, 40
	xor eax, eax
	xor ebx, ebx
	inc ebx
print:
	push eax
	push ecx

	push eax
	push format
	call printf
	add esp, 8

	pop ecx
	pop eax

	mov edx, eax
	mov eax, ebx
	add ebx, edx
	dec ecx
	jnz print

	pop ebx
	ret

format:
	db	'%10d', 0
