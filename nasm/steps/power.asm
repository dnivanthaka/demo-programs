; ---------------------------------------------------------
; power.asm
;
; Command line application to compute x^y
; Syntax: power x y
; x and y are integers
; ---------------------------------------------------------

	global main
	extern atoi
	extern printf

	section .text

main:
	push ebx
	push esi
	push edi

	mov eax, [esp+16]
	cmp eax, 3
	jne error1

	mov ebx, [esp+20]  ; argv
	push dword [ebx+4]
	call atoi
	add esp, 4
	mov esi, eax
	push dword [ebx+8]
	call atoi
	add esp, 4
	cmp eax, 0
	jl error2
	mov edi, eax

	mov eax, 1

check:
	test edi, edi
	jz gotit
	imul eax, esi
	dec edi
	jmp check

gotit:
	push eax
	push answer
	call printf
	add esp, 8
	jmp done

error1:
	push badArgumentCount
	call printf
	add esp, 4
	jmp done

error2:
	push negativeExponent
	call printf
	add esp, 4

done:
	pop edi
	pop esi
	pop ebx
	ret

answer:
	db '%d', 10 ,0
badArgumentCount:
	db 'Requires exactly two arguments', 10, 0
negativeExponent:
	db 'The exponent may not be negative', 10, 0
