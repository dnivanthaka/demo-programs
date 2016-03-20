section .data
    snippet db "KANGAROO"
section .text

    global _start

_start:
    nop
;put code here
    mov ebx,snippet
    mov eax,8
DoMore add byte [ebx],32
    inc ebx
    dec eax
    jnz DoMore
;put code here
    nop

section .bss
