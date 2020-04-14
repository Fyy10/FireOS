[org 0x7c00]
[bits 16]

section .text

    global main

main:   ; entry point

; initializations
cli
jmp 0x0000:ZeroSeg
ZeroSeg:
    xor ax, ax  ; mov ax, 0
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov sp, main    ; stack pointer
    cld             ; clear direction flag, to read string from left to right
sti

; reset disk
push ax
xor ax, ax
mov dl, 0x80    ; hard disk (qemu)
int 0x13
pop ax

; start
mov si, STR_1
call printf

mov si, STR_2
call printf

mov al, 1       ; number of sectors to read
mov cl, 2       ; first sector to read (sector 1 is for ipl)
call readDisk
jmp test

jmp fin

; functions
%include "printf.s"
%include "readDisk.s"

; string here
STR_1: db "Welcome to FireOS", 0x0a, 0x0d, 0
STR_2: db "Loaded in 16-bit Real Mode to memory location 0x7c00", 0x0a, 0x0d, 0
DISK_ERR_MSG: db "Error Loading Disk...", 0x0a, 0x0d, 0
TEST_STR: db "Disk loaded successfully, you are in the second sector", 0x0a, 0x0d, 0

fin:
    hlt
    jmp fin

; padding and magic number
times 510-($-$$) db 0
dw 0xaa55

; the second sector
test:
    mov si, TEST_STR
    call printf

times 512 db 0

