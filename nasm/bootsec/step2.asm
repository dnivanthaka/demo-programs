section .data
section .text

    global _start

_start:
    nop
hang:
    jmp hang
    nop

times 510-($-$$) db 0
dw 0AA55h
section .bss
