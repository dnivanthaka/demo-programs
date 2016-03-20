section .data
section .text

    global _start

_start:
    nop
    mov ax, 0x07C0
    mov ds, ax
    mov si, msg
    call bios_print

hang:
    jmp hang

msg db 'It Works!!!', 13, 10, 0

bios_print:
    lodsb                   ; put char at ds:si in al and increment si
    or al, al               ; check if we are end, 0=end
    jz done
    mov ah, 0x0E
    int 0x10
    jmp bios_print
done:
    ret

    nop

times 510-($-$$) db 0
db 0x55                     ; boot signature bytes
db 0xAA
section .bss
