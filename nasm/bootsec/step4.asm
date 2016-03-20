[BITS 16]
[ORG 0]
    
jmp start
    bootdrv db 0
    msg     db 'It Works!!!', 13, 10, 0
    Digits  db  '0123456789'

start:
    nop
    ;jmp 07c0h
    ;mov ax, 0x07C0
    ;xor ax, ax
    mov ax, 0x07C0
    mov ds, ax

    mov [bootdrv], dl ; save the drive we booted from

    mov si, msg
;-------- Setting up the Stack --------------------------------------
    cli
    mov ax, 0x9000 ; The typical place for stack
    mov ss, ax
    mov sp, 0xffff ; using the whole segment :)
    sti
;--------------------------------------------------------------------

    call bios_print

    xor bx, bx
    ;xor cx, cx
    mov ah, 0x0E
    ;add byte[bootdrv], 48
    ;mov al, 'A'
    ;mov al, si
    ;mov si, Digits
    ;mov cl, [bootdrv]
    ;inc cx
    ;mov ch, [bootdrv]
    ;mov cl, [bootdrv]
    ;mov al, byte [Digits+ecx] ; al or ah cannot be part of a LEA call
    ;mov al, byte [si+bootdrv]
    cmp byte [bootdrv], 0
    je floppy
    cmp byte [bootdrv], 1
    je floppy
    mov al, 'C'
    int 0x10
    jmp hang
floppy:
    mov al, 'A'
    int 0x10
    ;jmp hang
    ;mov al, byte [Digits+ecx]
    ;add al, byte [Digits+al]
    ;mov al, [bootdrv]
    ;add al, '0'
    ;int 0x10

hang:
    jmp hang


;--------------------------------------------------------------------
bios_print:
    lodsb                   ; put char at ds:si in al and increment si
    or al, al               ; check if we are end, 0=end
    jz done
    mov ah, 0x0E
    ;mov bx,0007
    int 0x10
    jmp bios_print
done:
    ret
;--------------------------------------------------------------------

    nop

times 510-($-$$) db 0
db 0x55                     ; boot signature bytes
db 0xAA
