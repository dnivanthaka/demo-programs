section .data
section .text

    global _start

_start:
    nop
    ;mov eax, 'WXYZ'
    ;mov eax, 0FFFFFFFFh
    ;mov ebx, 02Dh
    ;inc eax
    ;inc ebx
    ;mov eax,5
;DoMore dec eax
    ;jmp DoMore
    ;nop
    ;mov eax,42
    ;neg eax
    ;add eax,42
    ;mov ax,-42
    ;mov ebx,eax
    ;movsx ebx,ax
    ;mov eax,447
    ;mov ebx,1739
    ;mul ebx
    mov eax,0FFFFFFFFh
    mov ebx,03B72h
    mul ebx

section .bss
