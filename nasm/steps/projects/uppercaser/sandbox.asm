; program           : uppercaser
; version           : 1.0
; Created date      : 13/11/2010
; Last Update       : 13/11/2010
; Author            : Dinusha N Amerasinghe
; Description       : A simple program in assembly for Linux,using NASM 2.05,
;                     demonstrating simple text file I/O (through redirection) for reading an
;                     input file to a buffer in blocks, forcing lowercase characters to
;                     uppercase, and writing the modified buffer to an output file.
; Running the program : uppercaser2 > (output file) < (input file)

section .bss    ; section containing uninitialized data

    BUFFLEN equ 1024
    BUFF: resb BUFFLEN

section .data   ; section containing initialized data

section .text   ; section containing executable code

    global _start

_start:
    nop
Read:
    mov eax, 3
    mov ebx, 0
    mov ecx, Buff
    mov edx, BUFFLEN
    int 80h
    mov esi, eax
    cmp eax, 0
    je Done

; Set up the registers for the process buffer step

    mov ecx, esi
    mov ebp, Buff
    dec ebp

; Go through the buffer and convert lowercase to uppercase characters:

    cmp byte [ebp+ecx], 61h
    jb Next 
    cmp byte [ebp+ecx], 7Ah
    ja Next

    sub byte [ebp+ecx], 20h
Next: dec ecx
      jnz Scan

Write:
     mov eax, 4
     mov ebx, 1
     mov ecx, Buff
     mov edx, esi
     int 80h
     jmp Read

Done:
     mov eax, 0
     mov ebx, 0
     int 80h

    nop

