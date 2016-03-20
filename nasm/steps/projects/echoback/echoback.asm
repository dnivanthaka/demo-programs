SECTION .bss                                    ; uninitialized data

    Buff: resb 255

SECTION .data                                   ; initialized data

    AskInput db "Enter a string :", 0xA         ; ask input string
    AskInputLen equ $ - AskInput                ; length of the ask input string

SECTION .text                                   ; executable data

    global _start

_start:
    nop                                         ; keeps debuggers happy
AskData:
    mov eax, 4                                  ; using write function
    mov ebx, 1                                  ; fd of stdout
    mov ecx, AskInput                           ; output string address
    mov edx, AskInputLen                        ; length of the string
    int 0x80                                    ; call linux interrupt service dispatcher
                                    
GetInput:
    mov eax, 3                                  ; using read function
    mov ebx, 0                                  ; fd of stdin
    mov ecx, Buff                               ; pointer to buffer
    mov edx, 255                                ; number of bytes to read
    int 0x80                                    ; call linux interrupt service dispatcher

EchoBack:
    mov eax, 4                                  ; using write function
    mov ebx, 1                                  ; fd of stdout
    mov ecx, Buff                               ; output string buffer address
    mov edx, 255                                ; length of the string buffer
    int 0x80                                    ; call linux interrupt service dispatcher

;====================================
; Exit Call
;====================================
    mov eax, 1                                  ; exit function number
    mov ebx, 0                                  ; send 0 as the exit code for now
    int 0x80                                    ; call linux interrupt service dispatcher
