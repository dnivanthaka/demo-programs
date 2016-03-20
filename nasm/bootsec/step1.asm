; step1.asm
; hangs the pc

hang:
    jmp hang

times 510-($-$$) db 0
dw 0AA55h
